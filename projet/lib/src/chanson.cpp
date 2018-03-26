/**
 * \file chanson.cpp
 * \brief implementation de la classe Chanson
 * \author 
 */

#include "chanson.h"

const uint16_t Chanson::PERIODE_MAX = 32;
uint16_t Chanson::compteurNotesChanson = 0;
uint16_t Chanson::compteurMsNote = 0;
ChansonMusique Chanson::chansonCourante_ = Chansons::chansonTeletubbies; // chanson par defaut

/**
 * Callback pour les notes de la chanson
 * \todo typedef pour pointeur vers methode de classe
 */
void callbackNoteChanson()
{
    // si la chanson n'est pas finie
    if(Chanson::compteurNotesChanson < Chanson::chansonCourante_.nbNotes)
    {
        // recupere la note
        NoteChanson note = Chanson::chansonCourante_.notes[Chanson::compteurNotesChanson];
        // calcule la duree instantanee
        uint8_t duree = (Chanson::compteurMsNote > Chanson::PERIODE_MAX) ? Chanson::PERIODE_MAX : Chanson::compteurMsNote;
        // decremente le compteur de duree
        Chanson::compteurMsNote -= duree;

        // joue la note
        Chanson::playNote(note.noteMidi, duree);

        // si la note a finie de jouer
        if(Chanson::compteurMsNote == 0)
        {
            // incremente compteur
            Chanson::compteurNotesChanson++;
            // initialise le compteur de temps pour la prochaine note
            Chanson::compteurMsNote = Chanson::getDureeMsNoteSelonNoteMusicaleEtTempo(
                                        Chanson::chansonCourante_.notes[Chanson::compteurNotesChanson].duree,
                                        Chanson::chansonCourante_.tempo);
        }
    }
    else
    {
        // chanson terminee
        Debug::out("chanson terminee\n");
        Chanson::stop();
    }
}

void Chanson::init()
{
    // initialise le buzzer
    Buzzer::init();

    // initialise le timer0
    Timer0::setCompACallback(&callbackNoteChanson);

    // selectionne un prescaler de 1024
    /// \todo integre avec NoteMusicale
    Timer0::setPrescaler(Prescaler::Pres_1024);
}

void Chanson::setChanson(const ChansonMusique& chanson)
{
    chansonCourante_ = chanson;
}

void Chanson::play()
{
    // reinitialise compteur de notes
    compteurNotesChanson = 0;

    // initialise le compteur de temps pour la premiere note
    compteurMsNote = getDureeMsNoteSelonNoteMusicaleEtTempo(
                        chansonCourante_.notes[compteurNotesChanson].duree,
                        chansonCourante_.tempo);

    // part le timer pour la note
    Timer0::start();
}

void Chanson::playNote(uint8_t noteMidi, uint8_t duree)
{
    // joue la note
    Buzzer::play(noteMidi);

    // regle le timer pour la note
    Timer0::setOCRnA(getValOCRnFromMs(duree));
}

void Chanson::pause()
{
    Buzzer::stop();
    Timer0::stop();
}

void Chanson::stop()
{
    pause();
    compteurNotesChanson = 0;
    Debug::out("chanson stop\n");
}

uint8_t Chanson::getValOCRnFromMs(const uint8_t& ms)
{
    return (ms * (F_CPU / 1000)) / static_cast<uint16_t>(Prescaler::Pres_1024);
}

uint16_t Chanson::getDureeMsNoteSelonNoteMusicaleEtTempo(const NoteMusicale& note, const Tempo& tempo)
{
    // 1000 [ms/s] * 60 [s/min] / tempo [BPM]
    //    = le nombre de millisecondes d'un beat selon le tempo
    uint16_t beatMs = (1000 / static_cast<uint8_t>(tempo)) * 60;
    uint16_t duree = 0;

    switch(note)
    {
        case NoteMusicale::Carree:
            duree = (beatMs * 8);
            break;
        case NoteMusicale::Ronde:
            duree = (beatMs * 4);
            break;
        case NoteMusicale::Blanche:
            duree = (beatMs * 2);
            break;
        default:
        case NoteMusicale::Noire:
            duree = (beatMs * 1);
            break;
        case NoteMusicale::Croche:
            duree = (beatMs / 2);
            break;
        case NoteMusicale::DoubleCroche:
            duree = (beatMs / 4);
            break;
        case NoteMusicale::TripleCroche:
            duree = (beatMs / 8);
            break;
        case NoteMusicale::QuadrupleCroche:
            duree = (beatMs / 16);
            break;
    }

    return duree;
}

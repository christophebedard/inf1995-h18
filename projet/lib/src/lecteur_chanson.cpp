/**
 * \file lecteur_chanson.cpp
 * \brief implementation de la classe LecteurChanson
 * \author 
 */

#include "lecteur_chanson.h"

const uint16_t LecteurChanson::PERIODE_MAX = 32;
uint16_t LecteurChanson::compteurNotesChanson = 0;
uint16_t LecteurChanson::compteurMsNote = 0;
ChansonMusique LecteurChanson::chansonCourante_ = Chansons::twentieth; // chanson par defaut
bool LecteurChanson::isPlaying_ = false;

/**
 * Callback pour les notes de la chanson
 * \todo typedef pour pointeur vers methode de classe
 */
void callbackNoteChanson()
{
    // si la chanson n'est pas finie
    if(LecteurChanson::compteurNotesChanson < LecteurChanson::chansonCourante_.nbNotes)
    {
        // recupere la note
        NoteChanson note = LecteurChanson::chansonCourante_.notes[LecteurChanson::compteurNotesChanson];
        // calcule la duree instantanee
        uint8_t duree = (LecteurChanson::compteurMsNote > LecteurChanson::PERIODE_MAX) ? LecteurChanson::PERIODE_MAX : LecteurChanson::compteurMsNote;
        // decremente le compteur de duree
        LecteurChanson::compteurMsNote -= duree;

        // joue la note
        LecteurChanson::playNote(note.noteMidi, duree);

        // si la note a finie de jouer
        if(LecteurChanson::compteurMsNote == 0)
        {
            // incremente compteur
            LecteurChanson::compteurNotesChanson++;
            // initialise le compteur de temps pour la prochaine note
            LecteurChanson::compteurMsNote = LecteurChanson::getDureeMsNoteSelonFigureDeNoteEtTempo(
                                        LecteurChanson::chansonCourante_.notes[LecteurChanson::compteurNotesChanson].duree,
                                        LecteurChanson::chansonCourante_.tempo);
        }
    }
    else
    {
        // chanson terminee
        LecteurChanson::stop();
    }
}

void LecteurChanson::init()
{
    // initialise le buzzer
    Buzzer::init();

    // initialise le timer0
    Timer0::setCompACallback(&callbackNoteChanson);

    // selectionne un prescaler de 1024
    /// \todo integre avec FigureDeNote
    Timer0::setPrescaler(Prescaler::Div_1024);
}

void LecteurChanson::setChanson(const ChansonMusique& chanson)
{
    chansonCourante_ = chanson;
}

void LecteurChanson::play()
{
    // reinitialise compteur de notes
    compteurNotesChanson = 0;

    // initialise le compteur de temps pour la premiere note
    compteurMsNote = getDureeMsNoteSelonFigureDeNoteEtTempo(
                        chansonCourante_.notes[compteurNotesChanson].duree,
                        chansonCourante_.tempo);

    // part le timer pour la note
    Timer0::start();

    // set le flag de lecture en cours
    isPlaying_ = true;
}

void LecteurChanson::playNote(uint8_t noteMidi, uint8_t duree)
{
    // joue la note
    Buzzer::play(noteMidi);

    // regle le timer pour la note
    Timer0::setOCRnA(getValOCRnFromMs(duree));
}

void LecteurChanson::pause()
{
    Buzzer::stop();
    Timer0::stop();
}

void LecteurChanson::stop()
{
    pause();
    compteurNotesChanson = 0;
    isPlaying_ = false;
}

bool LecteurChanson::isPlaying()
{
    return isPlaying_;
}

uint8_t LecteurChanson::getValOCRnFromMs(const uint8_t& ms)
{
    return (ms * (F_CPU / 1000)) / static_cast<uint16_t>(Prescaler::Div_1024);
}

uint16_t LecteurChanson::getDureeMsNoteSelonFigureDeNoteEtTempo(const FigureDeNote& note, const Tempo& tempo)
{
    // 1000 [ms/s] * 60 [s/min] / tempo [BPM]
    //    = le nombre de millisecondes d'un beat selon le tempo
    uint16_t beatMs = (1000 / static_cast<uint8_t>(tempo)) * 60;
    uint16_t duree = 0;

    switch(note)
    {
        case FigureDeNote::Carree:
            duree = (beatMs * 8);
            break;
        case FigureDeNote::Ronde:
            duree = (beatMs * 4);
            break;
        case FigureDeNote::Blanche:
            duree = (beatMs * 2);
            break;
        default:
        case FigureDeNote::Noire:
            duree = (beatMs * 1);
            break;
        case FigureDeNote::Croche:
            duree = (beatMs / 2);
            break;
        case FigureDeNote::DoubleCroche:
            duree = (beatMs / 4);
            break;
        case FigureDeNote::TripleCroche:
            duree = (beatMs / 8);
            break;
        case FigureDeNote::QuadrupleCroche:
            duree = (beatMs / 16);
            break;
    }

    return duree;
}

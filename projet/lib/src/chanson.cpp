/**
 * \file chanson.cpp
 * \brief implementation de la classe Chanson
 * \author 
 */

#include "chanson.h"

const uint16_t Chanson::PERIODE_MAX = 32;
uint16_t Chanson::compteurNotesChanson = 0;
uint16_t Chanson::compteurMsNote = 0;

const uint16_t Chanson::NOMBRE_NOTES_CHANSON = 66;
const NoteChanson Chanson::NOTES_CHANSON[] = {
    {76, UNITE_TEMPS_MS}, {76, UNITE_TEMPS_MS}, {20, UNITE_TEMPS_MS}, {76, UNITE_TEMPS_MS}, {20, UNITE_TEMPS_MS},
    {72, UNITE_TEMPS_MS}, {76, UNITE_TEMPS_MS}, {20, UNITE_TEMPS_MS}, {79, UNITE_TEMPS_MS}, {20, UNITE_TEMPS_MS},
    {67, UNITE_TEMPS_MS}, {20, UNITE_TEMPS_MS}, {72, UNITE_TEMPS_MS}, {20, UNITE_TEMPS_MS}, {67, UNITE_TEMPS_MS},
    {20, UNITE_TEMPS_MS}, {64, UNITE_TEMPS_MS}, {20, UNITE_TEMPS_MS}, {69, UNITE_TEMPS_MS}, {20, UNITE_TEMPS_MS},
    {71, UNITE_TEMPS_MS}, {20, UNITE_TEMPS_MS}, {70, UNITE_TEMPS_MS}, {69, UNITE_TEMPS_MS}, {20, UNITE_TEMPS_MS},
    {67, UNITE_TEMPS_MS}, {76, UNITE_TEMPS_MS}, {79, UNITE_TEMPS_MS}, {81, UNITE_TEMPS_MS}, {20, UNITE_TEMPS_MS},
    {77, UNITE_TEMPS_MS}, {79, UNITE_TEMPS_MS}, {20, UNITE_TEMPS_MS}, {76, UNITE_TEMPS_MS}, {20, UNITE_TEMPS_MS},
    {72, UNITE_TEMPS_MS}, {74, UNITE_TEMPS_MS}, {71, UNITE_TEMPS_MS}, {20, UNITE_TEMPS_MS}, {72, UNITE_TEMPS_MS},
    {20, UNITE_TEMPS_MS}, {67, UNITE_TEMPS_MS}, {20, UNITE_TEMPS_MS}, {64, UNITE_TEMPS_MS}, {20, UNITE_TEMPS_MS},
    {69, UNITE_TEMPS_MS}, {20, UNITE_TEMPS_MS}, {71, UNITE_TEMPS_MS}, {20, UNITE_TEMPS_MS}, {70, UNITE_TEMPS_MS},
    {69, UNITE_TEMPS_MS}, {20, UNITE_TEMPS_MS}, {67, UNITE_TEMPS_MS}, {76, UNITE_TEMPS_MS}, {79, UNITE_TEMPS_MS},
    {81, UNITE_TEMPS_MS}, {20, UNITE_TEMPS_MS}, {77, UNITE_TEMPS_MS}, {79, UNITE_TEMPS_MS}, {20, UNITE_TEMPS_MS},
    {76, UNITE_TEMPS_MS}, {20, UNITE_TEMPS_MS}, {72, UNITE_TEMPS_MS}, {74, UNITE_TEMPS_MS}, {71, UNITE_TEMPS_MS},
    {20, UNITE_TEMPS_MS}
};
/*
const uint16_t Chanson::NOMBRE_NOTES_CHANSON = 41;
const NoteChanson Chanson::NOTES_CHANSON[] = {
    {98, UNITE_TEMPS_MS}, {0, UNITE_TEMPS_MS}, {98, UNITE_TEMPS_MS}, {0, UNITE_TEMPS_MS}, {62, UNITE_TEMPS_MS},
    {0, UNITE_TEMPS_MS}, {98, UNITE_TEMPS_MS}, {0, UNITE_TEMPS_MS}, {122, UNITE_TEMPS_MS}, {0, UNITE_TEMPS_MS},
    {74, UNITE_TEMPS_MS}, {0, UNITE_TEMPS_MS}, {98, UNITE_TEMPS_MS}, {0, UNITE_TEMPS_MS}, {62, UNITE_TEMPS_MS},
    {0, UNITE_TEMPS_MS}, {105, UNITE_TEMPS_MS}, {0, UNITE_TEMPS_MS}, {98, UNITE_TEMPS_MS}, {0, UNITE_TEMPS_MS},
    {98, UNITE_TEMPS_MS}, {0, UNITE_TEMPS_MS}, {62, UNITE_TEMPS_MS}, {0, UNITE_TEMPS_MS}, {81, UNITE_TEMPS_MS},
    {0, UNITE_TEMPS_MS}, {122, UNITE_TEMPS_MS}, {0, UNITE_TEMPS_MS}, {122, UNITE_TEMPS_MS}, {0, UNITE_TEMPS_MS},
    {74, UNITE_TEMPS_MS}, {0, UNITE_TEMPS_MS}, {122, UNITE_TEMPS_MS}, {0, UNITE_TEMPS_MS}, {0, UNITE_TEMPS_MS},
    {98, UNITE_TEMPS_MS}, {0, UNITE_TEMPS_MS}, {98, UNITE_TEMPS_MS}, {91, UNITE_TEMPS_MS}, {0, UNITE_TEMPS_MS},
    {103, UNITE_TEMPS_MS}
};
*/

/**
 * Callback pour les notes de la chanson
 * \todo typedef pour pointeur vers methode de classe
 */
void callbackNoteChanson()
{
    // si la chanson n'est pas finie
    if(Chanson::compteurNotesChanson < Chanson::NOMBRE_NOTES_CHANSON)
    {
        // recupere la note
        NoteChanson note = Chanson::NOTES_CHANSON[Chanson::compteurNotesChanson];
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
            Chanson::compteurMsNote = Chanson::NOTES_CHANSON[Chanson::compteurNotesChanson].duree;
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
    initTimer0(&callbackNoteChanson, nullptr);

    // selectionne un prescaler de 1024
    /// \todo integre avec NoteMusicale
    setPrescalerTimer0(Prescaler::PRE_1024);
}

void Chanson::play()
{
    // reinitialise compteur de notes
    compteurNotesChanson = 0;

    // initialise le compteur de temps pour la premiere note
    compteurMsNote = NOTES_CHANSON[compteurNotesChanson].duree;

    // part le timer pour la note
    startTimer0();
}

void Chanson::playNote(uint8_t noteMidi, uint8_t duree)
{
    // joue la note
    Buzzer::play(noteMidi);

    // regle le timer pour la note
    setOCRnATimer0FromMs(duree);
}

void Chanson::pause()
{
    Buzzer::stop();
    stopTimer0();
}

void Chanson::stop()
{
    pause();
    compteurNotesChanson = 0;
    Debug::out("chanson stop\n");
}

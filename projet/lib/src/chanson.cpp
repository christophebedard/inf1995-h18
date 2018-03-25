/**
 * \file chanson.cpp
 * \brief implementation de la classe Chanson
 * \author 
 */

#include "chanson.h"

uint16_t Chanson::compteurNotesChanson = 0;
const uint16_t Chanson::NOMBRE_NOTES_CHANSON = 66;
const NoteChanson Chanson::NOTES_CHANSON[] = {
    {70, 12}, {71, 12}, {20, 12}, {76, 12}, {20, 12}, {72, 12}, {76, 12}, {20, 12}, {79, 12}, {20, 36}, {67, 12}, {20, 36},
    {72, 12}, {20, 24}, {67, 12}, {20, 24}, {64, 12}, {20, 24}, {69, 12}, {20, 12}, {71, 12}, {20, 12}, {70, 12}, {69, 12}, {20, 12}, {67, 16}, {76, 16}, {79, 16}, {81, 12}, {20, 12}, {77, 12}, {79, 12}, {20, 12}, {76, 12}, {20, 12}, {72, 12}, {74, 12}, {71, 128}, {20, 24},
    {72, 12}, {20, 24}, {67, 12}, {20, 24}, {64, 12}, {20, 24}, {69, 12}, {20, 12}, {71, 12}, {20, 12}, {70, 12}, {69, 12}, {20, 12}, {67, 16}, {76, 16}, {79, 16}, {81, 12}, {20, 12}, {77, 12}, {79, 12}, {20, 12}, {76, 12}, {20, 12}, {72, 12}, {74, 12}, {71, 128}, {20, 24}
}; /// \todo

/**
 * Callback pour les notes de la chanson
 * \todo typedef pour pointeur vers methode de classe
 */
void callbackNoteChanson()
{
    // si la chanson n'est pas finie
    if(Chanson::compteurNotesChanson < Chanson::NOMBRE_NOTES_CHANSON)
    {
        NoteChanson note = Chanson::NOTES_CHANSON[Chanson::compteurNotesChanson];

        // joue la note
        Chanson::playNote(note);
        // incremente compteur
        Chanson::compteurNotesChanson++;
    }
    else
    {
        // chanson terminee
        Debug::out("chanson terminee\n");
        Chanson::stop();
    }
}

void test()
{
    Debug::out("b\n");
}

void Chanson::init()
{
    // initialise le buzzer
    Buzzer::init();

    // initialise le timer0
    initTimer0(&callbackNoteChanson, &test);
}

void Chanson::play()
{
    // selectionne un prescaler de 1024
    /// \todo integre avec NoteMusicale
    setPrescalerTimer0(Prescaler::PRE_1024);

    // part le timer pour la note
    startTimer0();
}

void Chanson::playNote(NoteChanson note)
{
    /*
    Debug::out("playNote() : note=");
    Debug::out(note.noteMidi);
    Debug::out(", duree=");
    Debug::out(note.duree);
    Debug::out("\n");
    */

    // joue la note
    Buzzer::play(note.noteMidi);

    // regle le timer pour la note
    setOCRnATimer0FromMs(note.duree);
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

/**
 * \file chanson.cpp
 * \brief implementation de la classe Chanson
 * \author 
 */

#include "chanson.h"

uint16_t Chanson::compteurNotesChanson = 0;
const uint16_t Chanson::NOMBRE_NOTES_CHANSON = 0; /// \todo
const NoteChanson Chanson::NOTES_CHANSON[] = {}; /// \todo

/**
 * Callback pour les notes de la chanson
 * \todo typedef pour pointeur vers methode de classe
 */
void callbackNoteChanson()
{
    // incremente note
    Chanson::compteurNotesChanson++;
    NoteChanson note = Chanson::NOTES_CHANSON[Chanson::compteurNotesChanson];

    // joue la nouvelle note
    Buzzer::play(note.noteMidi);

    // regle le timer pour la nouvelle note
    
}

void Chanson::init()
{
    Buzzer::init();

    initTimer0(&callbackNoteChanson, nullptr);
}

void Chanson::play()
{
    // joue la premiere note
    NoteChanson note = NOTES_CHANSON[compteurNotesChanson];
    Buzzer::play(note.noteMidi);

    // regle le timer
    //startTimer0();
    //setPrescalerTimer0(pre);
    //setOCRnATimer0(val_ocrn);
}

void Chanson::pause()
{
    stopTimer0();
}

void Chanson::stop()
{
    pause();
    compteurNotesChanson = 0;
}

#ifndef LIB_BUZZER_H
#define LIB_BUZZER_H

/**
 * \file buzzer.h
 * \brief declaration de la classe Buzzer
 * \author Christophe Bourque Bedard
 * \author Simon Moreau
 * \author Fares Ouaissa
 * \author Mohamed Saddik
 * 
 * Brancher le buzzer entre BROCHE_BUZZER et GND (port B)
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"
#include "broches.h"
#include "enums_structs.h"
#include "timer2.h"
#include "debug.h"

///< le numero de la note qui represente un silence
#define NOTE_NULLE 0
///< la note MIDI minimale valide
#define NOTE_MIN 12
///< la note MIDI maximale valide
#define NOTE_MAX 127

/**
 * \class Buzzer
 * \brief classe qui enveloppe (wrap) le Buzzer
 */
class Buzzer
{
public:
    /**
     * Initialisation du buzzer
     */
    static void init();

    /**
     * Lecture d'une note avec le buzzer
     *
     * \param note : la note MIDI a jouer
     */
    static void play(uint8_t note);

    /**
     * Arret de lecture de la note avec buzzer
     */
    static void stop();

    /**
     * Callback pour la note
     * \todo typedef pour pointeur vers methode de classe
     */
    friend void callbackNote();

private:
    static const NoteMidi DATA_NOTES[]; ///< les informations pour les notes (prescaler et valeur de OCRn)

};

#endif // LIB_BUZZER_H

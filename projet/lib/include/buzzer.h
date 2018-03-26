#ifndef LIB_BUZZER_H
#define LIB_BUZZER_H

/**
 * \file buzzer.h
 * \brief declaration de la classe Buzzer
 * \author 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"
#include "broches.h"
#include "enums.h"

#include "timer2.h"
#include "debug.h"


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

    static const uint8_t NOTE_NULLE; /**< le numero de la note qui represente un silence */

private:
    static const uint8_t NOTE_MIN; /**< la note MIDI minimale valide */
    static const uint8_t NOTE_MAX; /**< la note MIDI maximale valide */
    static const NoteMidi DATA_NOTES[]; /**< les informations pour les notes (prescaler et valeur de OCRn) */

};

#endif // LIB_BUZZER_H

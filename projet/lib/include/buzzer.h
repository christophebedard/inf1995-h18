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
#include "minuterie.h"
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
    static void play(uint16_t note);

    /**
     * Arret de lecture de la note avec buzzer
     */
    static void stop();

    static const uint8_t BROCHE_BUZZER; /**< la broche sur laquelle le buzzer est connecte (1-8) */

    static const uint16_t DEMI_PERIODES[]; /**< les periodes des notes */

private:
    static const uint16_t NOTE_MIN; /**< la note MIDI minimale valide */
    static const uint16_t NOTE_MAX; /**< la note MIDI maximale valide */
    //static const uint16_t DEMI_PERIODES[]; /**< les periodes des notes */

    /**
     * Recuperation de la demi periode selon la note
     * 
     * \param note : la note
     * 
     * \return la periode en microsecondes (us)
     */
    static uint16_t getDemiPeriode(uint16_t note);

};

#endif // LIB_BUZZER_H

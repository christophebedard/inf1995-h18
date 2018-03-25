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
 * Definition d'une note MIDI
 */
struct NoteMidi
{
    Prescaler pre; /**< la valeur du prescaler pour la note */
    uint8_t val_ocrn; /**< la valeur de OCRn pour la note */
};

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

    static const uint8_t BROCHE_BUZZER; /**< la broche sur laquelle le buzzer est connecte (1-8) */
    static const uint8_t NOTE_NULLE; /**< le numero de la note qui represente un silence */

private:
    static const uint8_t NOTE_MIN; /**< la note MIDI minimale valide */
    static const uint8_t NOTE_MAX; /**< la note MIDI maximale valide */
    static const NoteMidi DATA_NOTES[]; /**< les informations pour les notes (prescaler et valeur de OCRn) */

};

#endif // LIB_BUZZER_H

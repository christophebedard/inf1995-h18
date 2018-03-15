#ifndef LIB_BUZZER_H
#define LIB_BUZZER_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"
#include "minuterie.h"


class Buzzer
{
public:

    /**
     * Constructeur
     */
    Buzzer();

    /**
     * Destructeur
     */
    ~Buzzer();

    /**
     * Lecture d'une note avec le buzzer
     *
     * \param note : la note MIDI a jouer
     */
    void playNote(uint8_t note);

    /**
     * Arret de lecture de la note avec buzzer
     */
    void stopNote();

    static const uint8_t BROCHE_BUZZER; /**< la broche sur laquelle le buzzer est connecte (1-8) */

private:
    static const uint8_t NOTE_MIN; /**< la note MIDI minimale valide */
    static const uint8_t NOTE_MAX; /**< la note MIDI maximale valide */
    static const uint16_t PERIODES[]; /**< les periodes des notes */

    /**
     * Initialisation du buzzer
     */
    void init();

    /**
     * Recuperation de la periode selon la note
     * 
     * \param note : la note
     * 
     * \return la periode en microsecondes (us)
     */
    uint16_t getPeriode(uint8_t note);

    /**
     * Callback pour la note
     * \todo typedef pour pointeur vers methode de classe
     */
    //void callbackNote();
};

#endif // LIB_BUZZER_H

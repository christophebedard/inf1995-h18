/**
 * \file buzzer.cpp
 * \brief implementation de la classe Buzzer
 * \author 
 * 
 * Brancher le buzzer entre la broche BROCHE_BUZZER et le GND.
 */

#include "buzzer.h"


const uint8_t Buzzer::BROCHE_BUZZER = 7; /**< la broche [1,8] du buzzer */
const uint8_t Buzzer::NOTE_MIN = 45; /**< le numero de la note minimale supportee (premiere dans le tableau) */
const uint8_t Buzzer::NOTE_MAX = 81; /**< le numero de la note maximale supportee (derniere dans le tableau) */
const uint16_t Buzzer::PERIODES[] = {9090, 8580, 8090, 7644, 7215, 6810, 6428, 6067, 5726, 5405,
                                     5102, 4815, 4545, 4290, 4049, 3822, 3607, 3405, 3214, 3033,
                                     2863, 2702, 2551, 2407, 2272, 2145, 2024, 1911, 1803, 1702,
                                     1607, 1516, 1431, 1351, 1275, 1203, 1136}; /**< les valeurs des periodes en us (1 ms / 1000) */

/**
 * Callback pour la note
 * \todo typedef pour pointeur vers methode de classe
 */
void callbackNote()
{
    PORTB ^= _BV(Buzzer::BROCHE_BUZZER - 1);
}

void Buzzer::init()
{
    DDRB |= _BV(Buzzer::BROCHE_BUZZER - 1);
    initMinuterie2(&callbackNote);
}

void Buzzer::play(uint8_t note)
{
    startMinuterie2(note);
}

void Buzzer::stop()
{
    stopMinuterie2();
}

uint16_t Buzzer::getPeriode(uint8_t note)
{
    if (NOTE_MIN <= note && note <= NOTE_MAX)
    {
        return PERIODES[note - NOTE_MIN] / 1000;
    }
    else
    {
        return PERIODES[NOTE_MIN] / 1000;
    }
}

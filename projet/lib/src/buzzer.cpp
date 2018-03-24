/**
 * \file buzzer.cpp
 * \brief implementation de la classe Buzzer
 * \author 
 * 
 * Brancher le buzzer entre la broche BROCHE_BUZZER et le GND.
 */

#include "buzzer.h"


const uint8_t Buzzer::BROCHE_BUZZER = 7;
const uint16_t Buzzer::NOTE_MIN = 45;
const uint16_t Buzzer::NOTE_MAX = 81;
const uint16_t Buzzer::DEMI_PERIODES[37] = {4545, 4290, 4049, 3822, 3607, 3405, 3214, 3033, 2863, 2702,
                                            2551, 2408, 2272, 2145, 2024, 1911, 1803, 1702, 1607, 1516,
                                            1431, 1351, 1275, 1203, 1136, 1072, 1012,  955,  901,  851,
                                             803,  758,  715,  675,  637,  601,  568};

/**
 * Callback pour la note
 * \todo typedef pour pointeur vers methode de classe
 */
void callbackNote()
{
    PORTC ^= _BV(Buzzer::BROCHE_BUZZER - 1);
}

void Buzzer::init()
{
    DDRC |= _BV(Buzzer::BROCHE_BUZZER - 1);
    initTimer2(&callbackNote);
}

void Buzzer::play(uint16_t note)
{
    //startTimer2(getDemiPeriode(note));
    uint16_t demiPeriode = getDemiPeriode(note);
    
    Debug::out("\tdemi periode : ");
    Debug::out(demiPeriode);
    Debug::out("\n");

    startTimer2(demiPeriode);
}

void Buzzer::stop()
{
    stopTimer2();
}

uint16_t Buzzer::getDemiPeriode(uint16_t note)
{
    uint16_t val = DEMI_PERIODES[NOTE_MIN];
    
    if (NOTE_MIN <= note && note <= NOTE_MAX)
    {
        val = DEMI_PERIODES[note - NOTE_MIN];
    }
    
    Debug::out("\t\tnote : ");
    Debug::out(note);
    Debug::out("; demi periode : ");
    Debug::out(val);
    Debug::out("\n");

    return val;
}

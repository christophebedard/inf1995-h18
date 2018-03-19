#include "buzzer.h"

const uint8_t Buzzer::BROCHE_BUZZER = 7;
const uint8_t Buzzer::NOTE_MIN = 45;
const uint8_t Buzzer::NOTE_MAX = 81;
const uint16_t Buzzer::PERIODES[] = {9090, 8580, 8090, 7644, 7215, 6810, 6428, 6067, 5726, 5405,
                                     5102, 4815, 4545, 4290, 4049, 3822, 3607, 3405, 3214, 3033,
                                     2863, 2702, 2551, 2407, 2272, 2145, 2024, 1911, 1803, 1702,
                                     1607, 1516, 1431, 1351, 1275, 1203, 1136};

void callbackNote()
{
    PORTB ^= _BV(Buzzer::BROCHE_BUZZER - 1);
}

void Buzzer::init()
{
    DDRB |= _BV(Buzzer::BROCHE_BUZZER - 1);
    initMinuterie(&callbackNote);
}

void Buzzer::play(uint8_t note)
{
    startMinuterie(note);
}

void Buzzer::stop()
{
    stopMinuterie();
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
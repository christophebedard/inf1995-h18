#include "minuterie.h"

void initMinuterie()
{
    // mode CTC du timer 1 avec horloge divisee par 1024
	// interruption apres la duree spécifiee
    TCCR1A |= (1 << COM1A1) | (1 << COM1A0);
    // CTC et clk/1024
    TCCR1B |= (1 << WGM12)  | (1 << CS12) | (1 << CS10);
    TCCR1C = 0;
    TIMSK1 |= (1 << OCIE1A);
}

void startMinuterie(const uint16_t duree)
{
    TCNT1 = 0;
    OCR1A = duree * (F_CPU / 1024);
}

void stopMinuterie()
{
    OCR1A = 0;
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 = 0;
}

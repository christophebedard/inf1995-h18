#include "minuterie.h"

func_t timer1FuncPtr = nullptr; /**< variable du pointeur vers le callback TIMER1 */

ISR(TIMER1_COMPA_vect)
{
    /// \todo assert != nullptr
    timer1FuncPtr();
}

void initMinuterie(func_t func)
{
    cli();

    // interruption externe sur INT0, rising ou falling edge
    /// \todo minuterie semble pas fonctionner sans ces deux lignes-la si initInterruption() n'est pas appele
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);

    // garde en memoire le pointeur vers la fonction de callback
    timer1FuncPtr = func;

    TCNT1 = 0;
    // mode CTC du timer 1 avec horloge divisee par 1024
	// interruption apres la duree spécifiee
    TCCR1A |= (1 << COM1A1) | (1 << COM1A0);
    // CTC et clk/1024
    TCCR1B |= (1 << WGM12)  | (1 << CS12) | (1 << CS10);
    TCCR1C = 0;
    TIMSK1 |= (1 << OCIE1A);

    sei();
}

void startMinuterie(const uint16_t duree)
{
    TCNT1 = 0;
    /// \todo verifier si c'est la bonne formule (le temps ne semble pas etre exact)
    OCR1A = duree * (F_CPU / 1024);
}

void stopMinuterie()
{
    OCR1A = 0;
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 = 0;
}

#include "minuterie.h"

func_t timer1FuncPtr = nullptr; /**< variable du pointeur vers le callback TIMER1 */
func_t timer2FuncPtr = nullptr; /**< variable du pointeur vers le callback TIMER2 */

ISR(TIMER1_COMPA_vect)
{
    if (timer1FuncPtr != nullptr) timer1FuncPtr();
}

ISR(TIMER2_COMPA_vect)
{
    if (timer2FuncPtr != nullptr) timer2FuncPtr();
}

void initTimer1(func_t func)
{
    cli();

    // interruption externe sur INT0, rising ou falling edge
    /// \todo minuterie semble pas fonctionner sans ces deux lignes-la si initInterruption() n'est pas appele
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);

    // garde en memoire le pointeur vers la fonction de callback
    timer1FuncPtr = func;

    TCNT1 = 0;
    // mode CTC du timer 1 avec horloge divisee par 128
	// interruption apres la duree spécifiee
    TCCR1A |= (1 << COM1A1) | (1 << COM1A0);
    // CTC et clk/1024
    TCCR1B |= (1 << WGM12)  | (1 << CS12) | (1 << CS10);
    TCCR1C = 0;
    TIMSK1 |= (1 << OCIE1A);
    
    sei();
}

void initTimer2(func_t func)
{
    cli();

    // garde en memoire le pointeur vers la fonction de callback
    timer2FuncPtr = func;

    startTimer2();
    
    sei();
}

void startTimer1(const uint16_t duree)
{
    TCNT1 = 0;
    /// \todo verifier si c'est la bonne formule (le temps ne semble pas etre exact)
    OCR1A = (duree * F_CPU) / 128;
}

void startTimer2()
{
    TCNT2 = 0;
    // mode CTC du timer 1 avec horloge divisee par 128
	// interruption apres la duree spécifiee
    TCCR2A |= (1 << COM2A1) | (1 << COM2A0);
    // CTC et clk/1024
    TCCR2B |= (1 << WGM21)  | (1 << CS22) | (1 << CS20);
    TIMSK2 |= (1 << OCIE2A);
}

void setOCRnATimer2(const uint8_t& val_ocrn)
{
    TCNT2 = 0;
    OCR2A = val_ocrn;
}

void setOCRnBTimer2(const uint8_t& val_ocrn)
{
    TCNT2 = 0;
    OCR2B = val_ocrn;
}

void setPrescalerTimer2(const Prescaler& pre)
{
    TCCR2B &= ~(_BV(CS22) | _BV(CS21) | _BV(CS20));
    switch(pre)
    {
        case Prescaler::PRE_1:
            TCCR2B |= _BV(CS20);
            break;
        case Prescaler::PRE_8:
            TCCR2B |= _BV(CS21);
            break;
        case Prescaler::PRE_32:
            TCCR2B |= _BV(CS21) | _BV(CS20);
            break;
        case Prescaler::PRE_64:
            TCCR2B |= _BV(CS22);
            break;
        default:
        case Prescaler::PRE_128:
            TCCR2B |= _BV(CS22) | _BV(CS20);
            break;
        case Prescaler::PRE_256:
            TCCR2B |= _BV(CS22) | _BV(CS21);
            break;
        case Prescaler::PRE_1024:
            TCCR2B |= _BV(CS22) | _BV(CS21) | _BV(CS20);
            break;
    }
}

void stopTimer1()
{
    OCR1A = 0;
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 = 0;
}

void stopTimer2()
{
    OCR2A = 0;
    TCCR2A &= ~((1 << COM2A1) | (1 << COM2A0));
    TCCR2B &= ~((1 << WGM21)  | (1 << CS22) | (1 << CS20));
    TIMSK2 &= ~(1 << OCIE2A);
}

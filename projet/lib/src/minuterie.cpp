/**
 * \file minuterie.cpp
 * \brief implementation des fonctions pour la minuterie
 * \author 
 */

#include "minuterie.h"


func_t timer0AFuncPtr = nullptr; /**< variable du pointeur vers le callback TIMER0 A */
func_t timer0BFuncPtr = nullptr; /**< variable du pointeur vers le callback TIMER0 B */
func_t timer1FuncPtr = nullptr; /**< variable du pointeur vers le callback TIMER1 */
func_t timer2AFuncPtr = nullptr; /**< variable du pointeur vers le callback TIMER2 A */
func_t timer2BFuncPtr = nullptr; /**< variable du pointeur vers le callback TIMER2 B */

ISR(TIMER0_COMPA_vect)
{
    if (timer0AFuncPtr != nullptr) timer0AFuncPtr();
}

ISR(TIMER0_COMPB_vect)
{
    if (timer0BFuncPtr != nullptr) timer0BFuncPtr();
}

ISR(TIMER1_COMPA_vect)
{
    if (timer1FuncPtr != nullptr) timer1FuncPtr();
}

ISR(TIMER2_COMPA_vect)
{
    if (timer2AFuncPtr != nullptr) timer2AFuncPtr();
}

ISR(TIMER2_COMPB_vect)
{
    if (timer2BFuncPtr != nullptr) timer2BFuncPtr();
}

void initTimer0(func_t funcA, func_t funcB)
{
    // garde en memoire les pointeurs vers les fonction de callback
    timer0AFuncPtr = funcA;
    timer0BFuncPtr = funcB;
}

void initTimer1(func_t func)
{
    // interruption externe sur INT0, rising ou falling edge
    /// \todo minuterie semble pas fonctionner sans ces deux lignes-la si initInterruption() n'est pas appele
    EIMSK |= _BV(INT0);
    EICRA |= _BV(ISC00);

    // garde en memoire le pointeur vers la fonction de callback
    timer1FuncPtr = func;
}

void initTimer2(func_t funcA, func_t funcB)
{
    // garde en memoire les pointeurs vers les fonction de callback
    timer2AFuncPtr = funcA;
    timer2BFuncPtr = funcB;
}

void startTimer1(const uint16_t duree)
{
    TCNT1 = 0;
    /// \todo verifier si c'est la bonne formule (le temps ne semble pas etre exact)
    OCR1A = (duree * F_CPU) / 128;
}

void startTimer0()
{
    cli();

    TCNT0 = 0;

    // mode CTC
    TCCR0A |= _BV(WGM01);
	// interruption apres la duree spécifiee sur OC0A
    TCCR0A |= _BV(COM0A1) | _BV(COM0A0);
    // interruption apres la duree spécifiee sur OC0B
    //TCCR0A |= _BV(COM0B1) | _BV(COM0B0);
    // clk/1024
    TCCR0B |= _BV(CS02) | _BV(CS00);
    // active A [et B]
    TIMSK0 |= _BV(OCIE0A);// | _BV(OCIE0B);

    sei();
}

void startTimer1()
{
    cli();

    TCNT1 = 0;

    // mode CTC du timer 1 avec horloge divisee par 128
	// interruption apres la duree spécifiee
    TCCR1A |= _BV(COM1A1) | _BV(COM1A0);
    // CTC et clk/1024
    TCCR1B |= _BV(WGM12) | _BV(CS12) | _BV(CS10);
    TCCR1C = 0;
    // active A
    TIMSK1 |= _BV(OCIE1A);

    sei();
}

void startTimer2()
{
    cli();

    TCNT2 = 0;

    // mode CTC du timer 2 avec horloge divisee par 128
	// interruption apres la duree spécifiee
    TCCR2A |= _BV(COM2A1) | _BV(COM2A0);
    // CTC et clk/1024
    TCCR2B |= _BV(WGM21)  | _BV(CS22) | _BV(CS20);
    // active A et B
    TIMSK2 |= _BV(OCIE2A) | _BV(OCIE2B);

    sei();
}

void setOCRnATimer0FromMs(const uint8_t& ms)
{
    TCNT0 = 0;
    OCR0A = (ms * (F_CPU / 1000)) / 1024;
}

void setOCRnATimer0(const uint8_t& val_ocrn)
{
    TCNT0 = 0;
    OCR0A = val_ocrn;
}

void setOCRnBTimer0(const uint8_t& val_ocrn)
{
    TCNT0 = 0;
    OCR0B = val_ocrn;
}

void setOCRnATimer1(const uint16_t& val_ocrn)
{
    TCNT1 = 0;
    OCR1A = val_ocrn;
}

void setOCRnBTimer1(const uint16_t& val_ocrn)
{
    TCNT1 = 0;
    OCR1A = val_ocrn;
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

void setPrescalerTimer0(const Prescaler& pre)
{
    TCCR0B &= ~(_BV(CS02) | _BV(CS01) | _BV(CS00));
    switch(pre)
    {
        case Prescaler::Pres_1:
            TCCR0B |= _BV(CS00);
            break;
        case Prescaler::Pres_8:
            TCCR0B |= _BV(CS01);
            break;
        case Prescaler::Pres_64:
            TCCR0B |= _BV(CS01) | _BV(CS00);
            break;
        default:
        case Prescaler::Pres_256:
            TCCR0B |= _BV(CS02);
            break;
        case Prescaler::Pres_1024:
            TCCR0B |= _BV(CS02) | _BV(CS00);
            break;
    }
}

void setPrescalerTimer1(const Prescaler& pre)
{
    TCCR1B &= ~(_BV(CS12) | _BV(CS11) | _BV(CS10));
    switch(pre)
    {
        case Prescaler::Pres_1:
            TCCR0B |= _BV(CS10);
            break;
        case Prescaler::Pres_8:
            TCCR0B |= _BV(CS11);
            break;
        case Prescaler::Pres_64:
            TCCR0B |= _BV(CS11) | _BV(CS10);
            break;
        default:
        case Prescaler::Pres_256:
            TCCR0B |= _BV(CS12);
            break;
        case Prescaler::Pres_1024:
            TCCR0B |= _BV(CS12) | _BV(CS10);
            break;
    }
}

void setPrescalerTimer2(const Prescaler& pre)
{
    TCCR2B &= ~(_BV(CS22) | _BV(CS21) | _BV(CS20));
    switch(pre)
    {
        case Prescaler::Pres_1:
            TCCR2B |= _BV(CS20);
            break;
        case Prescaler::Pres_8:
            TCCR2B |= _BV(CS21);
            break;
        case Prescaler::Pres_32:
            TCCR2B |= _BV(CS21) | _BV(CS20);
            break;
        case Prescaler::Pres_64:
            TCCR2B |= _BV(CS22);
            break;
        default:
        case Prescaler::Pres_128:
            TCCR2B |= _BV(CS22) | _BV(CS20);
            break;
        case Prescaler::Pres_256:
            TCCR2B |= _BV(CS22) | _BV(CS21);
            break;
        case Prescaler::Pres_1024:
            TCCR2B |= _BV(CS22) | _BV(CS21) | _BV(CS20);
            break;
    }
}

void stopTimer0()
{
    OCR0A = 0;
    OCR0B = 0;
    TCCR0A &= ~(_BV(WGM01) | _BV(COM0A1) | _BV(COM0A0) | _BV(COM0B1) | _BV(COM0B0));
    TCCR0B &= ~(_BV(CS02) | _BV(CS00));
    TIMSK0 &= ~(_BV(OCIE0A) | _BV(OCIE0B));
}

void stopTimer1()
{
    OCR1A = 0;
    OCR1B = 0;
    TCCR1A &= ~(_BV(COM1A1) | _BV(COM1A0));
    TCCR1B &= ~(_BV(WGM12)  | _BV(CS12) | _BV(CS10));
    TIMSK1 &= ~(_BV(OCIE1A));
}

void stopTimer2()
{
    OCR2A = 0;
    OCR2B = 0;
    TCCR2A &= ~(_BV(COM2A1) | _BV(COM2A0));
    TCCR2B &= ~(_BV(WGM21)  | _BV(CS22) | _BV(CS20));
    TIMSK2 &= ~_BV(OCIE2A);
}

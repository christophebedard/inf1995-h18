/**
 * \file timer1.cpp
 * \brief implementation de la classe Timer1
 * \author 
 */

#include "timer1.h"

/// \todo deplacer vers classe static
func_t timer1CompACallback = nullptr; ///< le pointeur vers la fonction de callback pour TIMER1_COMPA
func_t timer1CompBCallback = nullptr; ///< le pointeur vers la fonction de callback pour TIMER1_COMPB

Prescaler Timer1::timPres = Prescaler::Pres_no_clk;

ISR(TIMER1_COMPA_vect)
{
    if (timer1CompACallback != nullptr) timer1CompACallback();
}

ISR(TIMER1_COMPB_vect)
{
    if (timer1CompBCallback != nullptr) timer1CompBCallback();
}

void Timer1::start()
{
    cli();

    resetTCNTn();
    setWaveformGenerationMode(WGM::WGM_4);
    setCompareOutputMode(COM::COM_set, COM::COM_normal);
    setInterruptEnable(true, false);
    setPrescaler(Prescaler::Pres_1024);
    
    sei();
}

void Timer1::stop()
{
    setOCRnA(0);
    setOCRnB(0);
    resetTCNTn();
    setWaveformGenerationMode(WGM::WGM_0);
    setCompareOutputMode(COM::COM_normal, COM::COM_normal);
    setInterruptEnable(0, 0);
    setPrescaler(Prescaler::Pres_no_clk);
}

void Timer1::setCompareOutputMode(COM a, COM b)
{
    TCCR1A &= ~(_BV(COM1A1) | _BV(COM1A0) | _BV(COM1B1) | _BV(COM1B0));

    switch(a)
    {
        default:
        case COM::COM_normal:
            //TCCR1A |= 0;
            break;
        case COM::COM_toggle:
            TCCR1A |= _BV(COM1A0);
            break;
        case COM::COM_clear:
            TCCR1A |= _BV(COM1A1);
            break;
        case COM::COM_set:
            TCCR1A |= _BV(COM1A1) | _BV(COM1A0);
            break;
    }

    switch(b)
    {
        default:
        case COM::COM_normal:
            //TCCR1A |= 0;
            break;
        case COM::COM_toggle:
            TCCR1A |= _BV(COM1B0);
            break;
        case COM::COM_clear:
            TCCR1A |= _BV(COM1B1);
            break;
        case COM::COM_set:
            TCCR1A |= _BV(COM1B1) | _BV(COM1B0);
            break;
    }
}

void Timer1::setWaveformGenerationMode(WGM mode)
{
    TCCR1A &= ~(_BV(WGM11) | _BV(WGM10));
    TCCR1B &= ~(_BV(WGM12));

    switch(mode)
    {
        default:
        case WGM::WGM_0:
            //TCCR1A |= 0;
            //TCCR1B |= 0;
            break;
        case WGM::WGM_1:
            TCCR1A |= _BV(WGM10);
            break;
        case WGM::WGM_2:
            TCCR1A |= _BV(WGM11);
            break;
        case WGM::WGM_3:
            TCCR1A |= _BV(WGM11) | _BV(WGM10);
            break;
        case WGM::WGM_4:
            TCCR1B |= _BV(WGM12);
            break;
        case WGM::WGM_5:
            TCCR1A |= _BV(WGM10);
            TCCR1B |= _BV(WGM12);
            break;
        case WGM::WGM_6:
            TCCR1A |= _BV(WGM11);
            TCCR1B |= _BV(WGM12);
            break;
        case WGM::WGM_7:
            TCCR1A |= _BV(WGM11) | _BV(WGM10);
            TCCR1B |= _BV(WGM12);
            break;
        case WGM::WGM_8:
            //TCCR1A |= 0;
            TCCR1B |= _BV(WGM13);
            break;
        case WGM::WGM_9:
            TCCR1A |= _BV(WGM10);
            TCCR1B |= _BV(WGM13);
            break;
        case WGM::WGM_10:
            TCCR1A |= _BV(WGM11);
            TCCR1B |= _BV(WGM13);
            break;
        case WGM::WGM_11:
            TCCR1A |= _BV(WGM11) | _BV(WGM10);
            TCCR1B |= _BV(WGM13);
            break;
        case WGM::WGM_12:
            TCCR1B |= _BV(WGM12);
            TCCR1B |= _BV(WGM13);
            break;
        case WGM::WGM_13:
            TCCR1A |= _BV(WGM10);
            TCCR1B |= _BV(WGM13) | _BV(WGM12);
            break;
        case WGM::WGM_14:
            TCCR1A |= _BV(WGM11);
            TCCR1B |= _BV(WGM13) | _BV(WGM12);
            break;
        case WGM::WGM_15:
            TCCR1A |= _BV(WGM11) | _BV(WGM10);
            TCCR1B |= _BV(WGM13) | _BV(WGM12);
            break;
    }
}

void Timer1::setPrescaler(const Prescaler pre)
{
    timPres = pre;

    TCCR1B &= ~(_BV(CS12) | _BV(CS11) | _BV(CS10));

    switch(pre)
    {
        default:
        case Prescaler::Pres_no_clk:
            //TCCR1B |= 0;
            break;
        case Prescaler::Pres_1:
            TCCR1B |= _BV(CS10);
            break;
        case Prescaler::Pres_8:
            TCCR1B |= _BV(CS11);
            break;
        case Prescaler::Pres_64:
            TCCR1B |= _BV(CS11) | _BV(CS10);
            break;
        case Prescaler::Pres_256:
            TCCR1B |= _BV(CS12);
            break;
        case Prescaler::Pres_1024:
            TCCR1B |= _BV(CS12) | _BV(CS10);
            break;
        case Prescaler::Pres_ext_falling:
            TCCR1B |= _BV(CS12) | _BV(CS11);
            break;
        case Prescaler::Pres_ext_rising:
            TCCR1B |= _BV(CS12) | _BV(CS11) | _BV(CS10);
            break;
    }
}

void Timer1::setInterruptEnable(bool a, bool b)
{
    TIMSK1 &= ~(_BV(OCIE1A) | _BV(OCIE1B));

    switch(a)
    {
        default:
        case false:
            //TIMSK1 |= 0;
            break;
        case true:
            TIMSK1 |= _BV(OCIE1A);
            break;
    }

    switch(b)
    {
        default:
        case false:
            //TIMSK1 |= 0;
            break;
        case true:
            TIMSK1 |= _BV(OCIE1B);
            break;
    }
}

void Timer1::setOCRnA(uint16_t val)
{
    OCR1A = val;
}

void Timer1::setOCRnB(uint16_t val)
{
    OCR1B = val;
}

void Timer1::setCompACallback(func_t func)
{
    timer1CompACallback = func;
}

void Timer1::setCompBCallback(func_t func)
{
    timer1CompBCallback = func;
}

void Timer1::resetTCNTn()
{
    TCNT1 = 0;
}
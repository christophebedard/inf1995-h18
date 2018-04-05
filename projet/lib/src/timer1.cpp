/**
 * \file timer1.cpp
 * \brief implementation de la classe Timer1
 * \author 
 */

#include "timer1.h"

func_t Timer1::timer1CompACallback = nullptr;
func_t Timer1::timer1CompBCallback = nullptr;
func_t Timer1::timer1OverflowCallback = nullptr;
Prescaler Timer1::timPres = Prescaler::No_clk;

ISR(TIMER1_COMPA_vect)
{
    if (Timer1::timer1CompACallback != nullptr) Timer1::timer1CompACallback();
}

ISR(TIMER1_COMPB_vect)
{
    if (Timer1::timer1CompBCallback != nullptr) Timer1::timer1CompBCallback();
}

ISR(TIMER1_OVF_vect)
{
    if (Timer1::timer1OverflowCallback != nullptr) Timer1::timer1OverflowCallback();
}

void Timer1::stop()
{
    cli();
    setOCRnA(0);
    setOCRnB(0);
    resetTCNTn();
    setWaveformGenerationMode(WGM::Mode_0);
    setCompareOutputMode(COM::Normal, COM::Normal);
    setInterruptEnable(false, false, false);
    setPrescaler(Prescaler::No_clk);
    sei();
}

void Timer1::setCompareOutputMode(COM a, COM b)
{
    TCCR1A &= ~(_BV(COM1A1) | _BV(COM1A0) | _BV(COM1B1) | _BV(COM1B0));

    switch(a)
    {
        default:
        case COM::Normal:
            //TCCR1A |= 0;
            break;
        case COM::Toggle:
            TCCR1A |= _BV(COM1A0);
            break;
        case COM::Clear:
            TCCR1A |= _BV(COM1A1);
            break;
        case COM::Set:
            TCCR1A |= _BV(COM1A1) | _BV(COM1A0);
            break;
    }

    switch(b)
    {
        default:
        case COM::Normal:
            //TCCR1A |= 0;
            break;
        case COM::Toggle:
            TCCR1A |= _BV(COM1B0);
            break;
        case COM::Clear:
            TCCR1A |= _BV(COM1B1);
            break;
        case COM::Set:
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
        case WGM::Mode_0:
            //TCCR1A |= 0;
            //TCCR1B |= 0;
            break;
        case WGM::Mode_1:
            TCCR1A |= _BV(WGM10);
            break;
        case WGM::Mode_2:
            TCCR1A |= _BV(WGM11);
            break;
        case WGM::Mode_3:
            TCCR1A |= _BV(WGM11) | _BV(WGM10);
            break;
        case WGM::Mode_4:
            TCCR1B |= _BV(WGM12);
            break;
        case WGM::Mode_5:
            TCCR1A |= _BV(WGM10);
            TCCR1B |= _BV(WGM12);
            break;
        case WGM::Mode_6:
            TCCR1A |= _BV(WGM11);
            TCCR1B |= _BV(WGM12);
            break;
        case WGM::Mode_7:
            TCCR1A |= _BV(WGM11) | _BV(WGM10);
            TCCR1B |= _BV(WGM12);
            break;
        case WGM::Mode_8:
            //TCCR1A |= 0;
            TCCR1B |= _BV(WGM13);
            break;
        case WGM::Mode_9:
            TCCR1A |= _BV(WGM10);
            TCCR1B |= _BV(WGM13);
            break;
        case WGM::Mode_10:
            TCCR1A |= _BV(WGM11);
            TCCR1B |= _BV(WGM13);
            break;
        case WGM::Mode_11:
            TCCR1A |= _BV(WGM11) | _BV(WGM10);
            TCCR1B |= _BV(WGM13);
            break;
        case WGM::Mode_12:
            TCCR1B |= _BV(WGM12);
            TCCR1B |= _BV(WGM13);
            break;
        case WGM::Mode_13:
            TCCR1A |= _BV(WGM10);
            TCCR1B |= _BV(WGM13) | _BV(WGM12);
            break;
        case WGM::Mode_14:
            TCCR1A |= _BV(WGM11);
            TCCR1B |= _BV(WGM13) | _BV(WGM12);
            break;
        case WGM::Mode_15:
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
        case Prescaler::No_clk:
            //TCCR1B |= 0;
            break;
        case Prescaler::Div_1:
            TCCR1B |= _BV(CS10);
            break;
        case Prescaler::Div_8:
            TCCR1B |= _BV(CS11);
            break;
        case Prescaler::Div_64:
            TCCR1B |= _BV(CS11) | _BV(CS10);
            break;
        case Prescaler::Div_256:
            TCCR1B |= _BV(CS12);
            break;
        case Prescaler::Div_1024:
            TCCR1B |= _BV(CS12) | _BV(CS10);
            break;
        case Prescaler::Ext_falling:
            TCCR1B |= _BV(CS12) | _BV(CS11);
            break;
        case Prescaler::Ext_rising:
            TCCR1B |= _BV(CS12) | _BV(CS11) | _BV(CS10);
            break;
    }
}

void Timer1::setInterruptEnable(bool a, bool b, bool overflow)
{
    TIMSK1 &= ~(_BV(OCIE1A) | _BV(OCIE1B) | _BV(TOIE1));

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

    switch(overflow)
    {
        default:
        case false:
            //TIMSK1 |= 0;
            break;
        case true:
            TIMSK1 |= _BV(TOIE1);
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

void Timer1::setOverflowCallback(func_t func)
{
    timer1OverflowCallback = func;
}

void Timer1::resetTCNTn()
{
    TCNT1 = 0;
}

/**
 * \file timer0.cpp
 * \brief implementation de la classe Timer0
 * \author Christophe Bourque Bedard
 * \author Simon Moreau
 * \author Fares Ouaissa
 * \author Mohamed Saddik
 */

#include "timer0.h"

func_t Timer0::timer0CompACallback = nullptr;
func_t Timer0::timer0CompBCallback = nullptr;
func_t Timer0::timer0OverflowCallback = nullptr;
Prescaler Timer0::timPres = Prescaler::No_clk;

ISR(TIMER0_COMPA_vect)
{
    if (Timer0::timer0CompACallback != nullptr) Timer0::timer0CompACallback();
}

ISR(TIMER0_COMPB_vect)
{
    if (Timer0::timer0CompBCallback != nullptr) Timer0::timer0CompBCallback();
}

ISR(TIMER0_OVF_vect)
{
    if (Timer0::timer0OverflowCallback != nullptr) Timer0::timer0OverflowCallback();
}

void Timer0::stop()
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

void Timer0::setCompareOutputMode(COM a, COM b)
{
    TCCR0A &= ~(_BV(COM0A1) | _BV(COM0A0) | _BV(COM0B1) | _BV(COM0B0));

    switch(a)
    {
        default:
        case COM::Normal:
            //TCCR0A |= 0;
            break;
        case COM::Toggle:
            TCCR0A |= _BV(COM0A0);
            break;
        case COM::Clear:
            TCCR0A |= _BV(COM0A1);
            break;
        case COM::Set:
            TCCR0A |= _BV(COM0A1) | _BV(COM0A0);
            break;
    }

    switch(b)
    {
        default:
        case COM::Normal:
            //TCCR0A |= 0;
            break;
        case COM::Toggle:
            TCCR0A |= _BV(COM0B0);
            break;
        case COM::Clear:
            TCCR0A |= _BV(COM0B1);
            break;
        case COM::Set:
            TCCR0A |= _BV(COM0B1) | _BV(COM0B0);
            break;
    }
}

void Timer0::setWaveformGenerationMode(WGM mode)
{
    TCCR0A &= ~(_BV(WGM01) | _BV(WGM00));
    TCCR0B &= ~(_BV(WGM02));

    switch(mode)
    {
        default:
        case WGM::Mode_0:
            //TCCR0A |= 0;
            //TCCR0B |= 0;
            break;
        case WGM::Mode_1:
            TCCR0A |= _BV(WGM00);
            break;
        case WGM::Mode_2:
            TCCR0A |= _BV(WGM01);
            break;
        case WGM::Mode_3:
            TCCR0A |= _BV(WGM01) | _BV(WGM00);
            break;
        case WGM::Mode_4:
            TCCR0B |= _BV(WGM02);
            break;
        case WGM::Mode_5:
            TCCR0A |= _BV(WGM00);
            TCCR0B |= _BV(WGM02);
            break;
        case WGM::Mode_6:
            TCCR0A |= _BV(WGM01);
            TCCR0B |= _BV(WGM02);
            break;
        case WGM::Mode_7:
            TCCR0A |= _BV(WGM01) | _BV(WGM00);
            TCCR0B |= _BV(WGM02);
            break;
    }
}

void Timer0::setPrescaler(const Prescaler pre)
{
    timPres = pre;

    TCCR0B &= ~(_BV(CS02) | _BV(CS01) | _BV(CS00));

    switch(pre)
    {
        default:
        case Prescaler::No_clk:
            //TCCR0B |= 0;
            break;
        case Prescaler::Div_1:
            TCCR0B |= _BV(CS00);
            break;
        case Prescaler::Div_8:
            TCCR0B |= _BV(CS01);
            break;
        case Prescaler::Div_64:
            TCCR0B |= _BV(CS01) | _BV(CS00);
            break;
        case Prescaler::Div_256:
            TCCR0B |= _BV(CS02);
            break;
        case Prescaler::Div_1024:
            TCCR0B |= _BV(CS02) | _BV(CS00);
            break;
        case Prescaler::Ext_falling:
            TCCR0B |= _BV(CS02) | _BV(CS01);
            break;
        case Prescaler::Ext_rising:
            TCCR0B |= _BV(CS02) | _BV(CS01) | _BV(CS00);
            break;
    }
}

void Timer0::setInterruptEnable(bool a, bool b, bool overflow)
{
    TIMSK0 &= ~(_BV(OCIE0A) | _BV(OCIE0B) | _BV(TOIE0));

    switch(a)
    {
        default:
        case false:
            //TIMSK0 |= 0;
            break;
        case true:
            TIMSK0 |= _BV(OCIE0A);
            break;
    }

    switch(b)
    {
        default:
        case false:
            //TIMSK0 |= 0;
            break;
        case true:
            TIMSK0 |= _BV(OCIE0B);
            break;
    }

    switch(overflow)
    {
        default:
        case false:
            //TIMSK0 |= 0;
            break;
        case true:
            TIMSK0 |= _BV(TOIE0);
            break;
    }
}

void Timer0::setOCRnA(uint8_t val)
{
    OCR0A = val;
}

void Timer0::setOCRnB(uint8_t val)
{
    OCR0B = val;
}

void Timer0::setCompACallback(func_t func)
{
    timer0CompACallback = func;
}

void Timer0::setCompBCallback(func_t func)
{
    timer0CompBCallback = func;
}

void Timer0::setOverflowCallback(func_t func)
{
    timer0OverflowCallback = func;
}

void Timer0::resetTCNTn()
{
    TCNT0 = 0;
}

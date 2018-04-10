/**
 * \file timer2.cpp
 * \brief implementation de la classe Timer2
 * \author 
 */

#include "timer2.h"

func_t Timer2::timer2CompACallback = nullptr;
func_t Timer2::timer2CompBCallback = nullptr;
func_t Timer2::timer2OverflowCallback = nullptr;
Prescaler Timer2::timPres = Prescaler::No_clk;

ISR(TIMER2_COMPA_vect)
{
    if (Timer2::timer2CompACallback != nullptr) Timer2::timer2CompACallback();
}

ISR(TIMER2_COMPB_vect)
{
    if (Timer2::timer2CompBCallback != nullptr) Timer2::timer2CompBCallback();
}

ISR(TIMER2_OVF_vect)
{
    if (Timer2::timer2OverflowCallback != nullptr) Timer2::timer2OverflowCallback();
}

void Timer2::stop()
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

void Timer2::setCompareOutputMode(COM a, COM b)
{
    TCCR2A &= ~(_BV(COM2A1) | _BV(COM2A0) | _BV(COM2B1) | _BV(COM2B0));

    switch(a)
    {
        default:
        case COM::Normal:
            //TCCR2A |= 0;
            break;
        case COM::Toggle:
            TCCR2A |= _BV(COM2A0);
            break;
        case COM::Clear:
            TCCR2A |= _BV(COM2A1);
            break;
        case COM::Set:
            TCCR2A |= _BV(COM2A1) | _BV(COM2A0);
            break;
    }

    switch(b)
    {
        default:
        case COM::Normal:
            //TCCR2A |= 0;
            break;
        case COM::Toggle:
            TCCR2A |= _BV(COM2B0);
            break;
        case COM::Clear:
            TCCR2A |= _BV(COM2B1);
            break;
        case COM::Set:
            TCCR2A |= _BV(COM2B1) | _BV(COM2B0);
            break;
    }
}

void Timer2::setWaveformGenerationMode(WGM mode)
{
    TCCR2A &= ~(_BV(WGM21) | _BV(WGM20));
    TCCR2B &= ~(_BV(WGM22));

    switch(mode)
    {
        default:
        case WGM::Mode_0:
            //TCCR2A |= 0;
            //TCCR2B |= 0;
            break;
        case WGM::Mode_1:
            TCCR2A |= _BV(WGM20);
            break;
        case WGM::Mode_2:
            TCCR2A |= _BV(WGM21);
            break;
        case WGM::Mode_3:
            TCCR2A |= _BV(WGM21) | _BV(WGM20);
            break;
        case WGM::Mode_4:
            TCCR2B |= _BV(WGM22);
            break;
        case WGM::Mode_5:
            TCCR2A |= _BV(WGM20);
            TCCR2B |= _BV(WGM22);
            break;
        case WGM::Mode_6:
            TCCR2A |= _BV(WGM21);
            TCCR2B |= _BV(WGM22);
            break;
        case WGM::Mode_7:
            TCCR2A |= _BV(WGM21) | _BV(WGM20);
            TCCR2B |= _BV(WGM22);
            break;
    }
}

void Timer2::setPrescaler(const Prescaler pre)
{
    timPres = pre;

    TCCR2B &= ~(_BV(CS22) | _BV(CS21) | _BV(CS20));

    switch(pre)
    {
        default:
        case Prescaler::No_clk:
            //TCCR2B |= 0;
            break;
        case Prescaler::Div_1:
            TCCR2B |= _BV(CS20);
            break;
        case Prescaler::Div_8:
            TCCR2B |= _BV(CS21);
            break;
        case Prescaler::Div_32:
            TCCR2B |= _BV(CS21) | _BV(CS20);
            break;
        case Prescaler::Div_64:
            TCCR2B |= _BV(CS22);
            break;
        case Prescaler::Div_128:
            TCCR2B |= _BV(CS22) | _BV(CS20);
            break;
        case Prescaler::Div_256:
            TCCR2B |= _BV(CS22) | _BV(CS21);
            break;
        case Prescaler::Div_1024:
            TCCR2B |= _BV(CS22) | _BV(CS21) | _BV(CS20);
            break;
    }
}

void Timer2::setInterruptEnable(bool a, bool b, bool overflow)
{
    TIMSK2 &= ~(_BV(OCIE2A) | _BV(OCIE2B) | _BV(TOIE2));

    switch(a)
    {
        default:
        case false:
            //TIMSK2 |= 0;
            break;
        case true:
            TIMSK2 |= _BV(OCIE2A);
            break;
    }

    switch(b)
    {
        default:
        case false:
            //TIMSK2 |= 0;
            break;
        case true:
            TIMSK2 |= _BV(OCIE2B);
            break;
    }

    switch(overflow)
    {
        default:
        case false:
            //TIMSK2 |= 0;
            break;
        case true:
            TIMSK2 |= _BV(TOIE2);
            break;
    }
}

void Timer2::setOCRnA(uint8_t val)
{
    OCR2A = val;
}

void Timer2::setOCRnB(uint8_t val)
{
    OCR2B = val;
}

void Timer2::setCompACallback(func_t func)
{
    timer2CompACallback = func;
}

void Timer2::setCompBCallback(func_t func)
{
    timer2CompBCallback = func;
}

void Timer2::setOverflowCallback(func_t func)
{
    timer2OverflowCallback = func;
}

void Timer2::resetTCNTn()
{
    TCNT2 = 0;
}

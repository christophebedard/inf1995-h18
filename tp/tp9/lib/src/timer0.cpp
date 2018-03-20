/**
 * \file timer0.cpp
 * \brief implementation de la classe Timer0
 * \author 
 */

#include "timer0.h"

func_t timer0CompACallback = nullptr; /*!< le pointeur vers la fonction de callback pour TIMER0_COMPA */
func_t timer0CompBCallback = nullptr; /*!< le pointeur vers la fonction de callback pour TIMER0_COMPB */

ISR(TIMER0_COMPA_vect)
{
    if (timer0CompACallback != nullptr) timer0CompACallback();
}

ISR(TIMER0_COMPB_vect)
{
    if (timer0CompBCallback != nullptr) timer0CompBCallback();
}

Timer0::Timer0() : Timer() {}

Timer0::~Timer0() {}

void Timer0::setCompareOutputMode(COM a, COM b)
{
    switch(a)
    {
        default:
        case COM::COM_normal:
            //TCCR0A |= 0;
            break;
        case COM::COM_toggle:
            TCCR0A |= _BV(COM0A0);
            break;
        case COM::COM_clear:
            TCCR0A |= _BV(COM0A1);
            break;
        case COM::COM_set:
            TCCR0A |= _BV(COM0A1) | _BV(COM0A0);
            break;
    }

    switch(b)
    {
        default:
        case COM::COM_normal:
            //TCCR0A |= 0;
            break;
        case COM::COM_toggle:
            TCCR0A |= _BV(COM0B0);
            break;
        case COM::COM_clear:
            TCCR0A |= _BV(COM0B1);
            break;
        case COM::COM_set:
            TCCR0A |= _BV(COM0B1) | _BV(COM0B0);
            break;
    }
}

void Timer0::setWaveformGenerationMode(WGM mode)
{
    switch(mode)
    {
        default:
        case WGM::WGM_0:
            //TCCR0A |= 0;
            //TCCR0B |= 0;
            break;
        case WGM::WGM_1:
            TCCR0A |= _BV(WGM00);
            break;
        case WGM::WGM_2:
            TCCR0A |= _BV(WGM01);
            break;
        case WGM::WGM_3:
            TCCR0A |= _BV(WGM01) | _BV(WGM00);
            break;
        case WGM::WGM_4:
            TCCR0B |= _BV(WGM02);
            break;
        case WGM::WGM_5:
            TCCR0A |= _BV(WGM00);
            TCCR0B |= _BV(WGM02);
            break;
        case WGM::WGM_6:
            TCCR0A |= _BV(WGM01);
            TCCR0B |= _BV(WGM02);
            break;
        case WGM::WGM_7:
            TCCR0A |= _BV(WGM01) | _BV(WGM00);
            TCCR0B |= _BV(WGM02);
            break;
    }
}

void Timer0::setPrescaler(Prescaler pre)
{
    switch(pre)
    {
        default:
        case Prescaler::Pre_no_clk:
            //TCCR0B |= 0;
            break;
        case Prescaler::Pre_none:
            TCCR0B |= _BV(CS00);
            break;
        case Prescaler::Pre_8:
            TCCR0B |= _BV(CS01);
            break;
        case Prescaler::Pre_64:
            TCCR0B |= _BV(CS01) | _BV(CS00);
            break;
        case Prescaler::Pre_256:
            TCCR0B |= _BV(CS02);
            break;
        case Prescaler::Pre_1024:
            TCCR0B |= _BV(CS02) | _BV(CS00);
            break;
        case Prescaler::Pre_ext_falling:
            TCCR0B |= _BV(CS02) | _BV(CS01);
            break;
        case Prescaler::Pre_ext_rising:
            TCCR0B |= _BV(CS02) | _BV(CS01) | _BV(CS00);
            break;
    }
}

void Timer0::setInterruptEnable(uint8_t a, uint8_t b)
{
    switch(a)
    {
        default:
        case 0:
            //TIMSK0 |= 0;
            break;
        case 1:
            TIMSK0 |= _BV(OCIE0A);
            break;
    }

    switch(b)
    {
        default:
        case 0:
            //TIMSK0 |= 0;
            break;
        case 1:
            TIMSK0 |= _BV(OCIE0B);
            break;
    }
}

void Timer0::setOCRnA(uint16_t val)
{
    // 8 bits seulement pour timer0
    OCR0A = (uint8_t)val;
}

void Timer0::setOCRnB(uint16_t val)
{
    // 8 bits seulement pour timer0
    OCR0B = (uint8_t)val;
}

void Timer0::setCompACallback(func_t func)
{
    timer0CompACallback = func;
}

void Timer0::setCompBCallback(func_t func)
{
    timer0CompBCallback = func;
}

void Timer0::resetTCNTn()
{
    TCNT0 = 0;
}

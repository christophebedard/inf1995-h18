/**
 * \file timer2.cpp
 * \brief implementation de la classe Timer2
 * \author 
 */

#include "timer2.h"

func_t timer2CompACallback = nullptr; /*!< le pointeur vers la fonction de callback pour TIMER2_COMPA */
func_t timer2CompBCallback = nullptr; /*!< le pointeur vers la fonction de callback pour TIMER2_COMPB */

ISR(TIMER2_COMPA_vect)
{
    if (timer2CompACallback != nullptr) timer2CompACallback();
}

ISR(TIMER2_COMPB_vect)
{
    if (timer2CompBCallback != nullptr) timer2CompBCallback();
}

Timer2::Timer2() : Timer() {}

Timer2::~Timer2() {}

void Timer2::setCompareOutputMode(COM a, COM b)
{
    switch(a)
    {
        default:
        case COM::COM_normal:
            //TCCR2A |= 0;
            break;
        case COM::COM_toggle:
            TCCR2A |= _BV(COM2A0);
            break;
        case COM::COM_clear:
            TCCR2A |= _BV(COM2A1);
            break;
        case COM::COM_set:
            TCCR2A |= _BV(COM2A1) | _BV(COM2A0);
            break;
    }

    switch(b)
    {
        default:
        case COM::COM_normal:
            //TCCR2A |= 0;
            break;
        case COM::COM_toggle:
            TCCR2A |= _BV(COM2B0);
            break;
        case COM::COM_clear:
            TCCR2A |= _BV(COM2B1);
            break;
        case COM::COM_set:
            TCCR2A |= _BV(COM2B1) | _BV(COM2B0);
            break;
    }
}

void Timer2::setWaveformGenerationMode(WGM mode)
{
    switch(mode)
    {
        default:
        case WGM::WGM_0:
            //TCCR2A |= 0;
            //TCCR2B |= 0;
            break;
        case WGM::WGM_1:
            TCCR2A |= _BV(WGM20);
            break;
        case WGM::WGM_2:
            TCCR2A |= _BV(WGM21);
            break;
        case WGM::WGM_3:
            TCCR2A |= _BV(WGM21) | _BV(WGM20);
            break;
        case WGM::WGM_4:
            TCCR2B |= _BV(WGM22);
            break;
        case WGM::WGM_5:
            TCCR2A |= _BV(WGM20);
            TCCR2B |= _BV(WGM22);
            break;
        case WGM::WGM_6:
            TCCR2A |= _BV(WGM21);
            TCCR2B |= _BV(WGM22);
            break;
        case WGM::WGM_7:
            TCCR2A |= _BV(WGM21) | _BV(WGM20);
            TCCR2B |= _BV(WGM22);
            break;
    }
}

void Timer2::setPrescaler(Prescaler pre)
{
    switch(pre)
    {
        default:
        case Prescaler::Pre_no_clk:
            //TCCR2B |= 0;
            break;
        case Prescaler::Pre_none:
            TCCR2B |= _BV(CS20);
            break;
        case Prescaler::Pre_8:
            TCCR2B |= _BV(CS21);
            break;
        case Prescaler::Pre_64:
            TCCR2B |= _BV(CS21) | _BV(CS20);
            break;
        case Prescaler::Pre_256:
            TCCR2B |= _BV(CS22);
            break;
        case Prescaler::Pre_1024:
            TCCR2B |= _BV(CS22) | _BV(CS20);
            break;
    }
}

void Timer2::setInterruptEnable(uint8_t a, uint8_t b)
{
    switch(a)
    {
        default:
        case 0:
            //TIMSK2 |= 0;
            break;
        case 1:
            TIMSK2 |= _BV(OCIE2A);
            break;
    }

    switch(b)
    {
        default:
        case 0:
            //TIMSK2 |= 0;
            break;
        case 1:
            TIMSK2 |= _BV(OCIE2B);
            break;
    }
}

void Timer2::setOCRnA(uint16_t val)
{
    // 8 bits seulement pour timer2
    OCR2A = (uint8_t)val;
}

void Timer2::setOCRnB(uint16_t val)
{
    // 8 bits seulement pour timer2
    OCR2B = (uint8_t)val;
}

void Timer2::setCompACallback(func_t func)
{
    timer2CompACallback = func;
}

void Timer2::setCompBCallback(func_t func)
{
    timer2CompBCallback = func;
}

void Timer2::resetTCNTn()
{
    TCNT2 = 0;
}

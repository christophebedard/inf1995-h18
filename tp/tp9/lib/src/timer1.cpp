/**
 * \file timer1.cpp
 * \brief implementation de la classe Timer1
 * \author 
 */

#include "timer1.h"

func_t timer1CompACallback = nullptr; /*!< le pointeur vers la fonction de callback pour TIMER1_COMPA */
func_t timer1CompBCallback = nullptr; /*!< le pointeur vers la fonction de callback pour TIMER1_COMPB */

ISR(TIMER1_COMPA_vect)
{
    if (timer1CompACallback != nullptr) timer1CompACallback();
}

ISR(TIMER1_COMPB_vect)
{
    if (timer1CompBCallback != nullptr) timer1CompBCallback();
}

Timer1::Timer1() : Timer() {}

Timer1::~Timer1() {}

void Timer1::setCompareOutputMode(COM a, COM b)
{
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
            TCCR1A |= _BV(COM1B1) | _BV(COM0B0);
            break;
    }
}

void Timer1::setWaveformGenerationMode(WGM mode)
{
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

void Timer1::setPrescaler(Prescaler pre)
{
    switch(pre)
    {
        default:
        case Prescaler::Pre_no_clk:
            //TCCR1B |= 0;
            break;
        case Prescaler::Pre_none:
            TCCR1B |= _BV(CS10);
            break;
        case Prescaler::Pre_8:
            TCCR1B |= _BV(CS11);
            break;
        case Prescaler::Pre_64:
            TCCR1B |= _BV(CS11) | _BV(CS10);
            break;
        case Prescaler::Pre_256:
            TCCR1B |= _BV(CS12);
            break;
        case Prescaler::Pre_1024:
            TCCR1B |= _BV(CS12) | _BV(CS10);
            break;
        case Prescaler::Pre_ext_falling:
            TCCR1B |= _BV(CS12) | _BV(CS11);
            break;
        case Prescaler::Pre_ext_rising:
            TCCR1B |= _BV(CS12) | _BV(CS11) | _BV(CS10);
            break;
    }
}

void Timer1::setInterruptEnable(uint8_t a, uint8_t b)
{
    switch(a)
    {
        default:
        case 0:
            //TIMSK1 |= 0;
            break;
        case 1:
            TIMSK1 |= _BV(OCIE1A);
            break;
    }

    switch(b)
    {
        default:
        case 0:
            //TIMSK1 |= 0;
            break;
        case 1:
            TIMSK1 |= _BV(OCIE1B);
            break;
    }
}

void Timer1::setOCRnA(uint16_t val)
{
    Debug::out(val);
    Debug::out(" = set OCR1A\n");
    OCR1A = val;
}

void Timer1::setOCRnB(uint16_t val)
{
    Debug::out(val);
    Debug::out(" = set OCR1B\n");
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

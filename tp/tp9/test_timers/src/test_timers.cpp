/**
 * \file test_pwm.cpp
 * \brief programme pour tester le PWM
 * \author 
 */

#include "delai.h"
#include "debug.h"
#include "timer0.h"
#include "timer1.h"
#include "timer2.h"

volatile bool startTim1 = false;

volatile bool startTim2 = false;

void callbackTimer0CompA()
{
    PORTB = VERT;
    Debug::out("callback tim0 compA");
    //startTim1 = true;
}

void callbackTimer0CompB()
{
    PORTB = ROUGE;
    Debug::out("callback tim0 compB");
    startTim1 = true;
}

void callbackTimer1CompA()
{
    PORTB = ROUGE;
    Debug::out("callback tim1 compA");
    //startTim2 = true;
}

void callbackTimer1CompB()
{
    PORTB = VERT;
    Debug::out("callback tim1 compB");
    startTim2 = true;
}

void callbackTimer2CompA()
{
    PORTB = VERT;
    Debug::out("callback tim2 compA");
}

void callbackTimer2CompB()
{
    PORTB = ROUGE;
    Debug::out("callback tim2 compB");
}


int main()
{
    DDRB = SORTIE; // LED

    PORTB = VERT;
    waitForMs(250);
    PORTB = ETEINT;

    UART::init(); // pour debug

    Debug::out("wait\n");
    waitForMs(5000);

    Debug::out("timer0\n");
    cli();
    Timer0 tim0;
    tim0.setCompareOutputMode(COM::COM_set, COM::COM_set);
    tim0.setWaveformGenerationMode(WGM::WGM_2);
    tim0.setPrescaler(Prescaler::Pre_1024);
    tim0.setInterruptEnable(0, 1);
    tim0.setCompACallback(&callbackTimer0CompA);
    tim0.setCompBCallback(&callbackTimer0CompB);
    tim0.setOCRnA(500);
    tim0.setOCRnB(2500);
    tim0.resetTCNTn();
    sei();

    while(!startTim1);
    Debug::out("timer1\n");
    cli();
    Timer1 tim1;
    tim1.setCompareOutputMode(COM::COM_set, COM::COM_set);
    tim1.setWaveformGenerationMode(WGM::WGM_4);
    tim1.setPrescaler(Prescaler::Pre_1024);
    tim1.setInterruptEnable(0, 1);
    tim1.setCompACallback(&callbackTimer0CompA);
    tim1.setCompBCallback(&callbackTimer0CompB);
    tim1.setOCRnA(500);
    tim1.setOCRnB(2500);
    tim1.resetTCNTn();
    sei();

    while(!startTim2);
    Debug::out("timer2\n");
    cli();
    Timer2 tim2;
    tim2.setCompareOutputMode(COM::COM_set, COM::COM_set);
    tim2.setWaveformGenerationMode(WGM::WGM_4);
    tim2.setPrescaler(Prescaler::Pre_1024);
    tim2.setInterruptEnable(1, 0);
    tim2.setCompACallback(&callbackTimer0CompA);
    tim2.setCompBCallback(&callbackTimer0CompB);
    tim2.setOCRnA(500);
    tim2.setOCRnB(2500);
    tim2.resetTCNTn();
    sei();

    Debug::out("fin\n");

    while(true);

    return 0;
}

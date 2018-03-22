/**
 * \file test_pwm.cpp
 * \brief programme pour tester le PWM
 * \author 
 */

#include "delai.h"
#include "debug.h"
#include "pwm.h"


int main()
{
    UART::init(); // pour debug

    initPWM();

    Debug::out("debut\n");

    waitForMs(500);
    ajustementPWM(25);
    Debug::out("25\n");
    waitForMs(1000);
    ajustementPWM(50);
    Debug::out("50\n");
    waitForMs(1000);
    ajustementPWM(75);
    Debug::out("75\n");
    waitForMs(1000);
    ajustementPWM(100);
    Debug::out("100\n");
    waitForMs(1000);
    ajustementPWM(0);
    Debug::out("0\n");

    Debug::out("fin\n");

    return 0;
}

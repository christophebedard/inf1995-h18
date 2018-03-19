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
    waitForMs(1000);
    ajustementPWM(50);
    waitForMs(1000);
    ajustementPWM(75);
    waitForMs(1000);
    ajustementPWM(100);
    waitForMs(1000);
    ajustementPWM(0);

    Debug::out("fin\n");

    return 0;
}

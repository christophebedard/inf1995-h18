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
    Debug::init();
    PWM::init();

    Debug::out("debut\n");

    waitForMs(500);

    PWM::setPourcentage(25);
    Debug::out("25\n");

    waitForMs(1000);

    PWM::setPourcentage(50);
    Debug::out("50\n");

    waitForMs(1000);

    PWM::setPourcentage(75);
    Debug::out("75\n");

    waitForMs(1000);

    PWM::setPourcentage(100);
    Debug::out("100\n");

    waitForMs(1000);

    PWM::setPourcentage(0);
    Debug::out("0\n");

    PWM::virageGauche(50);
    Debug::out("virage gauche\n");

    PWM::virageDroit(50);
    Debug::out("virage droit\n");

    Debug::out("fin\n");

    while(true);

    return 0;
}

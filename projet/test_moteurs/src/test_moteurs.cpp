/**
 * \file test_moteurs.cpp
 * \brief programme pour tester les moteurs/PWM
 * \author 
 */

#include "delai.h"
#include "debug.h"
#include "moteurs.h"


int main()
{
    Debug::init();
    Moteurs::init();

    Debug::out("debut\n");

    waitForMs(500);

    Moteurs::setPourcentage(25);
    Debug::out("25\n");

    waitForMs(1000);

    Moteurs::setPourcentage(50);
    Debug::out("50\n");

    waitForMs(1000);

    Moteurs::setPourcentage(75);
    Debug::out("75\n");

    waitForMs(1000);

    Moteurs::setPourcentage(100);
    Debug::out("100\n");

    waitForMs(1000);

    Moteurs::setPourcentage(0);
    Debug::out("0\n");

    Moteurs::virageGauche(50);
    Debug::out("virage gauche\n");

    Moteurs::virageDroit(50);
    Debug::out("virage droit\n");

    Debug::out("fin\n");

    while(true);

    return 0;
}

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

    Debug::out("25\n");
    Moteurs::setPourcentage(25);

    waitForMs(1000);

    Debug::out("50\n");
    Moteurs::setPourcentage(50);

    waitForMs(1000);

    Debug::out("75\n");
    Moteurs::setPourcentage(75);
    
    waitForMs(1000);

    Debug::out("100\n");
    Moteurs::setPourcentage(100);
    
    waitForMs(2000);

    Debug::out("arriere\n");

    Moteurs::setDirection(DirectionMoteur::Moteur_arriere);

    Debug::out("25\n");
    Moteurs::setPourcentage(25);

    waitForMs(1000);

    Debug::out("50\n");
    Moteurs::setPourcentage(50);

    waitForMs(1000);

    Debug::out("75\n");
    Moteurs::setPourcentage(75);
    
    waitForMs(1000);

    Debug::out("100\n");
    Moteurs::setPourcentage(100);
    
    waitForMs(1000);

    Debug::out("0\n");
    Moteurs::setPourcentage(0);

    Debug::out("virage gauche\n");
    Moteurs::virageGauche(50);

    Debug::out("virage droit\n");
    Moteurs::virageDroit(50);

    Debug::out("fin\n");

    while(true);

    return 0;
}

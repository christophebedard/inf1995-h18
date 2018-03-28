/**
 * \file test_capteur_distance.cpp
 * \brief programme pour tester le capteur de distance
 * \author 
 */

#include "debug.h"
#include "buzzer.h"
#include "capteur_distance.h"

int main()
{
    Debug::init();
    CapteurDistance::init();
    Buzzer::init();

    while(true)
    {
        uint16_t g = CapteurDistance::getDistanceGauche();
        uint16_t d = CapteurDistance::getDistanceDroit();
        
        Buzzer::play(d);

        Debug::out(g);
        Debug::out(", ");
        Debug::out(d);
        Debug::out("\n");
    }

    return 0;
}

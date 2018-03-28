/**
 * \file test_capteurs_distance.cpp
 * \brief programme pour tester les capteurs de distance
 * \author 
 */

#include "debug.h"
#include "buzzer.h"
#include "capteurs_distance.h"

int main()
{
    Debug::init();
    CapteursDistance::init();
    Buzzer::init();

    while(true)
    {
        uint16_t g = CapteursDistance::getDistanceGauche();
        uint16_t d = CapteursDistance::getDistanceDroit();
        
        Buzzer::play(d);

        Debug::out(g);
        Debug::out(", ");
        Debug::out(d);
        Debug::out("\n");
    }

    return 0;
}

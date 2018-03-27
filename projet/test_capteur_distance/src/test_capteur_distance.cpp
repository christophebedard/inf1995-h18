/**
 * \file test_capteur_distance.cpp
 * \brief programme pour tester le capteur de distance
 * \author 
 */

#include "debug.h"
#include "capteur_distance.h"

int main()
{
    Debug::init();
    CapteurDistance::init();

    while(true)
    {
        Debug::out(CapteurDistance::getDistance());
        Debug::out("\n");
    }

    return 0;
}

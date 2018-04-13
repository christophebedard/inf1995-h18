/**
 * \file etalonnage_capteur_distance.cpp
 * \brief programme pour la prise de donnees pour l'etalonnage
 *          des capteurs de distance
 * \author Christophe Bourque Bedard
 */

#include "broches.h"
#include "debug.h"
#include "can.h"

int main()
{
    Debug::init();

    can c;
    

    while(true)
    {
        // assume que le capteur est place a gauche
        uint16_t valCan = c.lecture(_BROCHE_TO_PIN(BROCHE_CAPTEUR_DISTANCE_GAUCHE));

        Debug::out(valCan);
        Debug::out("\n");

        waitForMs(50);
    }

    return 0;
}

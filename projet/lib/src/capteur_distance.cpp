/**
 * \file capteur_distance.cpp
 * \brief implementation de la classe CapteurDistance
 * \author 
 */

#include "capteur_distance.h"

// initialisation du CAN
can CapteurDistance::can_;


void CapteurDistance::init()
{
    // mettre les pins des CANs en entree
	DDRA &= ~(_BV(_BROCHE_TO_PIN(BROCHE_CAPTEUR_DISTANCE_GAUCHE)));
	DDRA &= ~(_BV(_BROCHE_TO_PIN(BROCHE_CAPTEUR_DISTANCE_DROIT)));
}

uint16_t CapteurDistance::getDistanceGauche()
{
    return can_.lecture(_BROCHE_TO_PIN(BROCHE_CAPTEUR_DISTANCE_GAUCHE));
}

uint16_t CapteurDistance::getDistanceDroit()
{
    return can_.lecture(_BROCHE_TO_PIN(BROCHE_CAPTEUR_DISTANCE_DROIT));
}

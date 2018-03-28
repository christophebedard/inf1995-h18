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
    return canToDistance(can_.lecture(_BROCHE_TO_PIN(BROCHE_CAPTEUR_DISTANCE_GAUCHE)));
}

uint16_t CapteurDistance::getDistanceDroit()
{
    return canToDistance(can_.lecture(_BROCHE_TO_PIN(BROCHE_CAPTEUR_DISTANCE_DROIT)));
}

uint16_t CapteurDistance::canToDistance(const uint16_t canVal)
{
    // voir util/python/interpolationCapteurDistance
    uint16_t dist = (6787.0 / ((double)canVal - 3.0)) - 4.0;

    // validation
    dist = (CAPTEUR_DISTANCE_MIN <= dist && dist <= CAPTEUR_DISTANCE_MAX)
            ? dist : CAPTEUR_DISTANCE_INVALIDE;

    return dist;
}
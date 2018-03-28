/**
 * \file capteurs_distance.cpp
 * \brief implementation de la classe CapteursDistance
 * \author 
 */

#include "capteurs_distance.h"

// initialisation du CAN
can CapteursDistance::can_;


void CapteursDistance::init()
{
    // mettre les pins des CANs en entree
	DDRA &= ~(_BV(_BROCHE_TO_PIN(BROCHE_CAPTEUR_DISTANCE_GAUCHE)));
	DDRA &= ~(_BV(_BROCHE_TO_PIN(BROCHE_CAPTEUR_DISTANCE_DROIT)));
}

uint16_t CapteursDistance::getDistanceGauche()
{
    return canToDistance(can_.lecture(_BROCHE_TO_PIN(BROCHE_CAPTEUR_DISTANCE_GAUCHE)));
}

uint16_t CapteursDistance::getDistanceDroit()
{
    return canToDistance(can_.lecture(_BROCHE_TO_PIN(BROCHE_CAPTEUR_DISTANCE_DROIT)));
}

uint16_t CapteursDistance::canToDistance(const uint16_t canVal)
{
    // voir util/python/interpolationCapteurDistance
    uint16_t dist = (6787.0 / ((double)canVal - 3.0)) - 4.0;

    // validation
    dist = (CAPTEUR_DISTANCE_MIN <= dist && dist <= CAPTEUR_DISTANCE_MAX)
            ? dist : CAPTEUR_DISTANCE_INVALIDE;

    return dist;
}
/**
 * \file capteurs_distance.cpp
 * \brief implementation de la classe CapteursDistance
 * \author 
 */

#include "capteurs_distance.h"


can CapteursDistance::can_;
uint16_t CapteursDistance::memCanGauche[LONGUEUR_MEMOIRE_LECTURES];
uint16_t CapteursDistance::memCanDroit[LONGUEUR_MEMOIRE_LECTURES];
uint16_t CapteursDistance::totalCanGauche = 0;
uint16_t CapteursDistance::totalCanDroit = 0;
uint8_t CapteursDistance::indexCanGauche = 0;
uint8_t CapteursDistance::indexCanDroit = 0;

void CapteursDistance::init()
{
    // mettre les pins des CANs en entree
	DDRA &= ~(_BV(_BROCHE_TO_PIN(BROCHE_CAPTEUR_DISTANCE_GAUCHE)));
	DDRA &= ~(_BV(_BROCHE_TO_PIN(BROCHE_CAPTEUR_DISTANCE_DROIT)));
}

uint8_t CapteursDistance::getDistanceGauche()
{
    uint16_t nouvelleVal = ajoutNouvelleLecture(can_.lecture(_BROCHE_TO_PIN(BROCHE_CAPTEUR_DISTANCE_GAUCHE)),
                                        memCanGauche,
                                        indexCanGauche,
                                        totalCanGauche);
    return canToDistance(nouvelleVal);
}

uint8_t CapteursDistance::getDistanceDroit()
{
    //uint16_t nouvelleVal = ajoutNouvelleLecture(can_.lecture(_BROCHE_TO_PIN(BROCHE_CAPTEUR_DISTANCE_DROIT)),
    //                                    memCanDroit,
    //                                    indexCanDroit,
    //                                    totalCanDroit);
    //return canToDistance(nouvelleVal);
    return canToDistance(can_.lecture(_BROCHE_TO_PIN(BROCHE_CAPTEUR_DISTANCE_DROIT)));
}

uint8_t CapteursDistance::canToDistance(const uint16_t canVal)
{
    // voir util/python/interpolationCapteurDistance
    uint8_t dist = (((7.0 / 5.0) * 6787.0 / ((double)canVal - 3.0)) - 4.0);

    // validation
    //dist = (CAPTEUR_DISTANCE_MIN <= dist && dist <= CAPTEUR_DISTANCE_MAX)
    //        ? dist : CAPTEUR_DISTANCE_INVALIDE;
    dist = (CAPTEUR_DISTANCE_MIN <= dist)
            ? ((dist <= CAPTEUR_DISTANCE_MAX) ? dist : CAPTEUR_DISTANCE_MAX)
              : CAPTEUR_DISTANCE_INVALIDE;

    return dist;
}

uint16_t CapteursDistance::ajoutNouvelleLecture(uint16_t lectCan, uint16_t* memCan, uint8_t& indexMemCan, uint16_t& totCan)
{
    // selon le principe de rolling average
    // https://en.wikipedia.org/wiki/Moving_average#Simple_moving_average
    // nouveau total = ancien total + nouvelle lecture - plus vieille lecture
    // nouvelle valeur = nouveau total / n
    totCan -= memCan[indexMemCan];
    totCan += lectCan;
    memCan[indexMemCan] = lectCan;
    indexMemCan = (indexMemCan < (LONGUEUR_MEMOIRE_LECTURES - 1)) ? (indexMemCan + 1) : 0;
    return (uint16_t)((double)totCan / (double)LONGUEUR_MEMOIRE_LECTURES);
}

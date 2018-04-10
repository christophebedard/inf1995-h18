/**
 * \file capteurs_distance.cpp
 * \brief implementation de la classe CapteursDistance
 * \author 
 */

#include "capteurs_distance.h"


can CapteursDistance::can_;
uint16_t CapteursDistance::memDistGauche[LONGUEUR_MEMOIRE_LECTURES];
uint16_t CapteursDistance::memDistDroit[LONGUEUR_MEMOIRE_LECTURES];

void CapteursDistance::init()
{
    // mettre les pins des CANs en entree
	DDRA &= ~(_BV(_BROCHE_TO_PIN(BROCHE_CAPTEUR_DISTANCE_GAUCHE)));
	DDRA &= ~(_BV(_BROCHE_TO_PIN(BROCHE_CAPTEUR_DISTANCE_DROIT)));
}

uint8_t CapteursDistance::getDistanceGauche()
{
    ajoutNouvelleLecture(can_.lecture(_BROCHE_TO_PIN(BROCHE_CAPTEUR_DISTANCE_GAUCHE)),
                         memDistGauche);
    return canToDistance(getMoyenneLectures(memDistGauche));
}

uint8_t CapteursDistance::getDistanceDroit()
{
    //ajoutNouvelleLecture(can_.lecture(_BROCHE_TO_PIN(BROCHE_CAPTEUR_DISTANCE_GAUCHE)),
    //                     memDistDroit);
    //return canToDistance(getMoyenneLectures(memDistDroit));
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

void CapteursDistance::ajoutNouvelleLecture(uint16_t canLect, uint16_t* memDist)
{
    // decalage
    for (uint8_t i = (LONGUEUR_MEMOIRE_LECTURES - 1); i > 0; --i)
    {
        memDist[i] = memDist[i - 1];
    }

    // ajout de la nouvelle valeur
    memDist[0] = canLect;
}

uint16_t CapteursDistance::getMoyenneLectures(uint16_t* memDist)
{
    double total = 0.0;
    for (uint8_t i = 0; i < LONGUEUR_MEMOIRE_LECTURES; ++i)
    {
        total += (double)memDist[i];
    }
    return (total / (double)LONGUEUR_MEMOIRE_LECTURES);
}

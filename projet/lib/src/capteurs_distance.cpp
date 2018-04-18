/**
 * \file capteurs_distance.cpp
 * \brief implementation de la classe CapteursDistance
 * \author Christophe Bourque Bedard
 * \author Simon Moreau
 * \author Fares Ouaissa
 * \author Mohamed Saddik
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

bool CapteursDistance::getDistanceGauche(uint8_t* dist)
{
    return canToDistance(ajoutNouvelleLecture(can_.lecture(_BROCHE_TO_PIN(BROCHE_CAPTEUR_DISTANCE_GAUCHE)),
                                              memCanGauche,
                                              indexCanGauche,
                                              totalCanGauche),
                         dist);
}

bool CapteursDistance::getDistanceDroit(uint8_t* dist)
{
    return canToDistance(ajoutNouvelleLecture(can_.lecture(_BROCHE_TO_PIN(BROCHE_CAPTEUR_DISTANCE_DROIT)),
                                              memCanDroit,
                                              indexCanDroit,
                                              totalCanDroit),
                         dist);
}

bool CapteursDistance::isDistanceValide(uint8_t* dist)
{
    return (CAPTEUR_DISTANCE_MIN <= *dist
                                 && *dist <= CAPTEUR_DISTANCE_MAX);
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

void CapteursDistance::formatDistance(uint8_t* dist)
{
    // si la distance est plus petite que le minimum, on lui donne 0
    // si la distance est plus grande que le maximum, on lui donne le maximum
    // sinon, on ne la modifie pas
    *dist = (CAPTEUR_DISTANCE_MIN <= *dist)
             ? ((*dist <= CAPTEUR_DISTANCE_FORMAT_MAX) ? *dist : CAPTEUR_DISTANCE_FORMAT_MAX)
               : CAPTEUR_DISTANCE_FORMAT_MIN;
}

uint8_t constrain(uint8_t val, uint8_t min, uint8_t max)
{
    uint8_t res = val;

    if (val < min)
    {
        res = min;
    }
    else if (val > max)
    {
        res = max;
    }

    return res;
}

bool CapteursDistance::canToDistance(uint16_t canVal, uint8_t* dist)
{
    if (canVal >= 730)
        *dist = 5;
    else if (canVal >= 700)
        *dist = 6;
    else if (canVal >= 680)
        *dist = 7;
    else if (canVal >= 610)
        *dist = 8;
    else if (canVal >= 550)
        *dist = 9;
    else if (canVal >= 490)
        *dist = 10;
    else if (canVal >= 440)
        *dist = 11;
    else if (canVal >= 410)
        *dist = 12;
    else if (canVal >= 390)
        *dist = 13;
    else if (canVal >= 365)
        *dist = 14;
    else if (canVal >= 345)
        *dist = 15;
    else if (canVal >= 330)
        *dist = 16;
    else if (canVal >= 320)
        *dist = 17;
    else if (canVal >= 310)
        *dist = 18;
    else if (canVal >= 300)
        *dist = 19;
    else if (canVal >= 290)
        *dist = 20;
    else
        *dist = constrain(uint8_t(16667 * pow((double)canVal, -1.176)), 21, 80);
    
    return true;
}

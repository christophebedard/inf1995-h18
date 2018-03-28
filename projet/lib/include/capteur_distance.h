#ifndef LIB_CAPTEUR_DISTANCE_H
#define LIB_CAPTEUR_DISTANCE_H

/**
 * \file capteur_distance.h
 * \brief declaration de la classe CapteurDistance
 * \author 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "broches.h"
#include "can.h"
#include "debug.h"


/**
 *  distance [cm] minimale pour une lecture valide
 */
#define CAPTEUR_DISTANCE_MIN 10
/**
 * distance [cm] maximale pour une lecture valide
 */
#define CAPTEUR_DISTANCE_MAX 80
/**
 * distance [cm] maximale pour une lecture valide
 */
#define CAPTEUR_DISTANCE_INVALIDE 0


/**
 * \class CapteurDistance
 * \brief classe qui drive les capteurs de distance
 */
class CapteurDistance
{
public:
    /**
     * Initialisation du capteur de distance
     */
    static void init();

    /**
     * Accesseur pour la distance la plus recente (gauche)
     * 
     * \return la distance [cm]
     */
    static uint16_t getDistanceGauche();

    /**
     * Accesseur pour la distance la plus recente (droit)
     * 
     * \return la distance [cm]
     */
    static uint16_t getDistanceDroit();

private:
    static can can_; ///< l'objet pour le CAN

    /**
     * Conversion de la valeur de lecture du CAN vers la distance
     * 
     * \param canVal : la valeur lue par le CAN [0, 2^10 - 1]
     * 
     * \return la distance [cm]
     */
    static uint16_t canToDistance(const uint16_t canVal);

};

#endif // LIB_CAPTEUR_DISTANCE_H

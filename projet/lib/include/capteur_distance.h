#ifndef LIB_CAPTEUR_DISTANCE_H
#define LIB_CAPTEUR_DISTANCE_H

/**
 * \file capteur_distance.h
 * \brief declaration de la classe CapteurDistance
 * \author 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
//#include "pwm.h"
#include "broches.h"
#include "can.h"
#include "debug.h"

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
     * \return la distance []
     */
    static uint16_t getDistanceGauche();

    /**
     * Accesseur pour la distance la plus recente (droit)
     * 
     * \return la distance []
     */
    static uint16_t getDistanceDroit();

private:
    static can can_; ///< l'objet pour le CAN

};

#endif // LIB_CAPTEUR_DISTANCE_H

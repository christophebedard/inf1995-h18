#ifndef LIB_CAPTEUR_DISTANCE_H
#define LIB_CAPTEUR_DISTANCE_H

/**
 * \file capteur_distance.h
 * \brief declaration de la classe CapteurDistance
 * \author 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
//#include "enums_structs.h"
//#include "pwm.h"
#include "debug.h"

/**
 * \class CapteurDistance
 * \brief classe qui enveloppe (wrap) le 
 */
class CapteurDistance
{
public:
    /**
     * Initialisation du capteur de distance
     */
    static void init();

    /**
     * Accesseur pour la distance lue la plus recente
     * 
     * \return la distance []
     */
    static uint8_t getDistance();

private:

};

#endif // LIB_CAPTEUR_DISTANCE_H

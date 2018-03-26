#ifndef LIB_PWM_H
#define LIB_PWM_H

/**
 * \file pwm.h
 * \brief declaration de la classe PWM
 * \author 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"
#include "delai.h"
#include "timer1.h"

/**
 * \class PWM
 * \brief classe qui enveloppe (wrap) le timer1 pour le PWM
 */
class PWM
{
public:
    /**
     * Initialisation du PWM
     */
    static void init();

    /**
     * Ajustement du PWM
     * 
     * \param pourcentage : la nouvelle valeur [0, 100] du PWM
     */
    static void setPourcentage(const uint8_t& pourcentage);

    /**
     * Virage a droite
     * 
     * \param pourcentage : la nouvelle valeur [0, 100] du PWM
     */
    static void virageDroit(const uint8_t& pourcentage);

    /**
     * Virage a gauche
     * 
     * \param pourcentage : la nouvelle valeur [0, 100] du PWM
     */
    static void virageGauche(const uint8_t& pourcentage);

    static const uint8_t BROCHE_MOTEUR_GAUCHE; ///< la broche PWM associee au moteur gauche (OC1A : port D, pin 5/broche 6)
    static const uint8_t BROCHE_MOTEUR_DROIT; ///< la broche PWM associee au moteur droit (OC1B : port D, pin 4/broche 5)

};

#endif // LIB_PWM_H

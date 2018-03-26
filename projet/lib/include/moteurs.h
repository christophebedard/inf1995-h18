#ifndef LIB_MOTEURS_H
#define LIB_MOTEURS_H

/**
 * \file moteurs.h
 * \brief declaration de la classe Moteurs
 * \author 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "pwm.h"

/**
 * \class Moteurs
 * \brief classe qui enveloppe (wrap) le PWM pour controler les moteurs
 */
class Moteurs
{
public:
    /**
     * Initialisation des moteurs
     */
    static void init();

    /**
     * Ajustement des moteurs (gauche et droit)
     * 
     * \param pourcentage : la nouvelle valeur [0, 100] du PWM
     */
    static void setPourcentage(const uint8_t& pourcentage);

    /**
     * Ajustement du moteur gauche
     * 
     * \param pourcentage : la nouvelle valeur [0, 100] du PWM
     */
    static void setPourcentageGauche(const uint8_t& pourcentage);

    /**
     * Ajustement du moteur droit
     * 
     * \param pourcentage : la nouvelle valeur [0, 100] du PWM
     */
    static void setPourcentageDroite(const uint8_t& pourcentage);

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

private:


};

#endif // LIB_MOTEURS_H

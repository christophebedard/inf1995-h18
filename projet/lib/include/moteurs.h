#ifndef LIB_MOTEURS_H
#define LIB_MOTEURS_H

/**
 * \file moteurs.h
 * \brief declaration de la classe Moteurs
 * \author 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "enums_structs.h"
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
     * Reglage de la direction des deux moteurs
     * 
     * \param dir : la direction des moteurs selon DirectionMoteur
     */
    static void setDirection(const DirectionMoteur& dir);

    /**
     * Reglage de la direction du moteur gauche
     * 
     * \param dir : la direction du moteur selon DirectionMoteur
     */
    static void setDirectionMoteurGauche(const DirectionMoteur& dirG);

    /**
     * Reglage de la direction du moteur droit
     * 
     * \param dir : la direction du moteur selon DirectionMoteur
     */
    static void setDirectionMoteurDroit(const DirectionMoteur& dirD);

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
    /**
     * Reglage de la direction selon la broche
     * 
     * \param dir : la direction du moteur selon DirectionMoteur
     * \param b : la broche a ajuster
     */
    static void setDirectionBroche(const DirectionMoteur& dir, uint8_t b);

};

#endif // LIB_MOTEURS_H

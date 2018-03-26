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
#include "broches.h"
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
     * Ajustement du PWM (deux cotes)
     * 
     * \param pourcentage : la nouvelle valeur [0, 100] du PWM
     */
    static void setPourcentage(const uint8_t& pourcentage);

    /**
     * Ajustement du PWM (gauche)
     * 
     * \param pourcentage : la nouvelle valeur [0, 100] du PWM
     */
    static void setPourcentageGauche(const uint8_t& pourcentage);

    /**
     * Ajustement du PWM (droite)
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
     * Calcul de la valeur du registre OCRn (16 bit) selon le pourcentage
     * 
     * \param pourcentage : la nouvelle valeur [0, 100] du PWM
     */
    static uint16_t getValOCRnFromPourcentage(const uint8_t& pourcentage);


};

#endif // LIB_PWM_H

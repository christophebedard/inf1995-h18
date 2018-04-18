#ifndef LIB_PWM_H
#define LIB_PWM_H

/**
 * \file pwm.h
 * \brief declaration de la classe PWM
 * \author Christophe Bourque Bedard
 * \author Simon Moreau
 * \author Fares Ouaissa
 * \author Mohamed Saddik
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
     * Ajustement du PWM (gauche)
     * 
     * \param pourcentage : la nouvelle valeur [0, 100] du PWM
     */
    static void setPourcentageOCRnB(const uint8_t& pourcentage);

    /**
     * Ajustement du PWM (droite)
     * 
     * \param pourcentage : la nouvelle valeur [0, 100] du PWM
     */
    static void setPourcentageOCRnA(const uint8_t& pourcentage);

private:
    /**
     * Calcul de la valeur du registre OCRn (16 bit) selon le pourcentage
     * 
     * \param pourcentage : la nouvelle valeur [0, 100] du PWM
     * 
     * \return la valeur de OCRn correspondante
     */
    static uint16_t getValOCRnFromPourcentage(const uint8_t& pourcentage);

};

#endif // LIB_PWM_H

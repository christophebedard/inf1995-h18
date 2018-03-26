#ifndef LIB_PWM_H
#define LIB_PWM_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"
#include "delai.h"
#include "timer1.h"

/**
 * Initialisation du PWM
 */
void initPWM();

/**
 * Ajustement du PWM
 * 
 * \param pourcentage : la nouvelle valeur [0, 100] du PWM
 */
void ajustementPWM(const uint8_t& pourcentage);

void virageDroit(const uint8_t& pourcentage);

void virageGauche(const uint8_t& pourcentage);

#endif // LIB_PWM_H

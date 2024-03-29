#ifndef LIB_PWM_H
#define LIB_PWM_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"

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

#endif // LIB_PWM_H

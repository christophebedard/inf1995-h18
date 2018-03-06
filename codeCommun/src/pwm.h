#ifndef LIB_PWM_H
#define LIB_PWM_H

#include <avr/io.h>
#include <avr/interrupt.h>

void ajustementPWM (const int& pourcentage );

void SetUpPWM();

#endif // LIB_PWM_H

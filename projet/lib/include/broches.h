#ifndef LIB_BROCHES_H
#define LIB_BROCHES_H

/**
 * \file broches.h
 * \brief declaration des broches auxquelles les capteurs sont connectes
 * \author 
 * 
 * Broches  : [1,8]
 * Pins     : [0,7]
 * 
 * Pin = broche - 1
 */


/**
 * Macro pour transformer un numero de broche en numero de pin
 */
#define _BROCHE_TO_PIN(b) (b - 1)

/**
 * Broche sur laquelle le buzzer est connecte (1-8)
 */
#define BROCHE_BUZZER 7

/**
 * Broche PWM associee au moteur gauche (OC1B)
 */
#define BROCHE_MOTEUR_GAUCHE_PWM 5

/**
 * Broche PWM associee au moteur droit (OC1A)
 */
#define BROCHE_MOTEUR_DROIT_PWM 6

/**
 * Broche de direction associee au moteur gauche
 */
#define BROCHE_MOTEUR_GAUCHE_DIRECTION 7

/**
 * Broche de direction associee au moteur droit
 */
#define BROCHE_MOTEUR_DROIT_DIRECTION 8


#endif // LIB_BROCHES_H

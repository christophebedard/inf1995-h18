#ifndef LIB_BROCHES_H
#define LIB_BROCHES_H

/**
 * \file broches.h
 * \brief declaration des broches auxquelles les capteurs sont connectes
 * \author Christophe Bourque Bedard
 * \author Simon Moreau
 * \author Fares Ouaissa
 * \author Mohamed Saddik
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
 * Broche A sur laquelle la LED est connectee (1-8)
 */
#define BROCHE_LED_A 1

/**
 * Broche B sur laquelle la LED est connectee (1-8)
 */
#define BROCHE_LED_B 2

/**
 * Broches sur lesquelles la LED est connectee (1-8)
 */
#define BROCHES_LED (_BV(_BROCHE_TO_PIN(BROCHE_LED_A)) | _BV(_BROCHE_TO_PIN(BROCHE_LED_B)))

/**
 * Broche sur laquelle le bouton est connecte (1-8)
 */
#define BROCHE_BOUTON 3

/**
 * Broche sur laquelle le buzzer est connecte (1-8)
 */
#define BROCHE_BUZZER 4

/**
 * Broche sur laquelle le buzzer pour WAV est connecte (1-8)
 * OC0A
 */
#define BROCHE_BUZZER_WAV 4

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

/**
 * Broche CAN pour le Vo du capteur de distance gauche
 */
#define BROCHE_CAPTEUR_DISTANCE_GAUCHE 3

/**
 * Broche CAN pour le Vo du capteur de distance droit
 */
#define BROCHE_CAPTEUR_DISTANCE_DROIT 4


#endif // LIB_BROCHES_H

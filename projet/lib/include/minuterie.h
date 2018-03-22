#ifndef LIB_MINUTERIE_H
#define LIB_MINUTERIE_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"

/**
 * Initialisation du timer 1
 *
 * \param func : le pointeur vers la fonction de callback
 */
void initTimer1(func_t func);

/**
 * Initialisation du timer 2
 *
 * \param func : le pointeur vers la fonction de callback
 */
void initTimer2(func_t func);

/**
 * Debut du timer 1
 * 
 * \param duree : la duree de la minuterie en millisecondes
 */
void startTimer1(const uint16_t duree);

/**
 * Debut du timer 2
 * 
 * \param duree : la duree de la minuterie en millisecondes
 */
void startTimer2(const uint16_t duree);

/**
 * Arret du timer 1
 */
void stopTimer1();

/**
 * Arret du timer 2
 */
void stopTimer2();

#endif // LIB_MINUTERIE_H

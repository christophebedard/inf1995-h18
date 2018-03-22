#ifndef LIB_MINUTERIE_H
#define LIB_MINUTERIE_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"

/**
 * Initialisation de la minuterie
 *
 * \param func : le pointeur vers la fonction de callback
 */
void initMinuterie(func_t func);
void initMinuterie2(func_t func);

/**
 * Initialisation de la minuterie
 * 
 * \param duree : la duree de la minuterie en millisecondes
 */
void startMinuterie(const uint16_t duree);
void startMinuterie2(const uint16_t duree);

/**
 * Arret de la minuterie
 */
void stopMinuterie();

void stopMinuterie2();
#endif // LIB_MINUTERIE_H

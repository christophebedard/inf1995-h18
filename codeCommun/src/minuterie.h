#ifndef LIB_MINUTERIE_H
#define LIB_MINUTERIE_H

#include "defines.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/**
 * Initialisation de la minuterie
 */
void initMinuterie();

/**
 * Initialisation de la minuterie
 * 
 * \param duree : la duree de la minuterie en millisecondes
 */
void startMinuterie(const uint16_t duree);

/**
 * Arret de la minuterie
 */
void stopMinuterie();

#endif // LIB_MINUTERIE_H

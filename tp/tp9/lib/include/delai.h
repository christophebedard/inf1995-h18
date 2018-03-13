#ifndef LIB_DELAI_H
#define LIB_DELAI_H

#include <avr/io.h>
#include <util/delay.h>
#include "defines.h"

/**
 * Delai en microsecondes
 * 
 * \param us : nombre de microsecondes
 */
void waitForUs(uint16_t us);

/**
 * Delai en millisecondes
 * 
 * \param us : le nombre de millisecondes
 */
void waitForMs(uint16_t ms);

#endif // LIB_DELAI_H

#ifndef LIB_INTERRUPTION_H
#define LIB_INTERRUPTION_H

#include "defines.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/**
 * Declaration des types de trigger d'interruption
 */
enum TypesTriggerInterrupt
{
    RisingEdge,
    FallingEdge,
    RisingOrFallingEdge
};

/**
 * Initialisation de l'interruption
 * 
 * \param type : le type de trigger de l'interruption
 */
void initInterruption(const TypesTriggerInterrupt type);

/**
 * Initialisation de l'interruption par defaut
 */
void initInterruption();

#endif // LIB_INTERRUPTION_H

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
 */
void initInterruption(const TypesTriggerInterrupt type);

#endif // LIB_INTERRUPTION_H

#ifndef LIB_INTERRUPTION_H
#define LIB_INTERRUPTION_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "enums_structs.h"




/**
 * Declaration des types de trigger d'interruption
 */

enum TypesTriggerInterrupt
{
    RisingEdge,
    FallingEdge,
    RisingOrFallingEdge
};

enum Interrupteur
{
    Enfonce,
    Relache
};
/**
 * Initialisation de l'interruption
 * 
 * \param func : le pointeur vers la fonction de callback
 * \param type : le type de trigger de l'interruption (defaut : rising ou falling edge)
 */
void initInterruption(func_t func, const TypesTriggerInterrupt type = FallingEdge);


void trajetInterrupt();

void diagnosticInterrupt();

Interrupteur getEtat();

#endif // LIB_INTERRUPTION_H

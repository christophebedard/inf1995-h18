#ifndef LIB_INTERRUPTION_H
#define LIB_INTERRUPTION_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "enums_structs.h"
#include "defines.h"



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

/**
 * Interruption qui fait faire un virage de 180 degre au robot
 * 
 */
void trajetInterrupt();

/**
 * Interruption qui modifie l'etat de l'interrupteur 
 */
void diagnosticInterrupt();

/**
 * Fonction qui retourne la valeur de la variable globale etat
 */
Interrupteur getEtat();

#endif // LIB_INTERRUPTION_H

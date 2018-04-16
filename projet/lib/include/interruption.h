#ifndef LIB_INTERRUPTION_H
#define LIB_INTERRUPTION_H

/**
 * \file interruption.h
 * \brief declaration de la classe Interruption
 * \author 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"
#include "broches.h"
#include "enums_structs.h"

// declaration explicite des vecteurs d'interruption (afin de les friend)
extern "C" void INT0_vect(void) __attribute__((signal));
extern "C" void INT1_vect(void) __attribute__((signal));

/**
 * \class Interruption
 * \brief classe qui enveloppe (wrap) les interruptions
 */
class Interruption
{
public:
    /**
     * Initialisation de l'interruption INT0
     * 
     * \param funcInt0 : le pointeur vers la fonction de callback pour INT0
     * \param typeInt0 : le type de trigger de l'interruption pour INT0 (defaut : falling edge)
     */
    static void initInt0(func_t funcInt0, const TypesTriggerInterrupt typeInt0 = TypesTriggerInterrupt::FallingEdge);

    /**
     * Initialisation de l'interruption INT1
     * 
     * \param funcInt0 : le pointeur vers la fonction de callback pour INT1
     * \param typeInt0 : le type de trigger de l'interruption pour INT1 (defaut : falling edge)
     */
    static void initInt1(func_t funcInt1, const TypesTriggerInterrupt typeInt1 = TypesTriggerInterrupt::FallingEdge);

    /**
     * Ami : interruption du INT0
     */
    friend void ::INT0_vect(void);

    /**
     * Ami : interruption du INT1
     */
    friend void ::INT1_vect(void);

private:
    static func_t int0FuncPtr; //< variable du pointeur vers le callback INT0
    static func_t int1FuncPtr; //< variable du pointeur vers le callback INT1

};

#endif // LIB_INTERRUPTION_H

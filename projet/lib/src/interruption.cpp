#include "interruption.h"
#include "enums_structs.h"
#include <avr/io.h>
#include <avr/interrupt.h>
volatile Interrupteur etat = Relache;
func_t int0FuncPtr = nullptr; /**< variable du pointeur vers le callback INT0 */

ISR(INT0_vect)
{
    /// \todo assert != nullptr
    int0FuncPtr();

    // clear flag
    EIFR |= (1 << INTF0);
}

void initInterruption(func_t func, const TypesTriggerInterrupt type)
{
    // garde en memoire le pointeur vers la fonction de callback
    int0FuncPtr = func;

    cli();
    etat = Relache;
    // interruption externe sur INT0
    EIMSK |= (1 << INT0);

    // selon type de trigger specifie
    switch (type)
    {
        case RisingEdge:
            EICRA |= (1 << ISC00) | (1 << ISC01);
            break;
        case FallingEdge:
            EICRA |= (1 << ISC01);
            break;
        case RisingOrFallingEdge:
            EICRA |= (1 << ISC00);
            break;
        default:
            // interruption lors d'un rising ou falling edge
            EICRA |= (1 << ISC00);
    }

    sei();
}

Interrupteur getEtat()
{
    return etat;
}

void diagnosticInterrupt()
{
    if (etat == Relache)
        etat = Enfonce;
    else
        etat = Relache;
}


void trajetInterrupt()
{
    //vide avant trajet
}

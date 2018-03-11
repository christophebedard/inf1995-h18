#include "interruption.h"

func_t int0FuncPtr = nullptr; /**< variable du pointeur vers le callback INT0 */

ISR(INT0_vect)
{
    /// \todo assert != nullptr
    int0FuncPtr();
}

void initInterruption(func_t func, const TypesTriggerInterrupt type)
{
    // garde en memoire le pointeur vers la fonction de callback
    int0FuncPtr = func;

    cli();

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

    /// \todo mettre en parametre le mode de detection desire (falling, risinf, etc...)

    sei();
}

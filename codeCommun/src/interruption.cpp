#include "interruption.h"

void initInterruption(const TypesTriggerInterrupt type)
{
    cli();

    // interruption externe sur INT0
    EIMSK |= (1 << INT0);

    // selon type de trigger specifie
    switch (type)
    {
        case TypesTriggerInterrupt.RisingEdge:
            EICRA |= (1 << ISC00) | (1 << ISC01);
            break;
        case TypesTriggerInterrupt.FallingEdge:
            EICRA |= (1 << ISC01);
            break;
        case TypesTriggerInterrupt.RisingOrFallingEdge:
            EICRA |= (1 << ISC00);
            break;
        default:
            // interruption lors d'un rising ou falling edge
            EICRA |= (1 << ISC00);
    }

    /// \todo mettre en parametre le mode de detection desire (falling, risinf, etc...)

    sei();
}

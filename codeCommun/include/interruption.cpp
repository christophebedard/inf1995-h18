#include "interruption.h"

void initInterruption()
{
    cli();

    // interruption externe sur INT0
    EIMSK |= (1 << INT0);
    // interruption lors d'un rising ou falling edge
    EICRA |= (11 << ISC00);

    /// \todo mettre en parametre le mode de detection desire (falling, risinf, etc...)

    sei();
}

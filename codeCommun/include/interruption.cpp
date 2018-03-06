#include "interruption.h"

void InitialisationInterruption(){
    cli();

    EIMSK |= (1 << INT0);
    EICRA |= (11 << ISC00);
    //Configuration de l'interrupt pour detecter falling et rising edge (pour les push et release)
    // mettre en parametre le mode de detection desire (falling, risinf, etc...)
    sei();
}

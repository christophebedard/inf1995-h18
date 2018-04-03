#include "uart.h"
#include "delai.h"
#include "defines.h"
#include "enums_structs.h"
#include "capteurs_distance.h"
#include "interruption.h"
#include "moteurs.h"
#include "can.h"

int main()
{
    uint8_t bouton = 0x00;
    uint8_t instruction = 0xf5;
    UART::init();
    initInterruption(diagnosticInterrupt, RisingOrFallingEdge);
    Moteurs::init();
    UART::transmettre(1);
for(;;){
    UART::transmission(instruction);
    waitForMs(5);
    //etat interrupt
    if (getEtat() == Enfonce)
        UART::transmission(bouton);
    else
        UART::transmission(bouton + 1); 
    waitForMs(5);
    UART::transmission(instruction + 1);
    waitForMs(5);
    //distance gauche
    UART::transmission(CapteursDistance::getDistanceDroit());
    waitForMs(5);
    UART::transmission(instruction + 2);
    waitForMs(5);
    //distance droite
    UART::transmission(CapteursDistance::getDistanceGauche());
    waitForMs(5);
}   
    
       return 0;
}

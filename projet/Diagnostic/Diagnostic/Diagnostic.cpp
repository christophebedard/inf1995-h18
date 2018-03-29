#include "uart.h"
#include "delai.h"
#include "defines.h"
#include "info.h"
#include "capteurs_distance.h"
#include "interruption.h"
#include "moteurs.h"
volatile bool interrupt = false;

int main()
{
    UART::init();
    UART::initInterruption(&info::receiveInterrupt());
    interruption::initInterruption(&info::interrupt(), RisingOrFallingEdge);
    Moteurs::init();
    info::transmission(1);
for(;;){
    UART::transmission(0xf5);
    waitForMs(5);
    //etat interrupt
    UART:transmission(info::etat);
    /*
    if (info::etat == Enfonce)
        UART:transmission(0x00);
    else
        UART:transmission(0x01);*/ 
    //Si la transmission faite avant ne fonctionne pas on utilisera celle la
    waitForMs(5);
    UART::transmission(0xf6);
    waitForMs(5);
    //distance gauche
    UART::transmission(CapteursDistance::getDistanceDroite());
    waitForMs(5);
    UART::transmission(0xf7);
    waitForMs(5);
    //distance droite
    UART::transmission(CapteursDistance::getDistanceGauche());
    waitForMs(5);
}   
    
       return 0;
}

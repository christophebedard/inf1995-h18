#include "pwm.h"
#include "uart.h"
#include "buzzer.h"
#include "delai.h"
#include "memoire_24.h"
#include "defines.h"
#include "Info.h"
#include "Moteurs.h"

int main()
{
    DDRD = SORTIE:
    DDRB = SORTIE;
    DDRA = SORTIE;
    UART::init();
    Moteurs::init();
    Info::transmission(1);
for(;;){
    UART::transmission(0xf5);
    waitForMs(5);
    //etat interrupt
    waitForMs(5);
    UART::transmission(0xf6);
    waitForMs(5);
    //distance gauche
    waitForMs(5);
    UART::transmission(0xf7);
    waitForMs(5);
    //distance droite
    waitForMs(5);
}   
    //ce qui suit a mettre dans une interruption
    for (int i = 0; i < 2; i++){
        uint8_t instruction[i] = UART::reception();
        waitForMs(5)
    }
    switch instruction[0]:{
        case 0xfb:
            Info::transmission(1); 
            //Changer parametre à 0 si on utilise le robot vert, 1 pour gris
            break;
            
        case 0xfa:
            PORTA = instruction[1];
            //Valeur assignée au port A
            break;
            
        case 0xf9://droite
            if (instruction[1] >> 3 == 1){
                instruction[1] = (~instruction[1] + 0x01); //complement 2
                Moteurs::setDirectionMoteurDroit(DirectionMoteur::arriere);
            }
            else
                Moteurs::setDirectionMoteurDroit(DirectionMoteur::avant);
            Moteurs::setPourcentageDroite(instruction[1]);
            break;
    
        case 0xf8://gauche
            if (instruction[1] >> 3 == 1){
                instruction[1] = (~instruction[1] + 0x01); //complement 2
                Moteurs::setDirectionMoteurGauche(DirectionMoteur::arriere);
            }
            else
                Moteurs::setDirectionMoteurGauche(DirectionMoteur::avant);
            Moteurs::setPourcentageGauche(instruction[1]);
            break;
    }
   return 0;
}

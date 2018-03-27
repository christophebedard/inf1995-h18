#include "pwm.h"
#include "uart.h"
#include "buzzer.h"
#include "delai.h"
#include "memoire_24.h"
#include "defines.h"
#include "Info.h"

int main()
{
    DDRD = SORTIE:
    DDRB = SORTIE;
    DDRA = SORTIE;
    UART::init();
    for (int i = 0; i < 2; i++){
        uint8_t instruction[i] = UART::reception();
        waitForMs(5)
    }
    if (instruction[0] == 0x00)
        for(;;){
            Info::transmission(1); 
            //Changer parametre à 0 si on utilise le robot vert
        }
    
   return 0;
}

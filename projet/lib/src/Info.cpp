#include "info.h"
#include "defines.h"

static void transmission(int id)
{
    UART::transmit(0xf0); //Nom
        waitForMs(5);
        for (uint8_t i = 0; i < 12; i++){
            UART::transmit(INFO_NOM_ROBOT[i]);
            waitForMs(5);
        }
        UART::transmit(0xf1); //Equipe
        waitForMs(5);
        for (uint8_t i = 0; i < 5; i++){
            UART::transmit(INFO_EQUIPE[i]);
            waitForMs(5);
        }
        UART::transmit(0xf2); //Groupe
        waitForMs(5);
        for (uint8_t i = 0; i < 2; i++){
            UART::transmit(INFO_GROUPE[i]);
            waitForMs(5);
        }
        UART::transmit(0xf3); //Session
        waitForMs(5);
        for (uint8_t i = 0; i < 4; i++){
            UART::transmit(INFO_SESSION[i]);
            waitForMs(5);
        }
        UART::transmit(0xf4); //Couleur
        waitForMs(5);
        if (id == 1)
            couleur = COULEUR_ROBOT1;
        else if (id == 0)
            couleur = COULEUR_ROBOT2;
        UART::transmit(couleur);
}

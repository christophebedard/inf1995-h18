/**
 * \file copymem.h
 * \brief programme qui recoit du bytecode par UART (serieViaUSB) et qui l'ecrit en memoire
 * \author 
 */

#include "memoire_24.h"
#include "delai.h"
#include "uart.h"


int main()
{
    // sequence initiale
    DDRA = SORTIE;
    PORTA = ROUGE;
    waitForMs(250);
    PORTA = VERT;
    waitForMs(250);
    PORTA = ROUGE;
    waitForMs(250);
    PORTA = VERT;
    waitForMs(250);
    PORTA = ETEINT;

    // reception par UART et ecriture dans memoire
    UART::init();
    Memoire24CXXX mem;
    uint16_t adr = 0x00;
    
   /* uint16_t taille = 0x16;
    uint8_t tailleL = 0;
    tailleL |= taille ;
    uint8_t tailleH = 0;
    tailleH |= taille >> 8;
    mem.ecriture(adr++, tailleH);
    waitForMs(5);
    mem.ecriture(adr++, tailleL);
    waitForMs(5);
    uint8_t donnee[taille - 2];
    donnee[0] = 0x01;
    donnee[1] = 0x00;
    donnee[2] = 0x48;
    donnee[3] = 0x50;
    donnee[4] = 0x48;
    donnee[5] = 0x32;
    donnee[6] = 0x09;
    donnee[7] = 0x00;
    donnee[8] = 0xff;
    donnee[9] = 0x00;
    for (uint16_t i = 0; i < taille - 2; i++){
        mem.ecriture(adr++, donnee[i]);
        waitForMs(5);
    }*/
    // reception des deux premiers octets (taille)
    
    uint8_t tailleH = UART::reception();
    mem.ecriture(adr++, tailleH);
    waitForMs(5);
    uint8_t tailleL = UART::reception();
    mem.ecriture(adr++, tailleL);
    waitForMs(5);
    
    // calcul de la taille
    uint16_t taille = 0;
    taille |= tailleH << 8;
    taille |= tailleL;
    // reception et ecriture des autres octets
    for(uint16_t i = 2; i < taille; ++i)
    {
        
        uint8_t val = UART::reception();
        mem.ecriture(adr++, val);
        waitForMs(5);
    }
    
    // fin
    PORTA = VERT;

    return 0;
}

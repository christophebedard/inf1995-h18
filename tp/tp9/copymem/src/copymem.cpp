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

    // reception des deux premiers octets (taille)
    uint8_t tailleH = UART::reception();
    mem.ecriture(adr++, &tailleH);
    uint8_t tailleL = UART::reception();
    mem.ecriture(adr++, &tailleL);
    
    // calcul de la taille
    uint16_t taille |= tailleH << 8;
    taille |= tailleL;

    // reception et ecriture des autres octets
    for(uint16_t i = 2; i < taille; ++i)
    {
        uint8_t val = UART::reception();
        mem.ecriture(adr++, &val);
    }

    // fin
    PORTA = VERT;

    return 0;
}

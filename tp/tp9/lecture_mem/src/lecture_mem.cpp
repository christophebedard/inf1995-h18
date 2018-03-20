/**
 * \file lecture_mem.h
 * \brief programme qui lit les octets en memoire et les transmet par UART pour verification
 * \author 
 */

#include "memoire_24.h"
#include "delai.h"
#include "uart.h"
#include "debug.h"


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

    // transmission par UART et lecture dans memoire
    UART::init();
    Memoire24CXXX mem;

    uint16_t adr = 0x0;
    uint8_t buf[1];

    // lecture des octets de taille
    uint8_t tailleH = 0;
    uint8_t tailleL = 0;
    uint16_t taille = 0;
    mem.lecture(adr++, &tailleH);
    waitForMs(5);
    mem.lecture(adr++, &tailleL);
    waitForMs(5);
    taille = (tailleH << 8) | (tailleL);

    // lecture et transmission des octets
    // (le reset de l'adresse mene a la lecture des 2 premiers octets une deuxieme
    //   fois, mais cela permet de simplifier la boucle de transmission des octets)
    adr = 0x0;
    while(adr < taille)
    {
        // affichage de l'adresse
        if ((adr % 2) == 0)
        {
            Debug::out(adr, 16);
            Debug::out(" : ");
        }

        // lecture de l'octet
        mem.lecture(adr, buf);

        // transmission de l'octet
        Debug::out(buf[0], 16);

        // separateur
        if ((adr % 2) == 0)
        {
            Debug::out(" ");
        }
        else
        {
            Debug::out("\n");
        }

        adr++;
        waitForMs(5);
    }

    // transmission du nombre d'octets transmis (assez verbeux)
    Debug::out("adr fin = ");
    Debug::out(adr, 16);
    Debug::out(" / ");
    Debug::out(adr);

    // fin
    PORTA = VERT;

    return 0;
}

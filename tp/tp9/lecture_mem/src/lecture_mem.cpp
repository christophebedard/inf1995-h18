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
    uint16_t adr = 0x00;

    uint8_t buf[1];

    // lecture et transmission
    while(true)
    {
        mem.lecture(adr++, buf);
        Debug::out(*buf, 16);
    }

    // fin
    PORTA = VERT;

    return 0;
}

#define F_CPU 8000000
#include "librobot.a"


int main(){

    DDRA = 0x03;
    /*Sequence initiale*/
    PORTA = ROUGE;
    waitForMs(250);
    PORTA = VERT;
    waitForMs(250);
    PORTA = ROUGE;
    waitForMs(250);
    PORTA = VERT;
    waitForMs(250);
    PORTA = ETEINT;
    /*Debut interpretation*/
    initialisationUART();
    Memoire24CXXX M = Memoire24CXXX();
    uint8_t lire[] = {0};
    M.lecture(0x00, lire, 40);
    _delay_ms(5);
    for (uint8_t j=0; j < 255; j++ )
        transmissionUART (lire[j]); 
    return 0;
}

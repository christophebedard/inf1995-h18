#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "memoire_24.h"

int main(){
    const uint16_t VERT = 0x1;
    const uint16_t ROUGE = 0x2;
    DDRA = 0x03;
    uint8_t chaine[] = "*E*C*O*L*E* *P*O*L*Y*T*E*C*H*N*I*Q*U*E\0";
    Memoire24CXXX M = Memoire24CXXX();
    M.ecriture(0x00, chaine, 40);
    _delay_ms(10);
    uint8_t lire[] = {0};
    M.lecture(0x00, lire, 40);
    bool condition = true;
    for (int i = 0; i < 40; i++)
        if (chaine[i] != lire[i])
            condition = false;
    if (condition)
        PORTA = VERT;
    else
        PORTA = ROUGE;
    return 0;
}


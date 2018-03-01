#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "memoire_24.h"
void initialisationUART (void);
void transmissionUART ( uint8_t donnee );

int main(){
    initialisationUART();
    Memoire24CXXX M = Memoire24CXXX();
    uint8_t lire[] = {0};
    M.lecture(0x00, lire, 40);
    _delay_ms(5);
    for (uint8_t j=0; j < 255; j++ )
        transmissionUART (lire[j]);   
    
    for(;;) {}          //Sinon, le programme se repete
    
    return 0;
}

void initialisationUART (void) {

// 2400 bauds. Nous vous donnons la valeur des deux

// premier registres pour vous éviter des complications

UBRR0H = 0;

UBRR0L = 0xCF;

// permettre la reception et la transmission par le UART0

UCSR0A = (1 << RXC0) | (1 << TXC0) | (1<<UDRE0) ;

UCSR0B = (1 << RXEN0) | (1 << TXEN0) ;

// Format des trames: 8 bits, 1 stop bits, none parity

UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

}

void transmissionUART ( uint8_t donnee ) {

   /* Wait for empty transmit buffer */
   while ( !( UCSR0A & (1<<UDRE0)) )
      ;
   /* Put data into buffer, sends the data */
   UDR0 = donnee;
}

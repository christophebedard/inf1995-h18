/* Fichier : probleme1.cpp
* Auteur : Bourque Bédard Christophe  & Mohamed Saddik
* Date : 15 février 2018
*
* TP6 PB1
*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "memoire_24.h"

const uint8_t SORTIE = 0xff;
/*******************************************************************************
* Fonction d'initialisation UART. 
*******************************************************************************/
void initialisationUART ( void ) {
	DDRB = SORTIE;
	// 2400 bauds. Nous vous donnons la valeur des deux
	// premier registres pour vous éviter des complications
	UBRR0H = 0;
	
	UBRR0L = 0xCF;
	// permettre la reception et la transmission par le UART0
	UCSR0A = 0 ;
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0);
	// Format des trames: 8 bits, 1 stop bits, none parity
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00) ;
}

/*******************************************************************************
* Fonction d'initialisation UART. 
*******************************************************************************/
void transmissionUART ( uint8_t donnee ) {
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = donnee;
}

/*******************************************************************************
* Fonction principale. 
*******************************************************************************/
int main() {
	initialisationUART();
	
	Memoire24CXXX mem;
	
	uint16_t adress = 0x00; 
	uint8_t tableauLecture[1];
	
	mem.lecture(adress,tableauLecture);
	
	while (tableauLecture[0] != 0xFF) {
		transmissionUART(tableauLecture[0]);
		
		adress += 0x1;
		mem.lecture(adress,tableauLecture);
	}
	
	return 0;
}

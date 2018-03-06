#include "uart.h"

void initialisationUART()
{
	// 2400 bauds
	UBRR0H = 0;
	UBRR0L = 0xCF;
	// permettre la reception et la transmission par le UART0
	UCSR0A = 0 ;
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	// Format des trames: 8 bits, 1 stop bits, none parity
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

void transmissionUART(const uint8_t& donnee)
{
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = donnee;
}

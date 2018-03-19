/**
 * \file debug.cpp
 * \brief implementation de la classe UART
 * \author 
 */

#include "uart.h"

void UART::init()
{
	init(2400);
}

void UART::init(uint16_t rate)
{
	// selon le baud rate specifie
	// attention : >2400 semble causer trop d'erreurs de transmission
	UBRR0H = ((F_CPU / (16 * rate)) - 1) >> 8;
	UBRR0L = ((F_CPU / (16 * rate)) - 1);

	// reception et transmission
	UCSR0A = 0;
	UCSR0B |= _BV(RXEN0) | _BV(TXEN0);

	// format des trames : 8 bits
	// (asynchronous, 1 stop bit, none parity)
	UCSR0C |= _BV(UCSZ01) | _BV(UCSZ00);
}

void UART::transmission(const uint8_t& donnee)
{
	while(!(UCSR0A & _BV(UDRE0)));
	UDR0 = donnee;
}

void UART::transmission(const char* str)
{
	// transmission des caracteres un par un
	while (*str != '\0')
	{
		transmission((uint8_t)*str);
		++str;
	}
}

uint8_t UART::reception()
{
    uint8_t donnee;
    while(UCSR0A & _BV(UDRE0));
    donnee = UDR0;
    return donnee;
}

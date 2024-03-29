/**
 * \file debug.cpp
 * \brief implementation de la classe UART
 * \author Christophe Bourque Bedard
 * \author Simon Moreau
 * \author Fares Ouaissa
 * \author Mohamed Saddik
 */

#include "uart.h"


func_t UART::uart0RxCallback = nullptr;
func_t UART::uart0TxCallback = nullptr;

ISR(USART0_RX_vect)
{
    if (UART::uart0RxCallback != nullptr) UART::uart0RxCallback();
}

ISR(USART0_TX_vect)
{
    if (UART::uart0TxCallback != nullptr) UART::uart0TxCallback();
}

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
    UCSR0B |= _BV(RXEN0) | _BV(TXEN0) | _BV(RXCIE0);

    // format des trames : 8 bits
    // (asynchronous, 1 stop bit, none parity)
    UCSR0C |= _BV(UCSZ01) | _BV(UCSZ00);
}

void UART::setRxCallback(func_t func)
{
    uart0RxCallback = func;
}

void UART::setTxCallback(func_t func)
{
    uart0TxCallback = func;
}

void UART::transmission(const uint8_t& donnee)
{
    while(!(UCSR0A & _BV(UDRE0)));
    UDR0 = donnee;
    waitForMs(DELAI_UART_RX_TX);
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
    while(!(UCSR0A & _BV(RXC0)));
    waitForMs(DELAI_UART_RX_TX);
    return UDR0;
}

void UART::stop()
{
    UBRR0H = 0;
    UBRR0L = 0;
    UCSR0A = 0;
    UCSR0B &= ~(_BV(RXEN0) | _BV(TXEN0));
    UCSR0C &= ~(_BV(UCSZ01) | _BV(UCSZ00));
}

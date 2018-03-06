#ifndef LIB_UART_H
#define LIB_UART_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "memoire_24.h"

void initialisationUART ( void );

void transmissionUART ( uint8_t donnee );

#endif // LIB_UART_H

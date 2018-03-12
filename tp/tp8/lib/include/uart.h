#ifndef LIB_UART_H
#define LIB_UART_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"
#include "memoire_24.h"

/**
 * Initialisation du UART
 */
void initialisationUART();

/**
 * Transmission UART
 * 
 * \param donnee : l'octet a transmettre
 */
void transmissionUART(const uint8_t& donnee);

#endif // LIB_UART_H

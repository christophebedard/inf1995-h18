#ifndef LIB_DEBUG_H
#define LIB_DEBUG_H

/**
 * \file debug.h
 * \brief declaration de la classe Debug
 * \author 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"
#include "uart.h"

/**
 * \class Debug
 * \brief classe qui aide pour le debug
 */
class Debug
{
public:
    /**
     * Affichage nombre de base 10
     * 
     * \param nombre : le nombre a transmettre
     */
    static void out(const uint8_t& nombre);

    /**
     * Affichage nombre
     * 
     * \param nombre : le nombre a transmettre
     * \param base : la base du nombre
     */
    static void out(const uint8_t& nombre, const uint8_t& base);

    /**
     * Affichage string
     * 
     * \param str : le pointeur vers la string a transmettre
     */
    static void out(const char* str);

};

#endif // LIB_UART_H

#ifndef LIB_UART_H
#define LIB_UART_H

/**
 * \file uart.h
 * \brief declaration de la classe UART
 * \author 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"
#include "memoire_24.h"

/**
 * \class UART
 * \brief classe qui enveloppe (wrap) le UART
 */
class UART
{
public:
    /**
     * Initialisation du UART par defaut
     */
    static void init();

    /**
     * Initialisation du UART
     * 
     * \param rate : le baud rate
     */
    static void init(uint16_t rate);
    
    /**
     * Initialisation de l'interruption pour le UART
     * 
     *  \param func : la fonction qui gère l'interruption
     */
    static void initInterruption(func_t func);
    
    /**
     * Transmission UART
     * 
     * \param donnee : l'octet a transmettre
     */
    static void transmission(const uint8_t& donnee);

    /**
     * Transmission UART
     * 
     * \param str : le pointeur vers la string a transmettre
     */
    static void transmission(const char* str);

    /**
     * Reception UART
     * 
     * \return la donnee recue
    */
    static uint8_t reception();

    /**
     * Arret du UART
     */
    static void stop();

};

#endif // LIB_UART_H

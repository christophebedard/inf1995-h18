#ifndef LIB_UART_H
#define LIB_UART_H

/**
 * \file uart.h
 * \brief declaration de la classe UART
 * \author Christophe Bourque Bedard
 * \author Simon Moreau
 * \author Fares Ouaissa
 * \author Mohamed Saddik
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"
#include "enums_structs.h"
#include "delai.h"


///< delai apres reception ou transmission (ms)
#define DELAI_UART_RX_TX 5


// declaration explicite des vecteurs d'interruption (afin de les friend)
extern "C" void USART0_RX_vect(void) __attribute__((signal));
extern "C" void USART0_TX_vect(void) __attribute__((signal));


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
     * Reglage de la fonction de callback pour RX
     * 
     * \param func : le pointeur vers la fonction de callback
     */
    static void setRxCallback(func_t func);

    /**
     * Reglage de la fonction de callback pour TX
     * 
     * \param func : le pointeur vers la fonction de callback
     */
    static void setTxCallback(func_t func);
    
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

    /**
     * Ami : interruption du RX du USART0
     */
    friend void ::USART0_RX_vect(void);

    /**
     * Ami : interruption du RX du USART0
     */
    friend void ::USART0_TX_vect(void);

private:
    static func_t uart0RxCallback; ///< le pointeur vers la fonction de rappel pour RX
    static func_t uart0TxCallback; ///< le pointeur vers la fonction de rappel pour TX

};

#endif // LIB_UART_H

#ifndef LIB_DEBUG_H
#define LIB_DEBUG_H

/**
 * \file debug.h
 * \brief declaration de la classe Debug
 * \author Christophe Bourque Bedard
 * \author Simon Moreau
 * \author Fares Ouaissa
 * \author Mohamed Saddik
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"
#include "enums_structs.h"
#include "time.h"
#include "uart.h"

/**
 * \class Debug
 * \brief classe qui aide pour le debug
 * \todo implemente un buffer dans UART pour empecher que les transmissions viennent ralentir le programme
 */
class Debug
{
public:
    /**
     * Initialisation de Debug (== initialisation du UART)
     * (devrait etre appele au debut du programme afin 
     *  d'etre utilise par toutes les classes)
     */
    static void init();

    /**
     * Affichage nombre (8 bits) de base 10
     * 
     * \param nombre : le nombre a transmettre
     */
    static void out(const uint8_t& nombre);

    /**
     * Affichage nombre (16 bits) de base 10
     * 
     * \param nombre : le nombre a transmettre
     */
    static void out(const uint16_t& nombre);

    /**
     * Affichage nombre (8 bits)
     * 
     * \param nombre : le nombre a transmettre
     * \param base : la base du nombre
     */
    static void out(const uint8_t& nombre, const uint8_t& base);

    /**
     * Affichage nombre (16 bits)
     * 
     * \param nombre : le nombre a transmettre
     * \param base : la base du nombre
     */
    static void out(const uint16_t& nombre, const uint16_t& base);

    /**
     * Affichage prescaler
     * 
     * \param pre : le prescaler a transmettre
     */
    static void out(const Prescaler pre);

    /**
     * Affichage temps
     * 
     * \param t : le temps a transmettre
     */
    static void out(const Time& t);

    /**
     * Affichage string
     * 
     * \param str : le pointeur vers la string a transmettre
     */
    static void out(const char* str);

};

#endif // LIB_DEBUG_H

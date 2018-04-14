#ifndef LIB_HORLOGE_H
#define LIB_HORLOGE_H

/**
 * \file horloge.h
 * \brief declaration de la classe Horloge
 * \author 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"
#include "broches.h"
#include "timer0.h"
#include "time.h"
#include "debug.h"

/**
 * \class Horloge
 * \brief classe qui enveloppe (wrap) le timer0 pour encapsuler le temps
 *      plus ou moins inspire de timer.h :
 *          https://www.nongnu.org/avr-libc/user-manual/time_8h_source.html
 */
class Horloge
{
public:
    /**
     * Initialisation du timer
     */
    static void init();

    /**
     * Ami : callback 1 Hz
     */
    friend void callback1Hz();

    /**
     * Ami : callback 1 MHz
     * incremente le temps de 1 ms
     */
    friend void callback1MHz();

    /**
     * Appelle Debug::out() pour afficher le temps actuel
     */
    static void debug();

private:
    static Time relTime_; ///< le temps depuis l'initialisation

};

#endif // LIB_HORLOGE_H

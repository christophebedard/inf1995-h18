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
     * Accesseur pour le temps absolu
     * (depuis l'appel a init(), probablement)
     * 
     * \return le temps absolu
     */
    static Time getTime();

    /**
     * Verifie s'il s'est ecoule deltaT depuis refT
     * 
     * \param refT : le temps de reference (initial)
     * \param deltaT : la difference de temps a verifier
     * 
     * \return le resultat de la comparaison
     */
    static bool isEcoule(const Time& refT, const Time& deltaT);

    /**
     * Verifie s'il s'est ecoule deltaT depuis refT selon absT
     * 
     * \param refT : le temps de reference (initial)
     * \param deltaT : la difference de temps a verifier
     * 
     * \return le resultat de la comparaison
     */
    static bool isEcoule(const Time& refT, const Time& deltaT, const Time& absT);

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
    static Time absTime_; ///< le temps depuis l'initialisation

    /**
     * Incremente le temps absolue de 1 dixieme de seconde
     */
    static void systemTick();

};

#endif // LIB_HORLOGE_H

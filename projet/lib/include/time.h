#ifndef LIB_TIME_H
#define LIB_TIME_H

/**
 * \file time.h
 * \brief declaration de la classe Time
 * \author 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"
#include "broches.h"
#include "timer0.h"
#include "debug.h"

#define TIME_NB_MS 1000
#define TIME_NB_SEC 60
#define TIME_NB_MIN 60
#define TIME_NB_HEU 24

/**
 * Definition de temps
 */
struct tm_t
{
    uint8_t tm_ms; ///< nombre de millisecondes
    uint8_t tm_sec; ///< nombre de secondes
    uint8_t tm_min; ///< nombre de minutes
    uint8_t tm_heure; ///< nombre d'heures
};

/**
 * \class Time
 * \brief classe qui enveloppe (wrap) le timer0 pour encapsuler le temps
 *      plus ou moins inspire de timer.h :
 *          https://www.nongnu.org/avr-libc/user-manual/time_8h_source.html
 */
class Time
{
public:
    /**
     * Initialisation du timer
     */
    static void init();

    static tm_t tm(uint8_t ms, uint8_t sec, uint8_t min, uint8_t heu);

    /**
     * Accesseur pour le temps actuel
     * 
     * \return le temps actuel (tm_t)
     */
    static tm_t getTime();

    /**
     * Verifie s'il s'est ecoule deltaTime depuis initTime
     * 
     * \param initTime : le temps de reference
     * \param deltaTime : la difference de temps
     * 
     * \return le resultat de la comparaison
     */
    static bool isEcoule(tm_t initTime, tm_t deltaTime);

    /**
     * Verifie si deltaTime depuis initTime est plus grand que refTime
     * 
     * \param initTime : le temps de reference
     * \param deltaTime : la difference de temps
     * \param refTime : le temps de reference
     * 
     * \return le resultat de la comparaison
     */
    static bool isEcoule(tm_t initTime, tm_t deltaTime, tm_t refTime);

    static tm_t add(tm_t t1, tm_t t2);

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

    /**
     * Appelle Debug::out() pour afficher un temps
     * 
     * \param t : le temps a afficher
     */
    static void debug(tm_t t);

private:
    static tm_t relTime_; ///< le temps depuis l'initialisation

    /**
     * Incremente le temps de 1 ms
     */
    static void systemTick();

};

#endif // LIB_TIME_H

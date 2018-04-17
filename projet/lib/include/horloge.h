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

///< la valeur du "prostcaler" logiciel \todo ameliorer justesse
#define POSTSCALER 3


/**
 * \class Horloge
 * \brief classe qui enveloppe (wrap) le timer0 pour encapsuler le temps
 *      * plus ou moins inspire de timer.h :
 *          https://www.nongnu.org/avr-libc/user-manual/time_8h_source.html
 *      * defaut de l'implementation : erreur au niveau de la frequence (voir init())
 */
class Horloge
{
public:
    /**
     * Initialisation du timer
     */
    static void init();
    
    /**
     * Reinitalisation du timer
     */
    static void reinitialiser();
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
     * Ami : callback 122 Hz
     */
    friend void callback122Hz();

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

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

#define TIME_NB_DIX 10
#define TIME_NB_SEC 60
#define TIME_NB_MIN 60


/**
 * \class Time
 * \brief classe qui represente un temps
 *      plus ou moins inspire de timer.h :
 *          https://www.nongnu.org/avr-libc/user-manual/time_8h_source.html
 * supporte : +, >
 */
class Time
{
public:
    /**
     * Constructeur par defaut (zero)
     */
    Time();

    /**
     * Constructeur par parametres
     * 
     * \param dix : le nombre de dixiemes de secondes
     * \param sec : le nombre de secondes
     * \param min : le nombre de minutes
     */
    Time(uint8_t dix, uint8_t sec, uint8_t min);

    /**
     * Destructeur
     */
    ~Time();

    /**
     * Incremente le temps de 1 ms
     */
    static void tick();

    /**
     * Appelle Debug::out() pour afficher le temps
     */
    void debug();

    /**
     * Surcharge d'operateur + (adition)
     * 
     * \param d : l'objet a droite
     * 
     * \return le resultat de l'adition
     */
    Time& operator+(Time d);

    /**
     * Surcharge d'operateur > (plus grand)
     * 
     * \param d : l'objet a droite
     * 
     * \return le resultat de la comparaison
     */
    bool operator>(Time d);

private:
    uint8_t dix_;   ///< nombre de dixiemes de seconde
    uint8_t sec_;   ///< nombre de secondes
    uint8_t min_;   ///< nombre de minutes

};

#endif // LIB_TIME_H

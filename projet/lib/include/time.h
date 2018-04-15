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
 * supporte : +, =, >, <, >=, <=
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
     * Constructeur par copie
     * 
     * \param t : l'objet a copier
     */
    Time(const Time& t);

    /**
     * Destructeur
     */
    ~Time();

    /**
     * Incremente le temps de 1 ms
     */
    void tick();

    /**
     * Surcharge d'operateur = (assignation)
     * 
     * \param t : l'objet a assigner
     */
    Time& operator=(const Time& t);

    /**
     * Surcharge d'operateur < (plus petit)
     * 
     * \param g : l'objet de gauche
     * \param d : l'objet de droite
     * 
     * \return le resultat de la comparaison
     */
    friend bool operator<(const Time& g, const Time& d);

    friend bool operator>(const Time& g, const Time& d);
    friend bool operator<=(const Time& g, const Time& d);
    friend bool operator>=(const Time& g, const Time& d);

    /**
     * Surcharge d'operateur + (adition)
     * 
     * \param d : l'objet a droite
     * 
     * \return le resultat de l'adition (par copie)
     */
    friend Time operator+(const Time& g, const Time& d);

    /**
     * Surcharge d'operateur ++ (increment)
     */
    Time& operator++(int);

    uint8_t getDix() const;
    uint8_t getSec() const;
    uint8_t getMin() const;

private:
    uint8_t nDix_;   ///< nombre de dixiemes de seconde
    uint8_t nSec_;   ///< nombre de secondes
    uint8_t nMin_;   ///< nombre de minutes

};

#endif // LIB_TIME_H

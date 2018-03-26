#ifndef LIB_CHANSONS_H
#define LIB_CHANSONS_H

/**
 * \file chansons.h
 * \brief declaration de chansons
 * \author 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"
#include "enums_structs.h"

/**
 * \class Chansons
 * \brief classe qui contient les donnees pour les chansons
 */
class Chansons
{
public:
    static ChansonMusique chansonMario;         ///< chanson theme de Mario
    static ChansonMusique chansonTeletubbies;   ///< chanson theme des Teletubbies (mais non reconnaissable)
};

#endif // LIB_CHANSONS_H

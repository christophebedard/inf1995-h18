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
    static ChansonMusique chansonMario;
    static ChansonMusique chansonTeletubbies;
};

#endif // LIB_CHANSONS_H

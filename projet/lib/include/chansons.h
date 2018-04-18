#ifndef LIB_CHANSONS_H
#define LIB_CHANSONS_H

/**
 * \file chansons.h
 * \brief declaration de chansons
 * \author Christophe Bourque Bedard
 * \author Simon Moreau
 * \author Fares Ouaissa
 * \author Mohamed Saddik
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"
#include "enums_structs.h"
#include "notes_midi.h"


/**
 * \class Chansons
 * \brief classe qui contient les donnees pour les chansons
 */
class Chansons
{
public:
    static ChansonMusique mario;                     ///< chanson theme de Mario
    static ChansonMusique starWarsMarcheImperiale;   ///< chanson de Star Wars : Marche Imperiale
    static ChansonMusique twentieth;
};

#endif // LIB_CHANSONS_H

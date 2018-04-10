#ifndef LIB_BOUTON_H
#define LIB_BOUTON_H

/**
 * \file bouton.h
 * \brief declaration de la classe Bouton
 * \author 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"
#include "broches.h"
#include "enums_structs.h"
#include "interruption.h"

/**
 * \class Bouton
 * \brief classe qui enveloppe (wrap) le bouton
 */
class Bouton
{
public:
    /**
     * Initialisation du bouton
     * 
     * \param utiliseInterruption : le flag pour le fonctionnement (true : par interruption; false : par polling)
     */
    static void init(bool utiliseInterruption = false);

    /**
     * Accesseur pour l'etat du bouton
     * 
     * \return l'etat du bouton
     */
    static EtatBouton getEtat();

    /**
     * Ami : fonction de callback pour l'interruption du bouton
     */
    friend void callbackInterruptionBouton();

private:
    static volatile EtatBouton etat_; ///< l'etat actuelle du bouton
    static bool utiliseInterruption_; ///< le flag de fonctionnement du bouton

};

#endif // LIB_BOUTON_H

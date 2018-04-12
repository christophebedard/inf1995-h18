#ifndef LIB_TRAJET_H
#define LIB_TRAJET_H

/**
 * \file trajet.h
 * \brief declaration de la classe Trajet
 * \author 
 */

#include "pwm.h"
#include "uart.h"
#include "buzzer.h"
#include "delai.h"
#include "memoire_24.h"
#include "defines.h"
#include "capteurs_distance.h"
#include "controle_moteurs.h"
#include "enums_structs.h"

///< la tolerance pour la distance du mur initial 
#define MUR_INITIAL_DISTANCE_TOL 30

/**
 * \class Trajet
 * \brief classe qui definit notre trajet 
 */
class Trajet
{
public:
    /**
     * Initlialisation et execution en boucle inifinie
     */
    static void execute();

    /**
     * Ami : le callback apres detection d'un poteau
     */
    friend void poteauDetecte();

    /**
     * Ami : le callback pour l'execution du demi tour
     */
    friend void demiTour();

private:
    static bool droitChangementCote_;   ///< le flag pour le droit de changer de cote
    static CoteMur mur_;                ///< le mur suivi actuellement
    
    static bool getDroitChangementCote();
    static void setDroitChangementCote(bool droitChangementCote);
    static CoteMur getCoteSuivi();
    static void setCoteSuivi(CoteMur mur);

    /**
     * Initlialisation
     */
    static void init();

    static void changerCoteDroit(uint8_t PourcentageDroit, uint8_t PourcentageGauche);
    static void changerCoteGauche(uint8_t PourcentageDroit, uint8_t PourcentageGauche);
    static void ajusterDistance(uint8_t pourcentage);

};

#endif // LIB_TRAJET_H

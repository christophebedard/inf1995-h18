#ifndef LIB_TRAJET_H
#define LIB_TRAJET_H

/**
 * \file trajet.h
 * \brief declaration de la classe Trajet
 * \author Simon Moreau
 * \author Mohamed Saddik
 * \author Fares Ouaissa
 * \author Christophe Bourque Bedard
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "delai.h"
#include "defines.h"
#include "enums_structs.h"
#include "capteurs_distance.h"
#include "controle_moteurs.h"
#include "buzzer.h"
#include "bouton.h"
#include "horloge.h"
#include "debug.h"

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



private:
    static EtatTrajet etatActuel_;      ///< l'etat actuel du trajet
    static bool droitChangementCote_;   ///< le flag pour le droit de changer de cote
    static CoteMur mur_;                ///< le mur suivi actuellement
    static bool enCoursAjustement_;
    static uint8_t distancePrecedenteGauche_;///< la distance precedente a gauche
    static uint8_t distancePrecedenteDroit_;///< la distance precedente a gauche
    static bool isObjetDetectePrecedemment_; ///< le flag pour se souvenir de si on avait detecte un objet precedemment

    static void setEtat(EtatTrajet nouvEtat);
    static bool isObjetDetecte(uint8_t dist);
    static bool getEnCoursAjustement();
    static void setEnCoursAjustement(bool ajustement);
    static bool getDroitChangementCote();
    static void setDroitChangementCote(bool droitChangementCote);
    static CoteMur getCoteSuivi();
    static void setCoteSuivi(CoteMur mur);

    static void buzzerPoteauDetecte();
    static void buzzerChangementMur();
    static void buzzerSelectionMur(CoteMur cote);

    /**
     * Initlialisation
     */
    static void init();

    /**
     * Execution d'un demi tour
     */
    static void demiTour();

    /**
     * Selectionne le mur initial
     * 
     * \param gauche : la distance du capteur de distance gauche
     * \param droit : la distance du capteur de distance droit
     * 
     * \return le mur choisit
     */
    static CoteMur selectionMurInitial(uint8_t gauche, uint8_t droit);

    /**
     * Mise a jour de la DEL selon l'etat d'ajustement de la position du robot
     * 
     * \param enCoursAjustement : booleen (true si le robot s'ajuste)
     */
    static void updateDelAjustement(bool enCoursAjustement);

};

#endif // LIB_TRAJET_H

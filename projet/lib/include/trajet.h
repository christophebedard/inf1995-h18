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
    static EtatTrajet etatActuel_;              ///< l'etat actuel du trajet
    static bool droitChangementCote_;           ///< le flag pour le droit de changer de cote
    static CoteMur mur_;                        ///< le mur suivi actuellement
    static bool enCoursAjustement_;             ///< le flag pour signifier un ajustement
    static uint8_t distancePrecedenteGauche_;   ///< la distance precedente a gauche
    static uint8_t distancePrecedenteDroit_;    ///< la distance precedente a gauche
    static bool isObjetDetectePrecedemment_;    ///< le flag pour se souvenir de si on avait detecte un objet precedemment

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
     * Buzzer pour signifier la detection d'un poteau
     */
    static void buzzerPoteauDetecte();
    
    /**
     * Buzzer pour signifier le changement de mur
     */
    static void buzzerChangementMur();
    
    /**
     * Buzzer pour signifier la selection d'un mur
     * 
     * \param cote : le cote du mur choisi
     */
    static void buzzerSelectionMur(CoteMur cote);

    /**
     * Mise a jour de la DEL selon l'etat d'ajustement de la position du robot
     * 
     * \param enCoursAjustement : booleen (true si le robot s'ajuste)
     */
    static void updateDelAjustement(bool enCoursAjustement);

    /**
     * Mutateur pour l'etat du trajet
     * 
     * \param nouvEtat : le nouvel etat
     */
    static void setEtat(EtatTrajet nouvEtat);
    
    /**
     * Accesseur pour le flag d'ajustement en cours
     * 
     * \return le flag d'ajustement en cours
     */
    static bool getEnCoursAjustement();
    
    /**
     * Mutateur pour le flag d'ajustement en cours
     * 
     * \param ajustement : la nouvelle valeur du flag d'ajustement en cours
     */
    static void setEnCoursAjustement(bool ajustement);
    
    /**
     * Accesseur pour le flag du droit de changement de cote
     * 
     * \return le flag du droit de changement de cote
     */
    static bool getDroitChangementCote();
    
    /**
     * Mutateur pour le flag du droit de changement de cote
     * 
     * \param droitChangementCote : la nouvelle valeur pour le flag du droit de changement de cote
     */
    static void setDroitChangementCote(bool droitChangementCote);
    
    /**
     * Accesseur pour le cote suivi
     * 
     * \return le cote suivi
     */
    static CoteMur getCoteSuivi();
    
    /**
     * Mutateur pour le cote suivi
     * 
     * \param mur : le nouveau cote suivi
     */
    static void setCoteSuivi(CoteMur mur);

    /**
     * Methode pour definir une detection selon une distance
     * 
     * \param dist : la distance a interpreter
     * 
     * \return le resultat (true : objet detecte)
     */
    static bool isObjetDetecte(uint8_t dist);

};

#endif // LIB_TRAJET_H

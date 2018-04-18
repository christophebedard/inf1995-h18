#ifndef LIB_CONTROLE_MOTEURS_H
#define LIB_CONTROLE_MOTEURS_H

/**
 * \file controleur_moteurs.h
 * \brief declaration de la classe ControleMoteurs
 * \author Christophe Bourque Bedard
 * \author Simon Moreau
 * \author Fares Ouaissa
 * \author Mohamed Saddik
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include "enums_structs.h"
#include "moteurs.h"
#include "capteurs_distance.h"
#include "debug.h"


// constantes pour le suivi de mur
#define SUIVI_MUR_DISTANCE  15  ///< la distance a laquelle on suit le mur
#define SUIVI_MUR_VIT_LIN   5  ///< la vitesse lineaire avec laquelle on suit le mur
#define SUIVI_MUR_TOL       3   ///< la tolerance sur l'erreur de la distance avec le mur

// constantes pour le demi tour
#define DEMI_TOUR_VITESSE_ANG           50      ///< la vitesse angulaire pour faire le demi tour
#define DEMI_TOUR_ATTENTE               1600    ///< le delai d'attente pour effectuer le demi tour
#define DEMI_TOUR_IMPULSION_VITESSE_ANG 45      ///< la vitesse angulaire pour l'impulsion d'arret
#define DEMI_TOUR_ATTENTE_IMPULSION     100     ///< le delai d'attente pour l'impulsion d'arret


/**
 * \class ControleMoteurs
 * \brief classe qui enveloppe (wrap) la classe Moteurs pour les controler
 * 
 * Notes :
 *      * vitesse lineaire positive : le robot avance
 *      * vitesse angulaire positive : le robot tourne dans le sens anti-horaire, a sa gauche
 */
class ControleMoteurs
{
public:
    /**
     * Initialisation du controleur
     */
    static void init();

    /**
     * Mise a jour des vitesses pour suivi de mur
     * \todo experimental
     * \param murSuivi : le mur suivi
     * \param cmd : la commande (distance par rapport au mur voulue)
     * \param vitLin : la vitesse lineaire a utiliser
     * \param tolErr : la tolerance d'erreur
     * 
     * \return l'erreur de distance
     */
     static uint8_t updateSuiviMur(CoteMur murSuivi, uint8_t cmd, uint8_t vitLin, uint8_t tolErr, const bool& changementEnCours);

    /**
     * Execution d'un demi tour
     * (bloquant)
     * \todo experimental
     * \param mur : le mur suivi au moment du demi tour
     */
    static void doDemiTour(CoteMur mur);

    /**
     * Reglage des vitesses et update
     * 
     * \param vitLin : la vitesse lineaire absolue
     * \param dirLin : la direction de la vitesse lineaire
     * \param vitAng : la vitesse angulaire absolue
     * \param dirAng : la direction de la vitesse angulaire (+ = anti-horaire; - = horaire)
     */
    static void setVitesses(uint8_t vitLin, DirectionMoteur dirLin, uint8_t vitAng, DirectionMoteur dirAng);

private:
    static uint8_t vitesseLineaire_;            ///< la vitesse lineaire absolue
    static uint8_t vitesseAngulaire_;           ///< la vitesse angulaire absolue
    static DirectionMoteur directionLineaire_;  ///< la direction de la vitesse lineaire
    static DirectionMoteur directionAngulaire_; ///< la direction de la vitesse angulaire (+ = anti-horaire; - = horaire)
    static int typeUpdate_;
    /**
     * Reglage de la vitesse lineaire
     * 
     * \param vitLin : la vitesse lineaire absolue
     * \param dirLin : la direction de la vitesse lineaire
     */
    static void setVitesseLineaire(uint8_t vitLin, DirectionMoteur dirLin);

    /**
     * Reglage de la vitesse angulaire
     * 
     * \param vitAng : la vitesse angulaire absolue
     * \param dirAng : la direction de la vitesse angulaire (+ = anti-horaire; - = horaire)
     */
    static void setVitesseAngulaire(uint8_t vitAng, DirectionMoteur dirAng);

    /**
     * Reglage des vitesses
     * 
     * \param vitGauche[out] : la vitesse du moteur gauche
     * \param vitDroit[out] : la vitesse du moteur droit
     * \param dirGauche[out] : la direction du moteur gauche
     * \param dirDroi[out] : la direction du moteur droit
     */
    static void calculVitessesMoteurs(uint8_t* vitGauche, uint8_t* vitDroit, DirectionMoteur* dirGauche, DirectionMoteur* dirDroit);

    /**
     * Calcul des vitesses des moteurs et envoit des donnees aux moteurs
     */
    static void updateMoteurs();
};

#endif // LIB_CONTROLE_MOTEURS_H

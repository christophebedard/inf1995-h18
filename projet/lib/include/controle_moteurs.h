#ifndef LIB_CONTROLE_MOTEURS_H
#define LIB_CONTROLE_MOTEURS_H

/**
 * \file controleur_moteurs.h
 * \brief declaration de la classe ControleMoteurs
 * \author 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include "enums_structs.h"
#include "moteurs.h"
#include "capteurs_distance.h"

// constantes pour le suivi de mur
#define SUIVI_MUR_DISTANCE  15  ///< la distance a laquelle on suit le mur
#define SUIVI_MUR_VIT_LIN   8  ///< la vitesse lineaire avec laquelle on suit le mur
#define SUIVI_MUR_TOL       3   ///< la tolerance sur l'erreur de la distance avec le mur

// constantes pour le demi tour
#define DEMI_TOUR_VITESSE_ANG           50      ///< la vitesse angulaire pour faire le demi tour
#define DEMI_TOUR_ATTENTE               2200    ///< le delai d'attente pour effectuer le demi tour
#define DEMI_TOUR_IMPULSION_VITESSE_ANG 50      ///< la vitesse angulaire pour l'impulsion d'arret
#define DEMI_TOUR_ATTENTE_IMPULSION     100     ///< le delai d'attente pour l'impulsion d'arret

// constantes pour le contournement
#define CONTOURNEMENT_VITESSE_LIN       15      ///< la vitesse lineaire pour un contournement
#define CONTOURNEMENT_VITESSE_ANG       12      ///< la vitesse angulaire absolue pour un contournement
#define CONTOURNEMENT_ATTENTE           5000    ///< le delai d'attente pour effectuer le contournement

// constantes pour le changement de mur
#define CHANGEMENT_VITESSE_LIN    30

#define CHANGEMENT_VITESSE_ANG    20

#define CHANGEMENT_ATTENTE        800

#define CHANGEMENT_ATTENTE_RETOUR 700

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
     * Mise a jour des vitesses pour changement de cote
     * \todo experimental
     * \param nouvMur : le nouveau mur vers lequel aller
     */
    static void updateChangementCote(CoteMur nouvMur);

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
     static uint8_t updateSuiviMur(CoteMur murSuivi, uint8_t cmd, uint8_t vitLin, uint8_t tolErr);

    /**
     * Execution du contournement d'un mur
     * (bloquant)
     * \todo experimental
     * \param murCont : le mur a contourner
     */
    static void doContournementMur(CoteMur murCont);

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

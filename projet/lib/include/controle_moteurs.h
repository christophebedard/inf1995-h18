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
     * Mise a jour des vitesses pour contourner le mur
     * \todo experimental
     * \param murSuivi : le mur a contourner
     */
    static void updateContournementMur(CoteMur murSuivi);

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
     */
    static void updateSuiviMur(CoteMur murSuivi, uint8_t cmd, uint8_t vitLin, uint8_t tolErr);

    /**
     * Execution d'un demi tour
     * \todo experimental
     * \param mur : le mur suivi au moment du demi tour
     */
    static void doDemiTour(CoteMur mur);

    /**
     * Calcul des vitesses des moteurs et envoit des donnees aux moteurs
     */
    static void updateMoteurs();

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

};

#endif // LIB_CONTROLE_MOTEURS_H

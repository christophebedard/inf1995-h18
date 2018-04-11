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
     * Mise a jour du suivi de mur
     * \todo experimental
     * \param 
     */
    static void updateSuiviMur(Murs mur, uint8_t cmd, uint8_t vitLin, uint8_t thresErr);

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

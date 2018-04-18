#ifndef LIB_CAPTEURS_DISTANCE_H
#define LIB_CAPTEURS_DISTANCE_H

/**
 * \file capteurs_distance.h
 * \brief declaration de la classe CapteursDistance
 * \author Christophe Bourque Bedard
 * \author Simon Moreau
 * \author Fares Ouaissa
 * \author Mohamed Saddik
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "broches.h"
#include "can.h"
#include "debug.h"


/**
 * Valeur CAN valide minimale (tres grosse distance)
 * selon etalonnage_capteur_distance.py
 */
#define CAPTEUR_DISTANCE_CAN_VAL_MIN 100
/**
 * Valeur CAN valide maximale (tres petite distance)
 * selon etalonnage_capteur_distance.py
 */
#define CAPTEUR_DISTANCE_CAN_VAL_MAX 480
/**
 * Distance [cm] minimale valide
 */
#define CAPTEUR_DISTANCE_MIN 10
/**
 * Distance [cm] maximale valide
 * (selon le max de l'enonce du projet)
 */
#define CAPTEUR_DISTANCE_MAX 45
/**
 * Distance [cm] minimale a afficher si invalide
 */
#define CAPTEUR_DISTANCE_FORMAT_MIN 0
/**
 * Distance [cm] maximale a afficher si invalide
 */
#define CAPTEUR_DISTANCE_FORMAT_MAX 80
/**
 * Distance [cm] pour une lecture invalide (tres basse)
 */
#define CAPTEUR_DISTANCE_CAN_VAL_INVALIDE_MIN 80
/**
 * Distance [cm] pour une lecture invalide (tres haute)
 */
#define CAPTEUR_DISTANCE_CAN_VAL_INVALIDE_MAX 0
/**
 * Longueur de la memoire des lectures de valeurs CAN
 */
#define LONGUEUR_MEMOIRE_LECTURES 50

/**
 * \class CapteursDistance
 * \brief classe qui pilote les capteurs de distance
 */
class CapteursDistance
{
public:
    /**
     * Initialisation du capteur de distance
     */
    static void init();

    /**
     * Accesseur pour la distance la plus recente (gauche)
     * 
     * \param[out] dist : le pointeur dans lequel placer la distance [cm]
     * 
     * \return la validite de la mesure
     */
    static bool getDistanceGauche(uint8_t* dist);

    /**
     * Accesseur pour la distance la plus recente (droit)
     * 
     * \param[out] dist : le pointeur dans lequel placer la distance [cm]
     * 
     * \return la validite de la mesure
     */
    static bool getDistanceDroit(uint8_t* dist);

    /**
     * Utilitaire pour restreindre la valeur de la distance
     * pour pouvoir l'afficher meme si elle n'est pas valide
     * 
     * \param[out] dist : le pointeur qui contient la distance
     */
    static void formatDistance(uint8_t* dist);

private:
    static uint16_t memCanGauche[LONGUEUR_MEMOIRE_LECTURES];    ///< le buffer des dernieres lectures CAN pour moteur gauche
    static uint16_t memCanDroit[LONGUEUR_MEMOIRE_LECTURES];     ///< le buffer des dernieres lectures CAN pour moteur droit
    static uint16_t totalCanGauche;                             ///< le total courant des lectures CAN pour moteur gauche
    static uint16_t totalCanDroit;                              ///< le total courant des lectures CAN pour moteur droit
    static uint8_t indexCanGauche;                              ///< l'index courant du tableau de memoire pour moteur gauche
    static uint8_t indexCanDroit;                               ///< l'index courant du tableau de memoire pour moteur droit
    static can can_;                                            ///< l'objet pour le CAN

    /**
     * Validation de la distance selon la plage de distance du capteur
     * 
     * \param dist : la distance a valider
     * 
     * \return le resultat (true : valide; false : invalide)
     */
    static bool isDistanceValide(uint8_t* dist);

    /**
     * Conversion de la valeur de lecture du CAN vers la distance
     * 
     * \param canVal : la valeur CAN [0, 2^10 - 1]
     * \param[out] dist : la distance
     * 
     * \return la validite de la valeur
     */
    static bool canToDistance(uint16_t canVal, uint8_t* dist);

    /**
     * Ajout d'une nouvelle lecture CAN dans la memoire
     * 
     * \param lectCan : la nouvelle lecture CAN
     * \param memCan : le tableau de memoire a utiliser
     * \param indexMem : l'index du tableau de memoire a utiliser
     * \param totCan : la moyenne de lectures CAN a utiliser
     * 
     * \return la nouvelle valeur filtree
     */
    static uint16_t ajoutNouvelleLecture(uint16_t lectCan, uint16_t* memCan, uint8_t& indexMem, uint16_t& totCan);

};

#endif // LIB_CAPTEURS_DISTANCE_H

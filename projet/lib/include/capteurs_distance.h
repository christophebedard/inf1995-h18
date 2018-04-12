#ifndef LIB_CAPTEURS_DISTANCE_H
#define LIB_CAPTEURS_DISTANCE_H

/**
 * \file capteurs_distance.h
 * \brief declaration de la classe CapteursDistance
 * \author 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "broches.h"
#include "can.h"
#include "debug.h"


/**
 * Distance [cm] minimale pour une lecture valide
 */
#define CAPTEUR_DISTANCE_MIN 10
/**
 * Distance [cm] maximale pour une lecture valide
 * (selon le max de l'enonce du projet)
 */
#define CAPTEUR_DISTANCE_MAX 60
/**
 * Distance [cm] maximale pour une lecture valide
 */
#define CAPTEUR_DISTANCE_INVALIDE 0
/**
 * Longueur de la memoire des lectures de valeurs CAN
 */
#define LONGUEUR_MEMOIRE_LECTURES 5

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
     * Validation de la distance
     * 
     * \param dist : la distance a valider
     * 
     * \return le resultat (true : valide; false : invalide)
     */
    static bool isDistanceValide(uint8_t* dist);

    /**
     * Conversion de la valeur de lecture du CAN vers la distance
     * 
     * \param canVal : la valeur lue par le CAN [0, 2^10 - 1]
     * 
     * \return la distance [cm]
     */
    static uint8_t canToDistance(const uint16_t canVal);

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

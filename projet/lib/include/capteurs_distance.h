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
 */
#define CAPTEUR_DISTANCE_MAX 80
/**
 * Distance [cm] maximale pour une lecture valide
 */
#define CAPTEUR_DISTANCE_INVALIDE 0
/**
 * Longueur de la memoire des lectures de valeurs CAN
 */
#define LONGUEUR_MEMOIRE_LECTURES 10

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
     * \return la distance [cm]
     */
    static uint8_t getDistanceGauche();

    /**
     * Accesseur pour la distance la plus recente (droit)
     * 
     * \return la distance [cm]
     */
    static uint8_t getDistanceDroit();

private:
    static uint16_t memDistGauche[LONGUEUR_MEMOIRE_LECTURES];   ///< le buffer des dernieres lectures CAN pour moteur gauche
    static uint16_t memDistDroit[LONGUEUR_MEMOIRE_LECTURES];    ///< le buffer des dernieres lectures CAN pour moteur droit
    static can can_;                                            ///< l'objet pour le CAN

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
     * \param canLect : la nouvelle lecture CAN
     * \param memDist : le tableau de memoire a utiliser
     */
    static void ajoutNouvelleLecture(uint16_t canLect, uint16_t* memDist);

    /**
     * Calcul de la moyenne des lectures CAN en memoire
     * 
     * \param memDist : le tableau de memoire a utiliser
     */
    static uint16_t getMoyenneLectures(uint16_t* memDist);

};

#endif // LIB_CAPTEURS_DISTANCE_H

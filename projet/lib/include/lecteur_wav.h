#ifndef LIB_LECTEUR_WAV_H
#define LIB_LECTEUR_WAV_H

/**
 * \file lecteur_wav.h
 * \brief declaration de la classe LecteurWav
 * \author 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "timer0.h"
#include "timer1.h"

#define UPDATE_COUNT_STEP 2

/**
 * \class LecteurWav
 * \brief classe qui permet de jouer des donnees de fichier WAV
 */
class LecteurWav
{
public:
    /**
     * Initialisation
     */
    static void init();

    /**
     * Reglage des donnees de lecture
     * 
     * \param donnees : le pointeur vers le tableau de donnees
     * \param longueur : la longueur du tableau de donnees
     */
    static void setWav(const uint8_t* donnees, uint16_t longueur);

    /**
     * Lecture des donnees
     * 
     * \param loop : le choix pour la lecture en boucle
     */
    static void play(bool loop);

    /**
     * Arret de lecture et reinitialisation des compteurs
     */
    static void stop();

    /**
     * Etat de lecture
     * 
     * \return lecture en cours/lecture en pause (true) ou non (false)
     */
    static bool isPlaying();

    static volatile uint16_t position_;     ///< la position actuelle de la lecture
    static volatile uint8_t updateCount_;   ///< le compteur pour l'update de la valeur
    static bool loop_;                      ///< l'option de lecture en boucle
    static bool isPlaying_;        ///< l'etat de lecture
    static const uint8_t* donnees_;               ///< le pointeur vers le tableau de donnees
    static uint16_t longueurDonnees_;       ///< le nombre de donnees

private:

};

#endif // LIB_LECTEUR_WAV_H

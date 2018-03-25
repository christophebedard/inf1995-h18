#ifndef LIB_CHANSON_H
#define LIB_CHANSON_H

/**
 * \file chanson.h
 * \brief declaration de la classe Chanson
 * \author 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"
#include "buzzer.h"
#include "debug.h"

/**
 * Definition d'une note de chanson
 */
struct NoteChanson
{
    uint8_t duree; /**< la duree de la note (en millisecondes) */
    uint8_t noteMidi; /**< la note MIDI */
};

/**
 * \class Chanson
 * \brief classe qui enveloppe (wrap) le Buzzer pour lui faire jouer des chansons
 */
class Chanson
{
public:
    /**
     * Initialisation
     */
    static void init();

    /**
     * Lecture de la chanson
     */
    static void play();

    /**
     * Arret de lecture de la chanson
     */
    static void pause();

    /**
     * Arret de lecture de la chanson et reinitialisation du compteur
     */
    static void stop();

    static uint16_t compteurNotesChanson; /**< le compteur qui garde en memoire la note courante */
    static const uint16_t NOMBRE_NOTES_CHANSON; /**< le nombre total de notes pour la chanson */
    static const NoteChanson NOTES_CHANSON[]; /**< les informations pour les notes de la chanson */

private:

};

#endif // LIB_CHANSON_H

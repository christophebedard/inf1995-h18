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
#include "enums.h"
#include "buzzer.h"
#include "debug.h"


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

    /**
     * Lecture d'une note
     * donne la note MIDI au buzzer et regle le timer pour la duree
     * \todo rendre private (apres avoir change le callback pour etre une methode)
     * \param note : la NoteChanson a jouer
     */
    static void playNote(NoteChanson note);

private:

};

#endif // LIB_CHANSON_H

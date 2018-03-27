#ifndef LIB_LECTEURCHANSON_H
#define LIB_LECTEURCHANSON_H

/**
 * \file lecteur_chanson.h
 * \brief declaration de la classe LecteurChanson
 * \author 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"
#include "enums_structs.h"
#include "chansons.h"
#include "timer0.h"
#include "buzzer.h"
#include "debug.h"

/**
 * Unite de temps standard pour une note (en millisecondes)
 */
#define UNITE_TEMPS_MS 100

/**
 * \class LecteurChanson
 * \brief classe qui enveloppe (wrap) le Buzzer pour lui faire jouer des chansons
 */
class LecteurChanson
{
public:
    /**
     * Initialisation
     */
    static void init();

    /**
     * Reglage de la chanson
     * 
     * \param chanson : la chanson
     */
    static void setChanson(const ChansonMusique& chanson);

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

    /**
     * Etat de lecture de la chanson
     * 
     * \return lecture en cours/lecture en pause (true) ou non (false)
     */
    static bool isPlaying();

    static uint16_t compteurNotesChanson;   ///< le comcompteurMsNotepteur qui garde en memoire la note courante */
    static uint16_t compteurMsNote;         ///< le nombre de millisecondes restants a jouer pour la note courante */
    static ChansonMusique chansonCourante_; ///< la chanson courante
    static const uint16_t PERIODE_MAX;      ///< la longueur maximale de la periode selon le prescaler choisi */

    /**
     * Lecture d'une note
     * donne la note MIDI au buzzer et regle le timer pour la duree
     * 
     * \todo rendre private (apres avoir change le callback pour etre une methode)
     * 
     * \param noteMidi : la NoteChanson a jouer
     * \param duree : la duree en millisecondes
     */
    static void playNote(uint8_t noteMidi, uint8_t duree);

    /**
     * Calcule la duree en millisecondes d'une note
     * 
     * \todo rendre private (apres avoir change le callback pour etre une methode)
     * 
     * \param note : la figure de note
     * \param tempo : le tempo
     * 
     * \return la duree en millisecondes
     */
    static uint16_t getDureeMsNoteSelonFigureDeNoteEtTempo(const FigureDeNote& note, const Tempo& tempo);

private:
    /**
     * Calcule la valeur du registre OCRn selon le nombre de millisecondes
     * 
     * \param ms : le nombre de millisecondes
     * 
     * \return la valeur du registre OCRn
     */
    static uint8_t getValOCRnFromMs(const uint8_t& ms);

    static bool isPlaying_; ///< l'etat de lecture

};

#endif // LIB_LECTEURCHANSON_H

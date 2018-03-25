#ifndef LIB_ENUMS_H
#define LIB_ENUMS_H

/**
 * \file enums.h
 * \brief declaration de divers enums
 * \author 
 */

/**
 * Valeurs possibles pour le prescaler
 * Attention : certains timers ne supportent pas tous les prescalers
 */
enum class Prescaler
{
    PRE_1,      /**< une division par 1 */
    PRE_8,      /**< une division par 8 */
    PRE_32,     /**< une division par 32 */
    PRE_64,     /**< une division par 64 */
    PRE_128,    /**< une division par 128 */
    PRE_256,    /**< une division par 256 */
    PRE_1024    /**< une division par 1024 */
};

/**
 * Definition d'une note MIDI
 */
struct NoteMidi
{
    Prescaler pre; /**< la valeur du prescaler pour la note */
    uint8_t val_ocrn; /**< la valeur de OCRn pour la note */
};

/**
 * Definition d'une note de chanson (note MIDI et duree)
 */
struct NoteChanson
{
    uint8_t noteMidi;   /**< la note MIDI */
    uint16_t duree; /**< la duree de la note (selon une figure de note) */
    //NoteMusicale duree; /**< la duree de la note (selon une figure de note) */
};

/**
 * Definition d'une note musicale (duree)
 * voir : https://fr.wikipedia.org/wiki/Repr%C3%A9sentation_des_dur%C3%A9es_en_musique#Figures_de_note
 * on assume qu'une noire vaut 1 unite de temps
 */
enum class NoteMusicale
{
    Carree,             /**< une duree de (8) = le double de la ronde */
    Ronde,              /**< une duree de (4) = le double de la blanche */
    Blanche,            /**< une duree de (2) = le double de la noire */
    Noire,              /**< une duree de (1) = l'unite de temps */
    Croche,             /**< une duree de (1/2) = la moitie de la noire */
    DoubleCroche,       /**< une duree de (1/4) = la moitie de la croche */
    TripleCroche,       /**< une duree de (1/8) = la moitie de la double croche */
    QuadrupleCroche     /**< une duree de (1/16) = la moitie de la triple croche */
};

#endif // LIB_ENUMS_H

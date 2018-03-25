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
    Pres_1 = 1,          /**< une division par 1 */
    Pres_8 = 8,          /**< une division par 8 */
    Pres_32 = 32,        /**< une division par 32 */
    Pres_64 = 64,        /**< une division par 64 */
    Pres_128 = 128,      /**< une division par 128 */
    Pres_256 = 256,      /**< une division par 256 */
    Pres_1024 = 1024     /**< une division par 1024 */
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
    Carree = 8,             /**< une duree de (8) = le double de la ronde */
    Ronde = 4,              /**< une duree de (4) = le double de la blanche */
    Blanche = 2,            /**< une duree de (2) = le double de la noire */
    Noire = 0,              /**< une duree de (1) = l'unite de temps */
    Croche = 3,             /**< une duree de (1/2) = la moitie de la noire */
    DoubleCroche = 5,       /**< une duree de (1/4) = la moitie de la croche */
    TripleCroche = 9,       /**< une duree de (1/8) = la moitie de la double croche */
    QuadrupleCroche = 17    /**< une duree de (1/16) = la moitie de la triple croche */
};

#endif // LIB_ENUMS_H

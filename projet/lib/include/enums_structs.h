#ifndef LIB_ENUMS_STRUCTS_H
#define LIB_ENUMS_STRUCTS_H

/**
 * \file enums_structs.h
 * \brief declaration de divers enums et structs
 * \author 
 */

/**
 * Represente la direction des moteurs individuellement
 */
enum class DirectionMoteur
{
    Moteur_avant,   ///< vers l'avant
    Moteur_arriere  ///< vers l'arriere
};

/**
 * Represente COMNAx et COMNBx (voir doc pour precisions selon mode)
 */
enum class COM
{
    COM_normal, ///< normal port operation, OCnA/OCnB disconnected
    COM_toggle, ///< toggle OCnA/OCnB on compare match
    COM_clear,  ///< clear OCnA/OCnB on compare match
    COM_set     ///< set OCnA/OCnB on compare match
};

/**
 * Represente le waveform generation mode (voir doc pour precisions)
 */
enum class WGM
{
    WGM_0,      ///< normal (tim0 & tim1 & tim2)
    WGM_1,      ///< PWM, phase correct 8-bit (tim0 & tim1 & tim2)
    WGM_2,      ///< CTC (tim0 & tim2) / PWM, phase correct 9-bit (tim1)
    WGM_3,      ///< fast PWM (tim0 & tim2) / PWM, phase correct 10-bit (tim1)
    WGM_4,      ///< reserved (tim0 & tim2) / CTC (tim1)
    WGM_5,      ///< PWM, phase correct OCRA (tim0 & tim2) / fast PWM 8-bit (tim1)
    WGM_6,      ///< reserved (tim0 & tim2) / fast PWM 9-bit (tim1)
    WGM_7,      ///< fast PWM OCRA (tim0 & tim2) / fast PWM 10-bit (tim1)
    WGM_8,      ///< PWM, phase and frequency correct ICRn (tim1)
    WGM_9,      ///< PWM, phase and frequency correct OCRnA (tim1)
    WGM_10,     ///< PWM, phase correct ICRn (tim1)
    WGM_11,     ///< PWM, phase correct OCRnA (tim1)
    WGM_12,     ///< CTC ICRn (tim1)
    WGM_13,     ///< reserved
    WGM_14,     ///< fast PWM ICRn (tim1)
    WGM_15,     ///< fast PWM OCRnA (tim1)
};

/**
 * Valeurs possibles pour le prescaler
 * Attention : certains timers ne supportent pas tous les prescalers
 */
enum class Prescaler
{
    Pres_no_clk = 0,    ///< no clock source
    Pres_1 = 1,         ///< une division par 1
    Pres_8 = 8,         ///< une division par 8
    Pres_32 = 32,       ///< une division par 32
    Pres_64 = 64,       ///< une division par 64
    Pres_128 = 128,     ///< une division par 128
    Pres_256 = 256,     ///< une division par 256
    Pres_1024 = 1024,   ///< une division par 1024
    Pres_ext_falling,   ///< external clock source, falling edge
    Pres_ext_rising,    ///< external clock source, rising edge
};

/**
 * Definition d'une note MIDI
 */
struct NoteMidi
{
    Prescaler pre;      ///< la valeur du prescaler pour la note
    uint8_t val_ocrn;   ///< la valeur de OCRn pour la note
};

/**
 * Definition d'une note musicale (duree)
 * voir : https://fr.wikipedia.org/wiki/Repr%C3%A9sentation_des_dur%C3%A9es_en_musique#Figures_de_note
 * on assume qu'une noire vaut 1 unite de temps
 */
enum class NoteMusicale
{
    Carree = 8,             ///< une duree de (8) = le double de la ronde
    Ronde = 4,              ///< une duree de (4) = le double de la blanche
    Blanche = 2,            ///< une duree de (2) = le double de la noire
    Noire = 0,              ///< une duree de (1) = l'unite de temps
    Croche = 3,             ///< une duree de (1/2) = la moitie de la noire
    DoubleCroche = 5,       ///< une duree de (1/4) = la moitie de la croche
    TripleCroche = 9,       ///< une duree de (1/8) = la moitie de la double croche
    QuadrupleCroche = 17    ///< une duree de (1/16) = la moitie de la triple croche
};

/**
 * Definition d'une note de chanson (note MIDI et duree)
 */
struct NoteChanson
{
    uint8_t noteMidi;       ///< la note MIDI
    uint16_t duree;         ///< la duree de la note (selon une figure de note)
    //NoteMusicale duree;     ///< la duree de la note (selon une figure de note)
};

/**
 * Valeurs possibles pour le tempo (nombre de pulsations par minute)
 * https://fr.wikipedia.org/wiki/Tempo#Termes_conventionnels_italiens_et_allemands_des_principaux_tempos
 */
enum class Tempo
{
    Tempo_Largo = 50,       ///< un tempo large
    Tempo_Lento = 60,       ///< un tempo lent
    Tempo_Adagio = 70,      ///< un tempo a l'aise
    Tempo_Andante = 88,     ///< un tempo allant
    Tempo_Moderato = 100,   ///< un tempo modere
    Tempo_Allegreto = 114,  ///< un tempo assez allegre
    Tempo_Allegro = 136,    ///< un tempo allegre
    Tempo_Vivace = 140,     ///< un tempo vif
    Tempo_Presto = 170,     ///< un tempo rapide
    Tempo_Prestissimo = 188 ///< un tempo tres rapide
};

/**
 * Definition d'une chanson
 */
struct ChansonMusique
{
    uint8_t nbNotes;    ///< le nombre de notes
    NoteChanson notes;  ///< les notes
    Tempo tempo;        ///< le tempo
};

#endif // LIB_ENUMS_STRUCTS_H

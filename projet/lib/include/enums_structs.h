#ifndef LIB_ENUMS_STRUCTS_H
#define LIB_ENUMS_STRUCTS_H

/**
 * \file enums_structs.h
 * \brief declaration de divers enums et structs
 * \author 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"

/**
 * Declaration des types de trigger d'interruption
 */
enum class TypesTriggerInterrupt
{
    RisingEdge,         ///< un front montant
    FallingEdge,        ///< un front descendant
    RisingOrFallingEdge ///< un front montant ou descendant
};

/**
 * Declaration des etats pour le bouton
 */
enum class EtatBouton
{
    Enfonce = 0,        ///< l'etat enfonce/appuye/ON
    Relache = 1         ///< l'etat relache/non appuye/OFF
};

/**
 * Represente les messages robot-->logiciel pour le diagnostic
 */
enum class MessagesRobotLogiciel
{
    NomRobot = 0xf0,                ///< Nom du robot (maximum 13 octets)
    NumeroEquipe = 0xf1,            ///< Numero d’equipe (maximum 9 octets)
    NumeroSection = 0xf2,           ///< Numero de section (1 octet)
    Session = 0xf3,                 ///< Session (4 octets)
    CouleurBaseRobot = 0xf4,        ///< Couleur de la base du robot (1 octet)
    EtatBoutonInterrupt = 0xf5,     ///< Etat du bouton Interrupt (1 octet : 0x00 pour enfonce, 0x01 pour relache)
    DistanceCapteurGauche = 0xf6,   ///< Distance en cm detectee par le capteur gauche (1 octet)
    DistanceCapteurDroit = 0xf7     ///< Distance en cm detectee par le capteur droit (1 octet)
};

/**
 * Represente les messages logiciel-->robot pour le diagnostic
 */
enum class MessagesLogicielRobot
{
    VitesseRoueGauche = 0xf8, ///< Vitesse de la roue gauche
    VitesseRoueDroite = 0xf9, ///< Vitesse de la roue droite
    CouleurDel = 0xfa,        ///< Couleur de la Del libre
    RequeteEnvoiInfos = 0xfb  ///< Requete d’envoi des informations d’identification
};

/**
 * Represente la direction des moteurs individuellement
 */
enum class DirectionMoteur
{
    Avant = 1,   ///< vers l'avant
    Arriere = 0  ///< vers l'arriere
};

/**
 * Represente COMNAx et COMNBx (voir doc pour precisions selon mode)
 */
enum class COM
{
    Normal, ///< normal port operation, OCnA/OCnB disconnected
    Toggle, ///< toggle OCnA/OCnB on compare match
    Clear,  ///< clear OCnA/OCnB on compare match
    Set     ///< set OCnA/OCnB on compare match
};

/**
 * Represente le waveform generation mode (voir doc pour precisions)
 */
enum class WGM
{
    Mode_0,      ///< normal (tim0 & tim1 & tim2)
    Mode_1,      ///< PWM, phase correct 8-bit (tim0 & tim1 & tim2)
    Mode_2,      ///< CTC (tim0 & tim2) / PWM, phase correct 9-bit (tim1)
    Mode_3,      ///< fast PWM (tim0 & tim2) / PWM, phase correct 10-bit (tim1)
    Mode_4,      ///< reserved (tim0 & tim2) / CTC (tim1)
    Mode_5,      ///< PWM, phase correct OCRA (tim0 & tim2) / fast PWM 8-bit (tim1)
    Mode_6,      ///< reserved (tim0 & tim2) / fast PWM 9-bit (tim1)
    Mode_7,      ///< fast PWM OCRA (tim0 & tim2) / fast PWM 10-bit (tim1)
    Mode_8,      ///< PWM, phase and frequency correct ICRn (tim1)
    Mode_9,      ///< PWM, phase and frequency correct OCRnA (tim1)
    Mode_10,     ///< PWM, phase correct ICRn (tim1)
    Mode_11,     ///< PWM, phase correct OCRnA (tim1)
    Mode_12,     ///< CTC ICRn (tim1)
    Mode_13,     ///< reserved
    Mode_14,     ///< fast PWM ICRn (tim1)
    Mode_15,     ///< fast PWM OCRnA (tim1)
};

/**
 * Valeurs possibles pour le prescaler
 * Attention : certains timers ne supportent pas tous les prescalers
 */
enum class Prescaler
{
    No_clk = 0,         ///< no clock source
    Div_1 = 1,          ///< une division par 1
    Div_8 = 8,          ///< une division par 8
    Div_32 = 32,        ///< une division par 32
    Div_64 = 64,        ///< une division par 64
    Div_128 = 128,      ///< une division par 128
    Div_256 = 256,      ///< une division par 256
    Div_1024 = 1024,    ///< une division par 1024
    Ext_falling = 1025, ///< external clock source, falling edge
    Ext_rising = 1026   ///< external clock source, rising edge
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
 * Definition d'une figure de note (== duree)
 * voir : https://fr.wikipedia.org/wiki/Repr%C3%A9sentation_des_dur%C3%A9es_en_musique#Figures_de_note
 * on assume qu'une noire vaut 1 unite de temps
 */
enum class FigureDeNote
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
    FigureDeNote duree;     ///< la duree de la note (selon une figure de note)
};

/**
 * Valeurs possibles pour le tempo (nombre de pulsations par minute)
 * https://fr.wikipedia.org/wiki/Tempo#Termes_conventionnels_italiens_et_allemands_des_principaux_tempos
 */
enum class Tempo
{
    Largo = 50,       ///< un tempo large
    Lento = 60,       ///< un tempo lent
    Adagio = 70,      ///< un tempo a l'aise
    Andante = 88,     ///< un tempo allant
    Moderato = 100,   ///< un tempo modere
    Allegreto = 114,  ///< un tempo assez allegre
    Allegro = 136,    ///< un tempo allegre
    Vivace = 140,     ///< un tempo vif
    Presto = 170,     ///< un tempo rapide
    Prestissimo = 188 ///< un tempo tres rapide
};

enum class CoteMur
{
    Droit,
    Gauche
};
/**
 * Definition d'une chanson
 */
struct ChansonMusique
{
    uint8_t nbNotes;        ///< le nombre de notes
    NoteChanson notes[100]; ///< les notes, avec initialisation a 100 notes
    Tempo tempo;            ///< le tempo
};

#endif // LIB_ENUMS_STRUCTS_H

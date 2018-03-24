#ifndef LIB_MINUTERIE_H
#define LIB_MINUTERIE_H

/**
 * \file minuterie.h
 * \brief declaration des fonctions pour la minuterie
 * \author 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"

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
 * Initialisation du timer 0
 *
 * \param funcA : le pointeur vers la fonction de callback pour A
 * \param funcB : le pointeur vers la fonction de callback pour B
 */
void initTimer0(func_t funcA, func_t funcB);

/**
 * Initialisation du timer 1
 *
 * \param func : le pointeur vers la fonction de callback
 */
void initTimer1(func_t func);

/**
 * Initialisation du timer 2
 *
 * \param funcA : le pointeur vers la fonction de callback pour A
 * \param funcB : le pointeur vers la fonction de callback pour B
 */
void initTimer2(func_t funcA, func_t funcB);

/**
 * Active le timer 0
 */
void startTimer0();

/**
 * Debut du timer 1
 * 
 * \param duree : la duree de la minuterie en millisecondes
 */
void startTimer1(const uint16_t duree);

/**
 * Active le timer 1
 */
void startTimer1();

/**
 * Active le timer 2
 */
void startTimer2();

/**
 * Reglage de la valeur de OCRnA du timer 0
 * 
 * \param val_ocrn : la valeur de OCRnA
 */
void setOCRnATimer0(const uint8_t& val_ocrn);

/**
 * Reglage de la valeur de OCRnB du timer 0
 * 
 * \param val_ocrn : la valeur de OCRnB
 */
void setOCRnBTimer0(const uint8_t& val_ocrn);

/**
 * Reglage de la valeur de OCRnA du timer 1
 * 
 * \param val_ocrn : la valeur de OCRnA
 */
void setOCRnATimer1(const uint16_t& val_ocrn);

/**
 * Reglage de la valeur de OCRnB du timer 1
 * 
 * \param val_ocrn : la valeur de OCRnB
 */
void setOCRnBTimer1(const uint16_t& val_ocrn);

/**
 * Reglage de la valeur de OCRnA du timer 2
 * 
 * \param val_ocrn : la valeur de OCRnA
 */
void setOCRnATimer2(const uint8_t& val_ocrn);

/**
 * Reglage de la valeur de OCRnB du timer 2
 * 
 * \param val_ocrn : la valeur de OCRnB
 */
void setOCRnBTimer2(const uint8_t& val_ocrn);

/**
 * Reglage du prescaler du timer 0
 * 
 * \param pre : la valeur de Prescaler
 */
void setPrescalerTimer0(const Prescaler& pre);

/**
 * Reglage du prescaler du timer 1
 * 
 * \param pre : la valeur de Prescaler
 */
void setPrescalerTimer1(const Prescaler& pre);

/**
 * Reglage du prescaler du timer 2
 * 
 * \param pre : la valeur de Prescaler
 */
void setPrescalerTimer2(const Prescaler& pre);

/**
 * Arret du timer 0
 */
void stopTimer0();

/**
 * Arret du timer 1
 */
void stopTimer1();

/**
 * Arret du timer 2
 */
void stopTimer2();

#endif // LIB_MINUTERIE_H

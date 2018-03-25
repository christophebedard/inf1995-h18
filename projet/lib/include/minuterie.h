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
#include "enums.h"
#include "debug.h"


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
 * Reglage de la valeur de OCRnA du timer 0 selon le temps
 * Utilisant un prescaler de 1024, la periode maximale est 32.64 ms
 * \param ms : le nombre de millisecondes
 */
void setOCRnATimer0FromMs(const uint8_t& ms);

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

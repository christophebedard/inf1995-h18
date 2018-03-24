#ifndef LIB_MINUTERIE_H
#define LIB_MINUTERIE_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"

/**
 * Valeurs possibles pour le prescaler
 */
enum class Prescaler
{
    PRE_1,
    PRE_8,
    PRE_32,
    PRE_64,
    PRE_128,
    PRE_256,
    PRE_1024
};

struct NoteMidi
{
    Prescaler pre;
    uint8_t val_ocrn;
};

/**
 * Initialisation du timer 1
 *
 * \param func : le pointeur vers la fonction de callback
 */
void initTimer1(func_t func);

/**
 * Initialisation du timer 2
 *
 * \param func : le pointeur vers la fonction de callback
 */
void initTimer2(func_t func);

/**
 * Debut du timer 1
 * 
 * \param duree : la duree de la minuterie en millisecondes
 */
void startTimer1(const uint16_t duree);

/**
 * Active le timer 2
 */
void startTimer2();

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
 * Reglage du prescaler du timer 2
 * 
 * \param pre : la valeur de Prescaler
 */
void setPrescalerTimer2(const Prescaler& pre);

/**
 * Arret du timer 1
 */
void stopTimer1();

/**
 * Arret du timer 2
 */
void stopTimer2();

#endif // LIB_MINUTERIE_H

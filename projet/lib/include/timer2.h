#ifndef LIB_TIMER2_H
#define LIB_TIMER2_H

/**
 * \file timer2.h
 * \brief declaration de la classe Timer2
 * \author 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"
#include "enums.h"
#include "debug.h"

/**
 * \class Timer2
 * \brief classe qui definit un Timer2
 * Utilise pour :
 *          * jouer les notes MIDI avec le buzzer
 */
class Timer2
{
public:
    /**
     * Part le timer2
     */
    static void start();

    /**
     * Stop le timer2
     */
    static void stop();

    /**
     * Reglage du compare output mode (TCCRnA : COMn)
     * 
     * \param a : le mode pour le channel A
     * \param b : le mode pour le channel B
     */
    static void setCompareOutputMode(COM a, COM b);

    /**
     * Reglage du waveform generation mode (TCCRnA et TCCRnB : WGMn)
     * 
     * \param mode : le mode de generation
     */
    static void setWaveformGenerationMode(WGM mode);

    /**
     * Reglage du prescaler (TCCRnB : CSn)
     * 
     * \param pre : la valeur du prescaler
     */
    static void setPrescaler(const Prescaler pre);

    /**
     * Reglage du interrupt enable (TIMSKn : OCIEnA/OCIEnB)
     * 
     * \param a : la valeur pour le channel A (false ou true)
     * \param b : la valeur pour le channel B  (false ou true)
     */
    static void setInterruptEnable(bool a, bool b);

    /**
     * Reglage du output compare register A (OCRnA)
     * 
     * \param val : la valeur pour OCRnA
     */
    static void setOCRnA(uint8_t val);

    /**
     * Reglage du output compare register B (OCRnB)
     * 
     * \param val : la valeur pour OCRnB
     */
    static void setOCRnB(uint8_t val);

    /**
     * Reglage de la fonction de callback pour COMPA
     * 
     * \param func : le pointeur vers la fonction de callback
     */
    static void setCompACallback(func_t func);

    /**
     * Reglage de la fonction de callback pour COMPB
     * 
     * \param func : le pointeur vers la fonction de callback
     */
    static void setCompBCallback(func_t func);

    /**
     * Reset de TCNTn a 0
     */
    static void resetTCNTn();

    static Prescaler timPres; ///< le prescaler utilise

};

#endif // LIB_TIMER2_H

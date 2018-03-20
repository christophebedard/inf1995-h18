#ifndef LIB_TIMER_H
#define LIB_TIMER_H

/**
 * \file timer.h
 * \brief declaration de la classe Timer
 * \author 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"
#include "debug.h"

/// enum pour representer COMNAx et COMNBx (voir doc pour precisions selon mode)
enum class COM
{
    COM_normal, /*!< normal port operation, OCnA/OCnB disconnected */
    COM_toggle, /*!< toggle OCnA/OCnB on compare match */
    COM_clear,  /*!< clear OCnA/OCnB on compare match */
    COM_set     /*!< set OCnA/OCnB on compare match */
};

/// enum pour representer le waveform generation mode (voir doc pour precisions)
enum class WGM
{
    WGM_0,      /*!< normal (tim0 & tim1 & tim2) */
    WGM_1,      /*!< PWM, phase correct 8-bit (tim0 & tim1 & tim2) */
    WGM_2,      /*!< CTC (tim0 & tim2) / PWM, phase correct 9-bit (tim1) */
    WGM_3,      /*!< fast PWM (tim0 & tim2) / PWM, phase correct 10-bit (tim1) */
    WGM_4,      /*!< reserved (tim0 & tim2) / CTC (tim1) */
    WGM_5,      /*!< PWM, phase correct OCRA (tim0 & tim2) / fast PWM 8-bit (tim1) */
    WGM_6,      /*!< reserved (tim0 & tim2) / fast PWM 9-bit (tim1) */
    WGM_7,      /*!< fast PWM OCRA (tim0 & tim2) / fast PWM 10-bit (tim1) */
    WGM_8,      /*!< PWM, phase and frequency correct ICRn (tim1) */
    WGM_9,      /*!< PWM, phase and frequency correct OCRnA (tim1) */
    WGM_10,     /*!< PWM, phase correct ICRn (tim1) */
    WGM_11,     /*!< PWM, phase correct OCRnA (tim1) */
    WGM_12,     /*!< CTC ICRn (tim1) */
    WGM_13,     /*!< reserved */
    WGM_14,     /*!< fast PWM ICRn (tim1) */
    WGM_15,     /*!< fast PWM OCRnA (tim1) */
};

/// enum pour representer le prescaler (voir doc pour precisions selon le mode)
enum class Prescaler
{
    Pre_no_clk,         /*!< no clock source */
    Pre_none,           /*!< no prescaling */
    Pre_8,              /*!< /8 */
    Pre_64,             /*!< /64 */
    Pre_256,            /*!< /256 */
    Pre_1024,           /*!< /1024 */
    Pre_ext_falling,    /*!< external clock source, falling edge */
    Pre_ext_rising,     /*!< external clock source, rising edge */
};

/**
 * \class Timer
 * \brief classe abstraite qui definit un timer
 * dans le but de l'utiliser pour une minuterie, PWM, etc.
 */
class Timer
{
public:
    /// \todo singleton?

    /**
     * Constructeur
     */
    Timer();

    /**
     * Destructeur
     */
    ~Timer();

    /**
     * Reglage du compare output mode (TCCRnA : COMn)
     * 
     * \param a : le mode pour le channel A
     * \param b : le mode pour le channel B
     */
    virtual void setCompareOutputMode(COM a, COM b) =0;

    /**
     * Reglage du waveform generation mode (TCCRnA et TCCRnB : WGMn)
     * 
     * \param mode : le mode de generation
     */
    virtual void setWaveformGenerationMode(WGM mode) =0;

    /**
     * Reglage du prescaler (TCCRnB : CSn)
     * 
     * \param pre : la valeur du prescaler
     */
    virtual void setPrescaler(Prescaler pre) =0;

    /**
     * Reglage du interrupt enable (TIMSKn : OCIEnA/OCIEnB)
     * 
     * \param a : la valeur pour le channel A (0 ou 1)
     * \param b : la valeur pour le channel B (0 ou 1)
     */
    virtual void setInterruptEnable(uint8_t a, uint8_t b) =0;

    /**
     * Reglage du output compare register A (OCRnA)
     * 
     * \param val : la valeur pour OCRnA
     */
    virtual void setOCRnA(uint16_t val) =0;

    /**
     * Reglage du output compare register B (OCRnB)
     * 
     * \param val : la valeur pour OCRnB
     */
    virtual void setOCRnB(uint16_t val) =0;

    /**
     * Reglage de la fonction de callback pour COMPA
     * 
     * \param func : le pointeur vers la fonction de callback
     */
    virtual void setCompACallback(func_t func) =0;

    /**
     * Reglage de la fonction de callback pour COMPB
     * 
     * \param func : le pointeur vers la fonction de callback
     */
    virtual void setCompBCallback(func_t func) =0;

    /**
     * Reset de TCNTn a 0
     */
    virtual void resetTCNTn() =0;

};

#endif // LIB_TIMER_H

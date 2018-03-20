#ifndef LIB_TIMER2_H
#define LIB_TIMER2_H

/**
 * \file timer2.h
 * \brief declaration de la classe Timer2
 * \author 
 */

#include "timer.h"

/**
 * \class Timer2
 * \brief classe qui definit un Timer2
 */
class Timer2 : public Timer
{
public:
    /// \todo singleton?

    /**
     * Constructeur
     */
    Timer2();

    /**
     * Destructeur
     */
    ~Timer2();

    /**
     * Reglage du compare output mode (TCCRnA : COMn)
     * 
     * \param a : le mode pour le channel A
     * \param b : le mode pour le channel B
     */
    virtual void setCompareOutputMode(COM a, COM b);

    /**
     * Reglage du waveform generation mode (TCCRnA et TCCRnB : WGMn)
     * 
     * \param mode : le mode de generation
     */
    virtual void setWaveformGenerationMode(WGM mode);

    /**
     * Reglage du prescaler (TCCRnB : CSn)
     * 
     * \param pre : la valeur du prescaler
     */
    virtual void setPrescaler(Prescaler pre);

    /**
     * Reglage du interrupt enable (TIMSKn : OCIEnA/OCIEnB)
     * 
     * \param a : la valeur pour le channel A (0 ou 1)
     * \param b : la valeur pour le channel B (0 ou 1)
     */
    virtual void setInterruptEnable(uint8_t a, uint8_t b);

    /**
     * Reglage du output compare register A (OCRnA)
     * 
     * \param val : la valeur pour OCRnA
     */
    virtual void setOCRnA(uint16_t val);

    /**
     * Reglage du output compare register B (OCRnB)
     * 
     * \param val : la valeur pour OCRnB
     */
    virtual void setOCRnB(uint16_t val);

    /**
     * Reglage de la fonction de callback pour COMPA
     * 
     * \param func : le pointeur vers la fonction de callback
     */
    virtual void setCompACallback(func_t func);

    /**
     * Reglage de la fonction de callback pour COMPB
     * 
     * \param func : le pointeur vers la fonction de callback
     */
    virtual void setCompBCallback(func_t func);

    /**
     * Reset de TCNTn a 0
     */
    virtual void resetTCNTn();
};

#endif // LIB_TIMER2_H

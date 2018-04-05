#ifndef LIB_DIAGNOSTIC_H
#define LIB_DIAGNOSTIC_H

/**
 * \file diagnostic.h
 * \brief declaration de la classe Diagnostic
 * \author 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"
#include "broches.h"
#include "enums_structs.h"
#include "uart.h"
#include "can.h"
#include "capteurs_distance.h"
#include "debug.h"
#include "interruption.h"
#include "moteurs.h"


/**
 * \class Diagnostic
 * \brief classe qui execute les fonctions du diagnostic
 */
class Diagnostic
{
public:

    /**
     * Execution du diagnostic
     */
    static void execute();

    /**
     * Fonction de callback pour la reception
     */
    friend void callbackRx();

private:
    static uint8_t bouton;
    static uint8_t instruction;
    
    //static const uint8_t d; ///< 

    /**
     * Initialisation
     */
    static void init();

    /**
     * Transmission d'un message
     * 
     * \param type : le type du message (selon les enums)
     * \param donnee : la donnee du message
     */
    static void transmissionMessage(uint8_t type, uint8_t donnee);

    /**
     * Transmission des informations du robot
     *
     * \param id : l'identificateur du robot
     *              (0 pour le robot 2; 1 pour le robot 1)
     */
    static void transmettreInfos(int id);


};

#endif // LIB_DIAGNOSTIC_H

#ifndef LIB_DIAGNOSTIC_H
#define LIB_DIAGNOSTIC_H

/**
 * \file diagnostic.h
 * \brief declaration de la classe Diagnostic
 * \author Simon Moreau
 * \author Mohamed Saddik
 * \author Fares Ouaissa
 * \author Christophe Bourque Bedard
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"
#include "broches.h"
#include "enums_structs.h"
#include "delai.h"
#include "uart.h"
#include "can.h"
#include "capteurs_distance.h"
#include "debug.h"
#include "bouton.h"
#include "moteurs.h"


/**
 * \class Diagnostic
 * \brief classe qui execute les fonctions du diagnostic
 */
class Diagnostic
{
public:
    /**
     * Initlialisation et execution du diagnostic en boucle inifinie
     * (pour execution en standalone)
     */
    static void execute();

    /**
     * Initialisation
     */
    static void init(bool modeDebug = false);

    /**
     * Update
     * (transmission des informations du robot)
     */
    static void update();

    /**
     * Ami : fonction de callback pour la reception
     */
    friend void callbackRx();

private:
    static bool modeDebug_; ///< le flag pour le mode debug (pas de controle des moteurs ou de la LED)
    
    /**
     * Transmission d'un message via enum
     * 
     * \param type : le type du message (selon l'enum MessagesRobotLogiciel)
     * \param donnee : la donnee du message
     */
    static void transmissionMessage(MessagesRobotLogiciel msg, uint8_t donnee);

    /**
     * Transmission d'un message string via enum
     * 
     * \param type : le type du message (selon l'enum MessagesRobotLogiciel)
     * \param donnee : le char* pour le string du message
     * \param longueur : la longueur du string
     */
    static void transmissionMessage(MessagesRobotLogiciel msg, const char* donnees, const uint8_t longueur);

    /**
     * Transmission d'un message
     * 
     * \param type : le type du message
     * \param donnee : la donnee du message
     */
    static void transmissionMessage(uint8_t type, uint8_t donnee);

    /**
     * Transmission des informations du robot
     */
    static void transmettreInfos();

};

#endif // LIB_DIAGNOSTIC_H

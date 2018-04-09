#ifndef LIB_DEFINES_H
#define LIB_DEFINES_H

/**
 * \file defines.h
 * \brief declaration de divers types et constantes globales
 * \author 
 */

#ifndef F_CPU
///< la frequence du CPU
#define F_CPU 8000000
#endif

#include <avr/io.h>
#include <avr/interrupt.h>


///< pointeur vers fonction sans argument et retour void
typedef void (*func_t)();

// definition des constantes
const uint8_t SORTIE = 0xff;
const uint8_t ENTREE = 0X00;
const uint8_t ETEINT = 0x00;
const uint8_t ROUGE = 0x02;
const uint8_t VERT = 0x01;

// informations sur l'equipe
const char INFO_NOM_ROBOT[] = "Thinky Winky";   ///< le nom du robot
const char INFO_EQUIPE[] = "68116";             ///< le numero de l'equipe
#define INFO_GROUPE 3                           ///< le numero du groupe
const char INFO_SESSION[] = "18-1";             ///< l'annee-session
#define COULEUR_ROBOT1 1                        ///< la couleur du premier robot (gris/noir)
#define COULEUR_ROBOT2 4                        ///< la couleur du deuxieme robot (vert)

///< le numero du robot actuel (1 ou 2)
#define NUMERO_ROBOT 1


#endif // LIB_DEFINES_H

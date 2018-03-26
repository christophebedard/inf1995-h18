#ifndef LIB_DEFINES_H
#define LIB_DEFINES_H

/**
 * \file defines.h
 * \brief declaration de divers types et constantes globales
 * \author 
 */

#ifndef F_CPU
#define F_CPU 8000000
#endif

// pointeur vers fonction sans argument et retour void
typedef void (*func_t)();

// Definition des constantes
const uint8_t SORTIE = 0xff;
const uint8_t ENTREE = 0X00;
const uint8_t ETEINT = 0x00;
const uint8_t ROUGE = 0x02;
const uint8_t VERT = 0x01;

// Informations sur l'equipe
const char INFO_NOM_ROBOT[] = "Thinky Winky";
const char INFO_EQUIPE[] = "68116";
const char INFO_GROUPE[] = "03";
const char INFO_SESSION[] = "18-1";


#endif // LIB_DEFINES_H

#ifndef LIB_TRAJET_H
#define LIB_TRAJET_H

/**
 * \file trajet.h
 * \brief declaration de la classe Trajet
 * \author 
 */

#include "pwm.h"
#include "uart.h"
#include "buzzer.h"
#include "delai.h"
#include "memoire_24.h"
#include "defines.h"
#include "capteurs_distance.h"
#include "moteurs.h"
#include "enums_structs.h"

/**
 * \class Trajet
 * \brief classe qui définit notre trajet 
 */
class Trajet
{
public:



void execute();
friend void poteauDetecte();
friend void demiTour();
private:
void changerCoteDroit(uint8_t PourcentageDroit,uint8_t PourcentageGauche);
void changerCoteGauche(uint8_t PourcentageDroit,uint8_t PourcentageGauche);
void init();
void contournerPanneauDroit(uint8_t pourcentage);
void contournerPanneauGauche(uint8_t pourcentage);
void ajusterDistance(uint8_t pourcentage);
bool getDroitChangementCote();
void setDroitChangementCote(bool droitChangementCote);
static CoteMur getCoteSuivi();
static void setCoteSuivi(CoteMur mur);
bool droitChangementCote_;
static CoteMur mur_;

};

#endif // LIB_TRAJET_H

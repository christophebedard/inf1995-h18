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


/**
 * \class Trajet
 * \brief classe qui définit notre trajet 
 */
class Trajet
{
public:

void changerCoteDroit();
void changerCoteGauche();
void jouerNote();
void contournerPanneauDroit();
void contournerPanneauGauche();
void ajusterDistance();
void demiTour();
bool getDroitChangementCote();
void setDroitChangementCote(bool droitChangementCote);


private:
    bool droitChangementCote;


};

#endif // LIB_TRAJET_H

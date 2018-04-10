/**
 * \file trajet.cpp
 * \brief implementation de la classe Diagnostic
 * \author 
 */

#include "trajet.h"
#include "interruption.h"
#include "bouton.h"
#include "moteurs.h"
#include "capteurs_distance.h"
#include "buzzer.h"
#include "enums_structs.h"
#include "timer0.h"

void Trajet::changerCoteGauche(uint8_t pourcentageDroit,uint8_t pourcentageGauche)
{   
    Moteurs::setPourcentageDroite(pourcentageDroit);
    Moteurs::setPourcentageGauche(0);
    waitForMs(100);
    while(!(CapteursDistance::getDistanceGauche() == 20)){
        Moteurs::setPourcentage(pourcentageDroit);
    }
    Moteurs::setPourcentageDroite(0);
    Moteurs::setPourcentageGauche(pourcentageGauche);
    waitForMs(100);
    Trajet::ajusterDistance(pourcentageGauche);
}

void Trajet::changerCoteDroit(uint8_t pourcentageDroit,uint8_t pourcentageGauche)
{
    Moteurs::setPourcentageDroite(0);
    Moteurs::setPourcentageGauche([ourcentageGauche);
    waitForMs(100);
    while(!(CapteursDistance::getDistanceDroit() == 20)){
        Moteurs::setPourcentage(pourcentageGauche);
    }
    Moteurs::setPourcentageDroite(pourcentageDroit);
    Moteurs::setPourcentageGauche(0);
    waitForMs(100);
    Trajet::ajusterDistance(pourcentageDroit);
}

void Trajet::poteauDetecte()
{   //5.1 cm
    Timer0::stop();
    for (uint8_t i = 0; i < 3; i++){
        Buzzer::play(115);
        waitForMs(200);
        Buzzer::stop();
        waitForMs(100);
    }
}

void Trajet::contournerPanneauDroit(uint8_t pourcentage)
{
    Moteurs::virageDroit(60);
    Moteurs::setPourcentage(pourcentage);
    Trajet::ajusterDistance(pourcentage);
}

void Trajet::contournerPanneauGauche(uint8_t pourcentage)
{
    Moteurs::virageGauche(60);
    Moteurs::setPourcentage(pourcentage);
    Trajet::ajusterDistance(pourcentage);
}

void Trajet::ajusterDistance(uint8_t pourcentage)
{
   switch (mur_){
   
       case CoteMur::Droit:
           while(!(CapteursDistance::getDistanceDroit() == 15)){
                if (CapteursDistance::getDistanceDroit() < 15)
                {
                    Moteurs::setPourcentageDroite(0);
                    Moteurs::setPourcentageGauche(pourcentage);
                }
                else if (CapteursDistance::getDistanceDroit() > 15)
                {
                    Moteurs::setPourcentageGauche(0);
                    Moteurs::setPourcentageDroite(pourcentage);
                }
                
            }
            Moteurs::setPourcentage(pourcentage);
       case CoteMur::Gauche:
            while(!(CapteursDistance::getDistanceGauche() == 15)){
                if (CapteursDistance::getDistanceGauche() < 15)
                {
                    Moteurs::setPourcentageGauche(0);
                    Moteurs::setPourcentageDroite(pourcentage);
                }
                else if (CapteursDistance::getDistanceGauche() > 15)
                {
                    Moteurs::setPourcentageDroite(0);
                    Moteurs::setPourcentageGauche(pourcentage);
                }
                
            }
            Moteurs::setPourcentage(pourcentage);
}
}

void Trajet::demiTour(uint8_t pourcentage)
{
    switch (mur_){
    
        case CoteMur::Droit:
            virageGauche(80);
            
        case CoteMur::Gauche:
            virageDroit(80);
    }
}

bool Trajet::getDroitChangementCote()
{
    return droitChangementCote_;
}

void Trajet::setDroitChangementCote(bool droitChangementCote)
{
    droitChangementCote_ = droitChangementCote
}

CoteMur getCoteSuivi()
{
    return mur_;
}

void setCoteSuivi(CoteMur mur)
{
    mur_ = mur;
}

void Trajet::init()
{
    Interruption::initInt1(demiTour, TypesTriggerInterrupt::RisingEdge);
    Moteurs::init();
    CapteursDistance::init();
    Buzzer::init();
    DDRA |= BROCHES_LED;
    Timer0::setCompACallback(Trajet::poteauDetecte);
    Timer0::setCompareOutputMode(COM::Clear, COM::Normal);
    Timer0::setWaveformGenerationMode(WGM::Mode_2);
    Timer0::setPrescaler(Prescaler::Div_256);
    Timer0::setInterruptEnable(true, false, false);
    //Attributs pour la situation initiale
    droitChangementCote_ = true;
    if(CapteursDistance::getDistanceDroit() == 15)
        mur_ = CoteMur::Droit;
    else if (CapteursDistance::getDistanceGauche() == 15)
        mur_ = CoteMur::Gauche;
    
    
}
void Trajet::execute()
{
    Trajet::init();
    
}

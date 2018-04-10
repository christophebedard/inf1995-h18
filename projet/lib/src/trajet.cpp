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

/**
 * Change de cote vers la gauche
 * @pourcentageDroit : la vitesse presente du moteur droit
 * @pourcentageGauche : la vitesse presente du moteur gauche
 */
void Trajet::changerCoteGauche(uint8_t pourcentageDroit,uint8_t pourcentageGauche)
{   
    Moteurs::setPourcentageDroite(pourcentageDroit);
    Moteurs::setPourcentageGauche(0);
    waitForMs(100);
    Moteurs::setPourcentage(pourcentageDroit);
    while(!(CapteursDistance::getDistanceGauche() == 20)){
    }
    Moteurs::setPourcentageDroite(0);
    Moteurs::setPourcentageGauche(pourcentageGauche);
    waitForMs(100);
    Trajet::ajusterDistance(pourcentageGauche);
    Trajet::setCoteSuivi(CoteMur::Gauche);
}

/**
 * Change de cote vers la droite
 * @pourcentageDroit : la vitesse presente du moteur droit
 * @pourcentageGauche : la vitesse presente du moteur gauche
 */
void Trajet::changerCoteDroit(uint8_t pourcentageDroit,uint8_t pourcentageGauche)
{
    Moteurs::setPourcentageDroite(0);
    Moteurs::setPourcentageGauche(pourcentageGauche);
    waitForMs(100);
    Moteurs::setPourcentage(pourcentageGauche);
    while(!(CapteursDistance::getDistanceDroit() == 20)){
        
    }
    Moteurs::setPourcentageDroite(pourcentageDroit);
    Moteurs::setPourcentageGauche(0);
    waitForMs(100);
    Trajet::ajusterDistance(pourcentageDroit);
    Trajet::setCoteSuivi(CoteMur::Droit);
}

/**
 * Termine la minuterie et joue une sequence de trois sons aigus
 */
void poteauDetecte()
{   //5.1 cm
    Timer0::stop();
    for (uint8_t i = 0; i < 3; i++){
        Buzzer::play(115);
        waitForMs(200);
        Buzzer::stop();
        waitForMs(100);
    }
}

/**
 * Contourne le panneau vers la droite
 * @pourcentage: vitesse du robot
 */
void Trajet::contournerPanneauDroit(uint8_t pourcentage)
{
    Moteurs::virageDroit(60);
    Moteurs::setPourcentage(pourcentage);
    Trajet::ajusterDistance(pourcentage);
}


/**
 * Contourne le panneau vers la gauche
 * @pourcentage: vitesse du robot
 */
void Trajet::contournerPanneauGauche(uint8_t pourcentage)
{
    Moteurs::virageGauche(60);
    Moteurs::setPourcentage(pourcentage);
    Trajet::ajusterDistance(pourcentage);
}

/**
 * Ajuste la distance au mur pour etre a 15 cm
 * @pourcentage: vitesse du robot
 */
void Trajet::ajusterDistance(uint8_t pourcentage)
{
   switch (Trajet::getCoteSuivi()){
   
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

/**
 * Robot fait un demi demiTour
 * @pourcentage: vitesse du robot
 */
void demiTour()
{
    switch (Trajet::getCoteSuivi()){
    
        case CoteMur::Droit:
            Moteurs::virageGauche(80);
            
        case CoteMur::Gauche:
            Moteurs::virageDroit(80);
    }
}


bool Trajet::getDroitChangementCote()
{
    return droitChangementCote_;
}

void Trajet::setDroitChangementCote(bool droitChangementCote)
{
    droitChangementCote_ = droitChangementCote;
}

CoteMur Trajet::getCoteSuivi()
{
    return mur_;
}

void Trajet::setCoteSuivi(CoteMur mur)
{
    mur_ = mur;
}

/**
 * initialisation pour le trajet
 */
void Trajet::init()
{
    Interruption::initInt1(demiTour, TypesTriggerInterrupt::RisingEdge);
    Moteurs::init();
    CapteursDistance::init();
    Buzzer::init();
    DDRA |= BROCHES_LED;
    Timer0::setCompACallback(poteauDetecte);
    Timer0::setCompareOutputMode(COM::Clear, COM::Normal);
    Timer0::setWaveformGenerationMode(WGM::Mode_2);
    Timer0::setPrescaler(Prescaler::Div_256);
    Timer0::setInterruptEnable(true, false, false);
    //Attributs pour la situation initiale
    droitChangementCote_ = true;
    if(CapteursDistance::getDistanceDroit() == 15)
        Trajet::setCoteSuivi(CoteMur::Droit);
    else if (CapteursDistance::getDistanceGauche() == 15)
        Trajet::setCoteSuivi(CoteMur::Gauche);
    
    
}

/**
 * Execute le trajet
 */
void Trajet::execute()
{
    Trajet::init();
    for(;;){
        uint8_t droit = CapteursDistance::getDistanceDroit();
        uint8_t gauche = CapteursDistance::getDistanceGauche();
        uint8_t pourcentage = 50;
        switch (Trajet::getCoteSuivi()){
        
            case CoteMur::Droit:
                Moteurs::setPourcentage(pourcentage);
                if(droit == 15)
                {
                    
                    if ((gauche > 10) && (gauche <= 60))
                    {
                        //Timer0::setOCRnA();//calculer valeurs
                        if (Trajet::getDroitChangementCote()){
                            changerCoteGauche(pourcentage, pourcentage);
                            Trajet::setDroitChangementCote(false);
                        }
                        
                    }   
                    //Timer0::stop();
                    
                }
                else if (droit < 15)
                    Trajet::ajusterDistance(pourcentage);
                else if ((droit > 15) && (droit <= 60))
                    Trajet::ajusterDistance(pourcentage);
                else if (droit > 60)
                    Trajet::contournerPanneauDroit(pourcentage);
                if (gauche > 60)
                    Trajet::setDroitChangementCote(true);
                    
            case CoteMur::Gauche:
                Moteurs::setPourcentage(60);
                if (gauche == 15)
                {
                    if ((droit > 10) && (droit <= 60))
                    {
                        //Timer0::setOCRnA();//calculer valeurs revoir gestion detection poteau
                        if (Trajet::getDroitChangementCote()){
                            changerCoteDroit(pourcentage, pourcentage);
                            Trajet::setDroitChangementCote(false);
                        }
                        
                    }
                    //Timer0::stop();
                }
                else if (gauche < 15)
                    Trajet::ajusterDistance(pourcentage);
                else if ((gauche > 15) && (gauche <= 60))
                    Trajet::ajusterDistance(pourcentage);
                else if (gauche > 60)
                    Trajet::contournerPanneauGauche(pourcentage);
                if (droit > 60)
                    Trajet::setDroitChangementCote(true);
        }
    }
}

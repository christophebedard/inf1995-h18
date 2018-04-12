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
/*void Trajet::changerCoteGauche(uint8_t pourcentageDroit, uint8_t pourcentageGauche)
{   
    Moteurs::setPourcentageDroite(pourcentageDroit);
    Moteurs::setPourcentageGauche(0);
    waitForMs(100);
    Moteurs::setPourcentage(pourcentageDroit);
    while(!(CapteursDistance::getDistanceGauche() == 20))
    {

    }
    Moteurs::setPourcentageDroite(0);
    Moteurs::setPourcentageGauche(pourcentageGauche);
    waitForMs(100);
    ajusterDistance(pourcentageGauche);
    setCoteSuivi(CoteMur::Gauche);
}*/

/**
 * Change de cote vers la droite
 * @pourcentageDroit : la vitesse presente du moteur droit
 * @pourcentageGauche : la vitesse presente du moteur gauche
 */
 /*
void Trajet::changerCoteDroit(uint8_t pourcentageDroit, uint8_t pourcentageGauche)
{
    Moteurs::setPourcentageDroite(0);
    Moteurs::setPourcentageGauche(pourcentageGauche);
    waitForMs(100);
    Moteurs::setPourcentage(pourcentageGauche);
    while(!(CapteursDistance::getDistanceDroit() == 20))
    {
        
    }
    Moteurs::setPourcentageDroite(pourcentageDroit);
    Moteurs::setPourcentageGauche(0);
    waitForMs(100);
    ajusterDistance(pourcentageDroit);
    setCoteSuivi(CoteMur::Droit);
}*/

/**
 * Termine la minuterie et joue une sequence de trois sons aigus
 */
void poteauDetecte()
{   //5.1 cm
    Timer0::stop();
    for (uint8_t i = 0; i < 3; i++)
    {
        Buzzer::play(115);
        waitForMs(200);
        Buzzer::stop();
        waitForMs(100);
    }
}

/**
 * Ajuste la distance au mur pour etre a 15 cm
 * @pourcentage: vitesse du robot
 *//*
void Trajet::ajusterDistance(uint8_t pourcentage)
{
   switch (getCoteSuivi())
   {
       case CoteMur::Droit:
           while(!(CapteursDistance::getDistanceDroit() == 15))
           {
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
            while(!(CapteursDistance::getDistanceGauche() == 15))
            {
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
*/
/**
 * Robot fait un demi demiTour
 */
void demiTour()
{
    ControleMoteurs::doDemiTour(Trajet::getCoteSuivi());
}

/**
 * initialisation pour le trajet
 */
void Trajet::init()
{
    DDRA |= BROCHES_LED;
    CapteursDistance::init();
    ControleMoteurs::init();
    Buzzer::init();
    Bouton::init();
    
    
    
    Interruption::initInt1(&demiTour, TypesTriggerInterrupt::RisingEdge);
    Timer0::setCompACallback(&poteauDetecte);
    Timer0::setCompareOutputMode(COM::Clear, COM::Normal);
    Timer0::setWaveformGenerationMode(WGM::Mode_2);
    Timer0::setPrescaler(Prescaler::Div_256);
    Timer0::setInterruptEnable(true, false, false);
    
    /*// attributs pour la situation initiale

    // le robot ne devrait pas avoir le droit de changer de cote,
    // puisqu'il est suppose ne voir qu'un seul mur initialement
    setDroitChangementCote(false);

    // selectionne le mur initial a suivre
    uint8_t lectDist = 60;
    CapteursDistance::getDistanceGauche(&lectDist);
    // si le mur gauche est assez proche
    if (lectDist <= MUR_INITIAL_DISTANCE_TOL)
    {
        setCoteSuivi(CoteMur::Gauche);
    }
    else
    {
        // sinon, on essaye avec le mur droit
        uint8_t lectDist = 0;
        CapteursDistance::getDistanceDroit(&lectDist);
        if (lectDist <= MUR_INITIAL_DISTANCE_TOL)
        {
            setCoteSuivi(CoteMur::Gauche);
        }
    }
    /// \todo attendre qu'il y ait vraiment un mur choisi?*/
}

/**
 * Execute le trajet
 */
void Trajet::execute()
{
    init();
	for(;;) 
{
	uint8_t gauche = 0;
        bool isValideDroit = CapteursDistance::getDistanceDroit(&gauche);
        uint8_t droit = 0;
        bool isValideGauche = CapteursDistance::getDistanceGauche(&droit);
        
        uint8_t pourcentage = 50;
    EtatTrajet EtatActuel = EtatTrajet::Initial; 
    switch (EtatActuel){
		
		case EtatTrajet::Initial:{
			
			// le robot ne devrait pas avoir le droit de changer de cote,
			// puisqu'il est suppose ne voir qu'un seul mur initialement
			setDroitChangementCote(false);

			// selectionne le mur initial a suivre
			uint8_t lectDist = 60;
			CapteursDistance::getDistanceGauche(&lectDist);
			
			// si le mur gauche est assez proche
			if (lectDist <= MUR_INITIAL_DISTANCE_TOL)
			{
				setCoteSuivi(CoteMur::Gauche);
			}
			else
			{
				// sinon, on essaye avec le mur droit
				uint8_t lectDist = 0;
				
				CapteursDistance::getDistanceDroit(&lectDist);
				
				if (lectDist <= MUR_INITIAL_DISTANCE_TOL)
				{
					setCoteSuivi(CoteMur::Gauche);
				}
			}
			
			EtatActuel = EtatTrajet::SuiviMur;
        break;}
            
        case EtatTrajet::SuiviMur:{
			Timer0::setOCRnA(700);
			Timer0::setOCRnB(350);
			switch (getCoteSuivi())
			{
			
				case CoteMur::Droit:{
					//Si rien n'est détecté par le capteur opposé
					if(gauche > 60)
					{
						ControleMoteurs::updateSuiviMur(getCoteSuivi(), 
						SUIVI_MUR_DISTANCE, SUIVI_MUR_VIT_LIN, 
						SUIVI_MUR_TOL);
					}
					//Si un mur est détecté par le capteur opposé
					else if(gauche >= 10 && gauche <= 60) 
					{
						if(droitChangementCote_)
							EtatActuel = EtatTrajet::ChangementMur;
					}
					//Si un demitour est commandé
					else if(Bouton::getEtat() == EtatBouton::Enfonce) 
					{
						EtatActuel = EtatTrajet::DemiTour;
					}
					//Si un mur doit etre contourné
					else if(droit > 60) 
					{
						EtatActuel = EtatTrajet::ContournementMur;
					}
					
				break;}
				
				case CoteMur::Gauche:{
					if(droit > 60)//Si rien n'est détecté par le capteur opposé
					{
						ControleMoteurs::updateSuiviMur(getCoteSuivi(), 
						SUIVI_MUR_DISTANCE, SUIVI_MUR_VIT_LIN, SUIVI_MUR_TOL);
					}
			 
					else if(droit >= 10 && droit <= 60) //Si un mur est détecté par le capteur opposé
					{
						if(droitChangementCote_)
							EtatActuel = EtatTrajet::ChangementMur;
					}
					else if(Bouton::getEtat() == EtatBouton::Enfonce) //Si un demitour est commandé
					{
						EtatActuel = EtatTrajet::DemiTour;
					}
					else if(gauche > 60) //Si un mur doit etre contourné
					{
						EtatActuel = EtatTrajet::ContournementMur;
					}
					
				break;}
			
						
        break;}
            
        case EtatTrajet::ChangementMur:{
            //Changer de mur et activer l'interdiction de changer de mur
            //Retourner à l'état SuiviMur
            if (Trajet::getCoteSuivi() == CoteMur::Droit)
				Trajet::setCoteSuivi(CoteMur::Gauche);
			else if (Trajet::getCoteSuivi() == CoteMur::Gauche)
				Trajet::setCoteSuivi(CoteMur::Droit);
            ControleMoteurs::updateChangementCote(getCoteSuivi());
            EtatActuel = EtatTrajet::SuiviMur;
        break;}
            
        case EtatTrajet::DemiTour:{
            //En fonction du coté de mur suivi, faire le tour dans le
				//bon sens
            //Retourner à l'état SuiviMur
            ControleMoteurs::doDemiTour(getCoteSuivi());
            
            EtatActuel = EtatTrajet::SuiviMur;   
        break;}
        
        case EtatTrajet::ContournementMur:{
            //En fonction du coté de mur suivi, faire le contournement
				//dans lebon sens
            //Retourner à l'état SuiviMur  
            ControleMoteurs::doContournementMur(getCoteSuivi());
            
            EtatActuel = EtatTrajet::SuiviMur; 
        break;}
        
	}
}
    /*while (true)
    {
        uint8_t gauche = 0;
        bool isValideDroit = CapteursDistance::getDistanceDroit(&gauche);
        uint8_t droit = 0;
        bool isValideGauche = CapteursDistance::getDistanceGauche(&droit);
        
        uint8_t pourcentage = 50;

        switch (getCoteSuivi())
        {
            case CoteMur::Droit:
                Moteurs::setPourcentage(pourcentage);
                if(droit == 15)
                {
                    
                    if ((gauche > 10) && (gauche <= 60))
                    {
                        //Timer0::setOCRnA();//calculer valeurs
                        if (getDroitChangementCote()){
                            changerCoteGauche(pourcentage, pourcentage);
                            setDroitChangementCote(false);
                        }
                        
                    }   
                    //Timer0::stop();
                    
                }
                else if (droit < 15)
                    ajusterDistance(pourcentage);
                else if ((droit > 15) && (droit <= 60))
                    ajusterDistance(pourcentage);
                else if (droit > 60)
                    ControleMoteurs::doContournementMur(CoteMur::Droit);
                if (gauche > 60)
                    setDroitChangementCote(true);
                    
            case CoteMur::Gauche:
                Moteurs::setPourcentage(60);
                if (gauche == 15)
                {
                    if ((droit > 10) && (droit <= 60))
                    {
                        //Timer0::setOCRnA();//calculer valeurs revoir gestion detection poteau
                        if (getDroitChangementCote()){
                            changerCoteDroit(pourcentage, pourcentage);
                            setDroitChangementCote(false);
                        }
                        
                    }
                    //Timer0::stop();
                }
                else if (gauche < 15)
                    ajusterDistance(pourcentage);
                else if ((gauche > 15) && (gauche <= 60))
                    ajusterDistance(pourcentage);
                else if (gauche > 60)
                    ControleMoteurs::doContournementMur(CoteMur::Gauche);
                if (droit > 60)
                    setDroitChangementCote(true);
        }
    }*/
}
}

// ------------------------------------------------------------

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




/**
 * \file trajet.cpp
 * \brief implementation de la classe Diagnostic
 * \author 
 */

#include "trajet.h"
#include "interruption.h"
#include "bouton.h"
#include "moteurs.h"
#include "controle_moteurs.h"
#include "capteurs_distance.h"
#include "buzzer.h"
#include "enums_structs.h"
#include "time.h"
#include "horloge.h"

CoteMur     Trajet::mur_ = CoteMur::Gauche;
bool        Trajet::droitChangementCote_ = false; 
EtatTrajet  Trajet::etatActuel_ = EtatTrajet::Initial;

bool Trajet::verifierDetection()
{
	uint8_t gauche = 0;
    bool isValideDroit = CapteursDistance::getDistanceDroit(&gauche);
    uint8_t droit = 0;
    bool isValideGauche = CapteursDistance::getDistanceGauche(&droit);
    switch (Trajet::getCoteSuivi())
    {
		
        case CoteMur::Droit:{
            if (gauche > 60)
                return false;
            else if ((gauche >= 10) && (gauche <= 60))
                return true;
            break;}
        case CoteMur::Gauche:{
            if (droit > 60)
                return false;
            else if ((droit >= 10) && (droit <= 60))
                return true;
			break;}
    }
}

/**
 * Termine la minuterie et joue une sequence de trois sons aigus
 */
void Trajet::poteauDetecte()
{   //5.1 cm
    if (!(Trajet::verifierDetection())){
        for (uint8_t i = 0; i < 3; i++)
        {
            Buzzer::play(110);
            waitForMs(200);
            Buzzer::stop();
            waitForMs(100);
        }
    }
}

void Trajet::init()
{
    DDRA |= BROCHES_LED;
    CapteursDistance::init();
    ControleMoteurs::init();
    Buzzer::init();
    Bouton::init();
    Horloge::init();
    
    setDroitChangementCote(false);
    etatActuel_ = EtatTrajet::Initial; 

    // autres initialisations de Horloge?
}


void Trajet::execute()
{
    init();
	while(true)
    {
        // lecture des valeurs de distance
		uint8_t gauche = 0;
        bool isValideDroit = CapteursDistance::getDistanceDroit(&gauche);
        uint8_t droit = 0;
        bool isValideGauche = CapteursDistance::getDistanceGauche(&droit);
        Trajet::updateDelAjustement(Trajet::getEnCoursAjustement());
        switch (etatActuel_)
        {
            case EtatTrajet::Initial:{
                Trajet::setEnCoursAjustement(true);
                // le robot ne devrait pas avoir le droit de changer de cote,
                // puisqu'il est suppose ne voir qu'un seul mur initialement
                Trajet::setDroitChangementCote(false);

                // selectionne le mur initial a suivre
                Trajet::setCoteSuivi(selectionMurInitial(gauche, droit));
                
                // change immediatement d'etat pour suivi mur
                Trajet::setEtat(EtatTrajet::SuiviMur);
                Trajet::setEnCoursAjustement(false);
                break;}
            
            case EtatTrajet::SuiviMur:{

                // effectue le suivi de mur
                uint8_t err = ControleMoteurs::updateSuiviMur(Trajet::getCoteSuivi(), 
                                                              SUIVI_MUR_DISTANCE,
                                                              SUIVI_MUR_VIT_LIN,
                                                              SUIVI_MUR_TOL);
                switch (getCoteSuivi())
                {
                
                    case CoteMur::Droit:
                        //Si rien n'est détecté par le capteur opposé
                        if(gauche > 60)
                        {
                            ControleMoteurs::updateSuiviMur(getCoteSuivi(), 
                                                            SUIVI_MUR_DISTANCE,
                                                            SUIVI_MUR_VIT_LIN,
                                                            SUIVI_MUR_TOL);
                            setDroitChangementCote(true);
                        }
                        //Si un mur est détecté par le capteur opposé
                        else if(gauche >= 10 && gauche <= 60) 
                        {   
                            uint8_t temp = gauche;
                            Time t = Time();//timer
                            Time deltaT = Time(0, 2, 0);
                            if(droitChangementCote_){
                                etatActuel_ = EtatTrajet::ChangementMur;
                                Trajet::setEnCoursAjustement(true);
                            }
                            
                                
                            uint8_t dTemp;
                            CapteursDistance::getDistanceGauche(&dTemp);
                            if (dTemp < temp){
                                Time t = Time();//timer
                                Time deltaT = Time(0, 2, 0);
                            
                            }
                            if (!(Horloge::isEcoule(t, deltaT)))
                                Trajet::poteauDetecte();
                        }
                        //Si un demitour est commandé
                        else if(Bouton::getEtat() == EtatBouton::Enfonce) 
                        {
                            etatActuel_ = EtatTrajet::DemiTour;
                            Trajet::setEnCoursAjustement(true);
                        }
                        //Si un mur doit etre contourné
                        else if(droit > 60) 
                        {
                            etatActuel_ = EtatTrajet::ContournementMur;
                            Trajet::setEnCoursAjustement(true);
                        }
                        
                    break;
                    
                    case CoteMur::Gauche:
                        if(droit > 60)//Si rien n'est détecté par le capteur opposé
                        {
                          
                            ControleMoteurs::updateSuiviMur(getCoteSuivi(),
                                                            SUIVI_MUR_DISTANCE,
                                                            SUIVI_MUR_VIT_LIN,
                                                            SUIVI_MUR_TOL);
                            Trajet::setDroitChangementCote(true);
                        }
                
                        else if(droit >= 10 && droit <= 60) //Si un mur est détecté par le capteur opposé
                        {
                            uint8_t temp = droit;
                            Time t = Time();//timer
                            Time deltaT = Time(0, 2, 0);
                            //timer
                            if(droitChangementCote_){
                                etatActuel_ = EtatTrajet::ChangementMur;
                                Trajet::setEnCoursAjustement(true);
                            }
                            uint8_t dTemp;
                            CapteursDistance::getDistanceDroit(&dTemp);
                            if (dTemp < temp){
                                Time t = Time();//timer
                                Time deltaT = Time(0, 2, 0);
                               //timer
                            }
                            if (!(Horloge::isEcoule(t, deltaT)))
                                Trajet::poteauDetecte();
                            
                        }
                        else if(Bouton::getEtat() == EtatBouton::Enfonce) //Si un demitour est commandé
                        {
                            etatActuel_ = EtatTrajet::DemiTour;
                            Trajet::setEnCoursAjustement(true);
                        }
                        else if(gauche > 60) //Si un mur doit etre contourné
                        {
                            etatActuel_ = EtatTrajet::ContournementMur;
                            Trajet::setEnCoursAjustement(true);
                        }
                        
                    break;}

                break;}
                
            case EtatTrajet::ChangementMur:{
                // interdiction de changer de mur
                Trajet::setDroitChangementCote(false);

                // retourner à l'etat SuiviMur
                if (Trajet::getCoteSuivi() == CoteMur::Droit)
                    Trajet::setCoteSuivi(CoteMur::Gauche);
                else if (Trajet::getCoteSuivi() == CoteMur::Gauche)
                    Trajet::setCoteSuivi(CoteMur::Droit);
                ControleMoteurs::updateChangementCote(getCoteSuivi());

                Trajet::setEtat(EtatTrajet::SuiviMur);
                Trajet::setEnCoursAjustement(false);
                break;}
                
            case EtatTrajet::DemiTour:{
                // en fonction du cote de mur suivi, faire le tour dans le bon sens
                Trajet::demiTour();
                // changer le cote du mur suivi
                setCoteSuivi((mur_ == CoteMur::Gauche) ? CoteMur::Droit : CoteMur::Gauche);

                // retour au suivi de mur
                Trajet::setEtat(EtatTrajet::SuiviMur);
                Trajet::setEnCoursAjustement(false);
            break;}
            
            case EtatTrajet::ContournementMur:{
                //En fonction du coté de mur suivi, faire le contournement
                    //dans lebon sens
                //Retourner à l'état SuiviMur 
                ControleMoteurs::doContournementMur(getCoteSuivi());
                
                Trajet::setEtat(EtatTrajet::SuiviMur);
                Trajet::setEnCoursAjustement(false);
            break;}
        }
}
}

// ------------------------------------------------------------

void Trajet::demiTour()
{
    ControleMoteurs::doDemiTour(Trajet::getCoteSuivi());
}

CoteMur Trajet::selectionMurInitial(uint8_t gauche, uint8_t droit)
{
    // assume qu'il y a au moins un mur assez proche
    CoteMur cote = CoteMur::Gauche;

    // si le mur gauche est assez proche
    if (gauche <= MUR_INITIAL_DISTANCE_TOL)
    {
         cote = CoteMur::Gauche;
    }
    else
    {
        // sinon, on essaye avec le mur droit
        if (droit <= MUR_INITIAL_DISTANCE_TOL)
        {
            cote = CoteMur::Droit;
        }
    }

    return cote;
}

// ------------------------------------------------------------

bool Trajet::getDroitChangementCote()
{
    return droitChangementCote_;
}
void Trajet::setEnCoursAjustement(bool ajustement)
{
    enCoursAjustement_ = ajustement;
}

bool Trajet::getEnCoursAjustement()
{
    return enCoursAjustement_ ;
}
void Trajet::setDroitChangementCote(bool droitChangementCote)
{
    droitChangementCote_ = droitChangementCote;
}

void Trajet::updateDelAjustement(bool enCoursAjustement)
{
    // update la LED
    PORTA &= ~(BROCHES_LED);
    PORTA |= (enCoursAjustement) ? VERT : ROUGE;
}

void Trajet::setEtat(EtatTrajet nouvEtat)
{
    etatActuel_ = nouvEtat;
}

CoteMur Trajet::getCoteSuivi()
{
    return mur_;
}

void Trajet::setCoteSuivi(CoteMur mur)
{
    mur_ = mur;
}

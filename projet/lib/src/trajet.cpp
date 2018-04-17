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
bool        Trajet::enCoursAjustement_ = true;
uint8_t     Trajet::distancePrecedenteGauche_ = 0;
uint8_t     Trajet::distancePrecedenteDroit_ = 0;
bool        Trajet::isObjetDetectePrecedemment_ = false;


bool Trajet::isObjetDetecte(uint8_t dist, bool isValide)
{
    bool res = false;

    if (dist > 60)
    {
        res = false;
    }
    else if ((dist >= 10) && (dist <= 60))
    {
        res = true;
    }

    return res;
}

/**
 * Termine la minuterie et joue une sequence de trois sons aigus
 */
void Trajet::poteauDetecte()
{   //5.1 cm
    for (uint8_t i = 0; i < 3; i++)
    {
        Buzzer::play(110);
        waitForMs(200);
        Buzzer::stop();
        waitForMs(100);
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

    Time tObjetDetecte = Time();//timer
    Time deltaPoteau = Time(0, 2, 0); // le temps correspondant a la longueur d'un poteau

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
                ControleMoteurs::updateSuiviMur(Trajet::getCoteSuivi(), 
                                                SUIVI_MUR_DISTANCE,
                                                SUIVI_MUR_VIT_LIN,
                                                SUIVI_MUR_TOL);
                
                switch (getCoteSuivi())
                {
                    case CoteMur::Droit:
                        // Si rien n'est détecté par le capteur opposé
                        if(gauche > 60)
                        {
                            // on peut changer de cote la prochaine fois qu'on detecte un mur
                            setDroitChangementCote(true);
                        }
                        //Si un mur est détecté par le capteur opposé
                        else if(gauche >= 10 && gauche <= 60)
                        {
                            isObjetDetectePrecedemment_ = true;
                            tObjetDetecte = Horloge::getTime();

                            //if(droitChangementCote_)
                            //{
                            //    etatActuel_ = EtatTrajet::ChangementMur;
                            //    Trajet::setEnCoursAjustement(true);
                            //    /// \todo sortir directement apres ceci?
                            //}
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
                            //etatActuel_ = EtatTrajet::ContournementMur;
                            //Trajet::setEnCoursAjustement(true);
                        }

                        // si un objet a ete detecte precedemment
                        if (isObjetDetectePrecedemment_)
                        {
                            // si le temps (de la longueur du poteau) n'est pas ecoule
                            if (!(Horloge::isEcoule(tObjetDetecte, deltaPoteau)))
                            {   
                                // on verifie qu'on continue toujours de voir un objet
                                // (avec une distance toujours similaire)
                                if (!((distancePrecedenteGauche_ - 1) <= gauche
                                            && (gauche <= (distancePrecedenteGauche_ + 1))))
                                {
                                    isObjetDetectePrecedemment_ = false;
                                }
                            }
                            else
                            {
                                isObjetDetectePrecedemment_ = false;
                                // on verifie qu'on ne voit plus l'objet/poteau
                                if (!isObjetDetecte(gauche, isValideGauche))
                                {
                                    // on a bien detecte un poteau
                                    Trajet::poteauDetecte();
                                }
                            }
                        }
                        
                        // update distancePrecedenteGauche_
                        distancePrecedenteGauche_ = gauche;

                    break;
                    
                    case CoteMur::Gauche:
                        // Si rien n'est détecté par le capteur opposé
                        if(droit > 60)
                        {
                            // on peut changer de cote la prochaine fois qu'on detecte un mur
                            setDroitChangementCote(true);
                        }
                        //Si un mur est détecté par le capteur opposé
                        else if(droit >= 10 && droit <= 60)
                        {
                            isObjetDetectePrecedemment_ = true;
                            tObjetDetecte = Horloge::getTime();

                            //if(droitChangementCote_)
                            //{
                            //    etatActuel_ = EtatTrajet::ChangementMur;
                            //    Trajet::setEnCoursAjustement(true);
                            //    /// \todo sortir directement apres ceci?
                            //}
                        }
                        //Si un demitour est commandé
                        else if(Bouton::getEtat() == EtatBouton::Enfonce) 
                        {
                            etatActuel_ = EtatTrajet::DemiTour;
                            Trajet::setEnCoursAjustement(true);
                        }
                        //Si un mur doit etre contourné
                        else if(gauche > 60) 
                        {
                            //etatActuel_ = EtatTrajet::ContournementMur;
                            //Trajet::setEnCoursAjustement(true);
                        }

                        // si un objet a ete detecte precedemment
                        if (isObjetDetectePrecedemment_)
                        {
                            // si le temps (de la longueur du poteau) n'est pas ecoule
                            if (!(Horloge::isEcoule(tObjetDetecte, deltaPoteau)))
                            {   
                                // on verifie qu'on continue toujours de voir un objet
                                // (avec une distance toujours similaire)
                                if (!((distancePrecedenteDroit_ - 1) <= droit
                                            && (droit <= (distancePrecedenteDroit_ + 1))))
                                {
                                    isObjetDetectePrecedemment_ = false;
                                }
                            }
                            else
                            {
                                isObjetDetectePrecedemment_ = false;
                                // on verifie qu'on ne voit plus l'objet/poteau
                                if (!isObjetDetecte(droit, isValideDroit))
                                {
                                    // on a bien detecte un poteau
                                    Trajet::poteauDetecte();
                                }
                            }
                        }
                        
                        // update distancePrecedenteDroit_
                        distancePrecedenteDroit_ = droit;
                    break;}

                break;}
                
            case EtatTrajet::ChangementMur:{
                // interdiction de changer de mur
                Trajet::setDroitChangementCote(false);

                // inverse le cote suivi
                if (Trajet::getCoteSuivi() == CoteMur::Droit)
                    Trajet::setCoteSuivi(CoteMur::Gauche);
                else if (Trajet::getCoteSuivi() == CoteMur::Gauche)
                    Trajet::setCoteSuivi(CoteMur::Droit);
                
                ControleMoteurs::updateChangementCote(getCoteSuivi());

                // retourner à l'etat SuiviMur et set le flag
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

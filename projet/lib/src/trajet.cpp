/**
 * \file trajet.cpp
 * \brief implementation de la classe Trajet
 * \author Simon Moreau
 * \author Mohamed Saddik
 * \author Fares Ouaissa
 * \author Christophe Bourque Bedard
 */

#include "trajet.h"


CoteMur     Trajet::mur_ = CoteMur::Gauche;
bool        Trajet::droitChangementCote_ = false; 
EtatTrajet  Trajet::etatActuel_ = EtatTrajet::Initial;
bool        Trajet::enCoursAjustement_ = true;
uint8_t     Trajet::distancePrecedenteGauche_ = 0;
uint8_t     Trajet::distancePrecedenteDroit_ = 0;
bool        Trajet::isObjetDetectePrecedemment_ = false;


bool Trajet::isObjetDetecte(uint8_t dist)
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

void Trajet::init()
{
    DDRA |= BROCHES_LED;
    CapteursDistance::init();
    ControleMoteurs::init();
    Buzzer::init();
    Bouton::init();
    Horloge::init();
    Debug::init();
    setDroitChangementCote(false);
    etatActuel_ = EtatTrajet::Initial; 

    // autres initialisations de Horloge?
}


void Trajet::execute()
{
    init();
    
	bool changementEnCours = false;
	
    // initialisation de la variable pour le temps detecte
    Time tObjetDetecte = Time();
    // le temps correspondant a la longueur d'un poteau
    Time deltaPoteau = Time(5, 2, 0);
    // le temps correspondant a une partie de la longueur d'un poteau
    Time deltaPoteauDebut = Time(4, 0, 0);
	uint8_t gTemp = 0;
	uint8_t dTemp = 0;
    // lecture de valeurs pour remplir la memoire
    for (int i = 0; i < LONGUEUR_MEMOIRE_LECTURES; i++)
    {
		// lecture des valeurs de distance
		uint8_t gauche = 0;
        CapteursDistance::getDistanceGauche(&gauche);
        uint8_t droit = 0;
        CapteursDistance::getDistanceDroit(&droit);

	}

	while(true)
    {
        // lecture des valeurs de distance
		uint8_t gauche = 0;
        CapteursDistance::getDistanceGauche(&gauche);
        uint8_t droit = 0;
        CapteursDistance::getDistanceDroit(&droit);
		
        Trajet::updateDelAjustement(Trajet::getEnCoursAjustement());
        
        switch (etatActuel_)
        {
            case EtatTrajet::Initial:
            {
                // le robot ne devrait pas avoir le droit de changer de cote,
                // puisqu'il est suppose ne voir qu'un seul mur initialement
                Trajet::setDroitChangementCote(false);
                
                // selectionne le mur initial a suivre
                Trajet::setCoteSuivi(selectionMurInitial(gauche, droit));
                
                // change immediatement d'etat pour suivi mur
                Trajet::setEtat(EtatTrajet::SuiviMur);

                break;
            }
            case EtatTrajet::SuiviMur:
            {
                // effectue le suivi de mur
                uint8_t err = ControleMoteurs::updateSuiviMur(Trajet::getCoteSuivi(), 
                                                              SUIVI_MUR_DISTANCE,
                                                              SUIVI_MUR_VIT_LIN,
                                                              SUIVI_MUR_TOL, changementEnCours);
				
                // update la LED
                Trajet::setEnCoursAjustement(!(err <= 3));
                
                switch (getCoteSuivi())
                {
                    case CoteMur::Droit:
                    {
                        // si un mur est detecte par le capteur oppose
                        if(gauche >= 10 && gauche <= 60)
                        {
                            isObjetDetectePrecedemment_ = true;
                            tObjetDetecte = Horloge::getTime();
							if(droitChangementCote_)
								{
									buzzerChangementMur();
									setCoteSuivi(CoteMur::Gauche);
									setDroitChangementCote(false);
									changementEnCours = true;
								}    
						}
						if (distancePrecedenteDroit_ + 5 >= gauche && distancePrecedenteDroit_ - 5 <= gauche)
							changementEnCours = false;
                        // si rien n'est detecte par le capteur oppose
                        if(gauche > 60)
                        {
                            // on peut changer de cote la prochaine fois qu'on detecte un mur
                            setDroitChangementCote(true);
                        }

					
                        // si un demitour est commande
                        if(Bouton::getEtat() == EtatBouton::Enfonce) 
                        {
                            etatActuel_ = EtatTrajet::DemiTour;
                            setEnCoursAjustement(true);
                        }
                        /*
                        // si un objet a ete detecte precedemment
                        if (isObjetDetectePrecedemment_)
                        {
                            // si le temps (de la longueur du poteau) n'est pas ecoule
                            if (!(Horloge::isEcoule(tObjetDetecte, deltaPoteau)))
                            {
								if (!(Horloge::isEcoule(tObjetDetecte, deltaPoteauDebut)))
								{
									// on verifie qu'on continue toujours de voir un objet
									// (avec une distance toujours similaire)
									if (!((distancePrecedenteGauche_ - 1) <= gauche
												&& (gauche <= (distancePrecedenteGauche_ + 1))))
									{
										isObjetDetectePrecedemment_ = false;
									}
								}
                            }
                            else
                            {
                                isObjetDetectePrecedemment_ = false;

                                // on verifie qu'on ne voit plus l'objet/poteau
                                if (!isObjetDetecte(gauche))
                                {
                                    // on a bien detecte un poteau
                                    buzzerPoteauDetecte();
                                }
                            
                        
                        */
                        // update distancePrecedenteGauche_
                        distancePrecedenteGauche_ = gauche;

                        break;
                    }
                    case CoteMur::Gauche:
                    {
                        // si un mur est detecte par le capteur oppose
                        if(droit >= 10 && droit <= 60)
                        {
                            isObjetDetectePrecedemment_ = true;
                            tObjetDetecte = Horloge::getTime();
							if(droitChangementCote_)
									{
										buzzerChangementMur();
										setCoteSuivi(CoteMur::Droit);
										setDroitChangementCote(false);
										changementEnCours = true;
                           
                            
                        }
						if (distancePrecedenteGauche_ + 5 >= droit && distancePrecedenteGauche_ - 5 <= droit)
							changementEnCours = false;
                        // si rien n'est detecte par le capteur oppose
                        if(droit > 60)
                        {
                            // on peut changer de cote la prochaine fois qu'on detecte un mur
                            setDroitChangementCote(true);
                        }
            
                        
                        // si un demitour est commande
                        if(Bouton::getEtat() == EtatBouton::Enfonce) 
                        {
                            etatActuel_ = EtatTrajet::DemiTour;
                            setEnCoursAjustement(true);
                        }

                        // si un objet a ete detecte precedemment
                        /*if (isObjetDetectePrecedemment_)
                        {
                            // si le temps (de la longueur du poteau) n'est pas ecoule
                            if (!(Horloge::isEcoule(tObjetDetecte, deltaPoteau)))
                            {
								if (!(Horloge::isEcoule(tObjetDetecte, deltaPoteauDebut)))
								{
									// on verifie qu'on continue toujours de voir un objet
									// (avec une distance toujours similaire)
									if (!((distancePrecedenteDroit_ - 1) <= droit
											 && (droit <= (distancePrecedenteDroit_ + 1))))
									{
										isObjetDetectePrecedemment_ = false;
									}
								}
                            }
                            else
                            {
                                isObjetDetectePrecedemment_ = false;

                                // on verifie qu'on ne voit plus l'objet/poteau
                                if (!isObjetDetecte(droit))
                                {
                                    // on a bien detecte un poteau
                                    buzzerPoteauDetecte();
                                }
                                
									
								
								
									
								}
                            }
                        
                        */
                        // update distancePrecedenteDroit_
                        distancePrecedenteDroit_ = droit;
                        
                        break;
                    
                }
                break;
            }
            case EtatTrajet::DemiTour:
            {
                // en fonction du cote de mur suivi, faire le tour dans le bon sens
                demiTour();

                // changer le cote du mur suivi
                setCoteSuivi((mur_ == CoteMur::Gauche) ? CoteMur::Droit : CoteMur::Gauche);

                // retour au suivi de mur
                setEtat(EtatTrajet::SuiviMur);
                setEnCoursAjustement(false);

                break;
            }
            
        }
    }
}

// ------------------------------------------------------------

void Trajet::buzzerPoteauDetecte()
{   //5.1 cm
    for (uint8_t i = 0; i < 3; i++)
    {
        Buzzer::play(110);
        waitForMs(200);
        Buzzer::stop();
        waitForMs(100);
    }
}

void Trajet::buzzerChangementMur()
{
    Buzzer::play(50);
	waitForMs(200);
    Buzzer::play(80);
    waitForMs(200);
	Buzzer::stop();
}

void Trajet::buzzerSelectionMur(CoteMur cote)
{
    switch (cote)
    {
        case CoteMur::Gauche:
            Buzzer::play(100);
            waitForMs(300);
            Buzzer::stop();
            break;
        case CoteMur::Droit:
            Buzzer::play(50);
            waitForMs(100);
			Buzzer::stop();
			waitForMs(100);
            Buzzer::play(50);
            waitForMs(100);
			Buzzer::stop();
            break;
    }
}

void Trajet::demiTour()
{
    ControleMoteurs::doDemiTour(Trajet::getCoteSuivi());
}

CoteMur Trajet::selectionMurInitial(uint8_t gauche, uint8_t droit)
{
    // assume qu'il y a au moins un mur assez proche
    CoteMur cote = CoteMur::Gauche;

    // si le mur gauche est assez proche
    if (gauche <= droit)
    {
        cote = CoteMur::Gauche;
         
    }
    else 
    {
        cote = CoteMur::Droit;
    }

    buzzerSelectionMur(cote);

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

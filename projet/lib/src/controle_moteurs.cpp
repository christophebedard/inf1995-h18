/**
 * \file controle_moteurs.cpp
 * \brief implementation de la classe ControleMoteurs
 * \author Christophe Bourque Bedard
 * \author Simon Moreau
 * \author Fares Ouaissa
 * \author Mohamed Saddik
 */

#include "controle_moteurs.h"


uint8_t ControleMoteurs::vitesseLineaire_ = 0;
uint8_t ControleMoteurs::vitesseAngulaire_ = 0;
DirectionMoteur ControleMoteurs::directionLineaire_ = DirectionMoteur::Avant;
DirectionMoteur ControleMoteurs::directionAngulaire_ = DirectionMoteur::Avant;


void ControleMoteurs::init()
{
    Moteurs::init();
}

void ControleMoteurs::doDemiTour(CoteMur murSuivi)
{
    // determine le sens de rotation selon le mur suivi
    DirectionMoteur dirAng = DirectionMoteur::Avant;
    switch (murSuivi)
    {
        case CoteMur::Gauche:
            dirAng = DirectionMoteur::Arriere;
            break;
        case CoteMur::Droit:
            dirAng = DirectionMoteur::Avant;
            break;
    }

    setVitesses(0, DirectionMoteur::Avant, DEMI_TOUR_VITESSE_ANG, dirAng);
    waitForMs(DEMI_TOUR_ATTENTE);
    setVitesses(0, DirectionMoteur::Avant, DEMI_TOUR_IMPULSION_VITESSE_ANG, ((dirAng == DirectionMoteur::Arriere) ? DirectionMoteur::Avant : DirectionMoteur::Arriere));
    waitForMs(DEMI_TOUR_ATTENTE_IMPULSION);
    setVitesses(0, DirectionMoteur::Avant, 0, DirectionMoteur::Avant);
}

void ControleMoteurs::doContournementMur(CoteMur murCont)
{
    /// \todo experimental

    // determine le sens de rotation selon le mur a contourner
    DirectionMoteur dirAng = DirectionMoteur::Avant;
    switch (murCont)
    {
        case CoteMur::Gauche:
            dirAng = DirectionMoteur::Avant;
            break;
        case CoteMur::Droit:
            dirAng = DirectionMoteur::Arriere;
            break;
    }

    setVitesses(0, DirectionMoteur::Avant, CONTOURNEMENT_VITESSE_ANG, dirAng);
    waitForMs(CONTOURNEMENT_ATTENTE);
    setVitesses(0, DirectionMoteur::Avant, 0, DirectionMoteur::Avant);
}

void ControleMoteurs::updateChangementCote(CoteMur nouvMur)
{
    /// \todo experimental
    if (nouvMur == CoteMur::Droit){
        ControleMoteurs::setVitesses(0, DirectionMoteur::Avant, CHANGEMENT_VITESSE_ANG, DirectionMoteur::Arriere);
        waitForMs(CHANGEMENT_ATTENTE);
    }
    else if (nouvMur == CoteMur::Gauche){
        ControleMoteurs::setVitesses(0, DirectionMoteur::Avant, CHANGEMENT_VITESSE_ANG, DirectionMoteur::Avant);
        waitForMs(CHANGEMENT_ATTENTE);
	}
	//setVitesses(CHANGEMENT_VITESSE_LIN,DirectionMoteur::Avant, 0, DirectionMoteur::Avant); 
}

uint8_t ControleMoteurs::updateSuiviMur(CoteMur murSuivi, uint8_t cmdDist, uint8_t vitLin, uint8_t tolErr)
{
    /// \todo experimental

    // lecture
    uint8_t lectDist = 0;
    bool isValide = false;
    switch (murSuivi)
    {
        case CoteMur::Gauche:
            isValide = CapteursDistance::getDistanceGauche(&lectDist);
            break;
        case CoteMur::Droit:
            isValide = CapteursDistance::getDistanceDroit(&lectDist);
            break;
    }
    // initialise les variables de commande
    uint8_t err = 0;
    uint8_t vitAng = 0;
    DirectionMoteur dirAng = DirectionMoteur::Avant;

    // si lecture valide
    if (isValide)
    {
        // selon la valeur de l'erreur
        err = (lectDist >= cmdDist) ? (lectDist - cmdDist) : (cmdDist - lectDist);

        // si erreur de direction
        if (err > tolErr)
        {
            // dtermine la direction de la vitesse angulaire
            switch (murSuivi)
            {
                case CoteMur::Gauche:
                    dirAng = (lectDist >= cmdDist) ? DirectionMoteur::Avant : DirectionMoteur::Arriere;
                    break;
                case CoteMur::Droit:
                    dirAng = (lectDist >= cmdDist) ? DirectionMoteur::Arriere : DirectionMoteur::Avant;
                    break;
            }
            
            // determine la vitesse angulaire a appliquer selon l'erreur
            switch (err)
            {
                default: vitAng = 0; break;
                case 0:
                case 1:
                case 2:
                case 3: vitAng = 3; break;
                case 4:
                case 5: vitAng = 6; break;
                case 6:
                case 7:
                case 8:
                case 9:
                case 10: vitAng = 7; break;
                case 11:
                case 12:
                case 13:
                case 14:
                case 15: vitAng = 9; break;
                case 16:
                case 17:
                case 18:
                case 19:
                case 20: vitAng = 10; break;
                case 21:
                case 22:
                case 23:
                case 24:
                case 25: 
                case 26:
                case 27:
                case 28:
                case 29:
                case 30: vitAng = 14; break;
                case 31:
                case 32:
                case 33:
                case 34:
                case 35: vitAng = 16; break;
                case 36:
                case 37:
                case 38:
                case 39:
                case 40: vitAng = 18; break;
                case 41:
                case 42:
                case 43:
                case 44:
                case 45:
                case 46:
                case 47:
                case 48:
                case 49:
                case 50: vitAng = 20; break;
            }
        }
    }
    else
    {
        // si la lecture n'est pas valide et que l'on estime
        // que c'est parce que le robot est trop proche
        if (lectDist < 20)
        {
            vitAng = 25;
            switch (murSuivi)
            {
                case CoteMur::Gauche:
                    dirAng = DirectionMoteur::Arriere;
                    break;
                case CoteMur::Droit:
                    dirAng = DirectionMoteur::Avant;
                    break;
            }
        }
        else if (lectDist > 20)
        {
            vitAng = 40;
            switch (murSuivi)
            {
                case CoteMur::Gauche:
                    dirAng = DirectionMoteur::Avant;
                    break;
                case CoteMur::Droit:
                    dirAng = DirectionMoteur::Arriere;
                    break;
            }
        }

        // set l'erreur comme etant tres grand
        // (pour signifier que le robot n'est evidemment pas dans la bonne position)
        err = 50;
    }
    if (lectDist < 7)
        {
            vitAng = 25;
            switch (murSuivi)
            {
                case CoteMur::Gauche:
                    dirAng = DirectionMoteur::Arriere;
                    break;
                case CoteMur::Droit:
                    dirAng = DirectionMoteur::Avant;
                    break;
            }
        }
     else if (lectDist > 60)
        {
            vitAng = 40;
            switch (murSuivi)
            {
                case CoteMur::Gauche:
                    dirAng = DirectionMoteur::Avant;
                    break;
                case CoteMur::Droit:
                    dirAng = DirectionMoteur::Arriere;
                    break;
            }
        }


    setVitesses(vitLin, DirectionMoteur::Avant, vitAng, dirAng);

    // Debug::out(lectDist);
    // Debug::out(", ");
    // Debug::out(err);
    // Debug::out(", ");
    // Debug::out(vitAng);
    // Debug::out("\n");

    return err;
}

void ControleMoteurs::setVitesses(uint8_t vitLin, DirectionMoteur dirLin, uint8_t vitAng, DirectionMoteur dirAng)
{
    setVitesseLineaire(vitLin, dirLin);
    setVitesseAngulaire(vitAng, dirAng);
    updateMoteurs();
}

void ControleMoteurs::updateMoteurs()
{
    // calcul des vitesses
    uint8_t vitGauche = 0;
    uint8_t vitDroit = 0;
    DirectionMoteur dirGauche = DirectionMoteur::Avant;
    DirectionMoteur dirDroit = DirectionMoteur::Avant;
    calculVitessesMoteurs(&vitGauche, &vitDroit, &dirGauche, &dirDroit);
	Debug::out(vitGauche);
	Debug::out(",");
	Debug::out(vitDroit);
	Debug::out("\n");

    // set les vitesses
    Moteurs::setDirectionMoteurGauche(dirGauche);
    Moteurs::setDirectionMoteurDroit(dirDroit);
    Moteurs::setPourcentageGauche(vitGauche);
    Moteurs::setPourcentageDroite(vitDroit);
}

void ControleMoteurs::calculVitessesMoteurs(uint8_t* vitGauche, uint8_t* vitDroit, DirectionMoteur* dirGauche, DirectionMoteur* dirDroit)
{
    // vitesse lineaire signee
    double vitLin_d = (double)vitesseLineaire_;
    vitLin_d *= (directionLineaire_ == DirectionMoteur::Avant) ? 1.0 : -1.0;

    // vitesse lineaire absolue associee a la vitesse angulaire
    double correctionAng_d = (double)vitesseAngulaire_;
    correctionAng_d *= (directionAngulaire_ == DirectionMoteur::Avant) ? 1.0 : -1.0;

    // vitesses signees des deux moteurs
    double vitGauche_d = vitLin_d - correctionAng_d;
    double vitDroit_d = vitLin_d + correctionAng_d;

    // deduit les directions des moteurs
    *dirGauche = (vitGauche_d >= 0.0) ? DirectionMoteur::Avant : DirectionMoteur::Arriere;
    *dirDroit = (vitDroit_d >= 0.0) ? DirectionMoteur::Avant : DirectionMoteur::Arriere;

    // valeur absolue des vitesses et convertion
    *vitGauche = (uint8_t)fabs(vitGauche_d);
    *vitDroit = (uint8_t)fabs(vitDroit_d);
}

void ControleMoteurs::setVitesseLineaire(uint8_t vitLin, DirectionMoteur dirLin)
{
    vitesseLineaire_ = vitLin;
    directionLineaire_ = dirLin;
}

void ControleMoteurs::setVitesseAngulaire(uint8_t vitAng, DirectionMoteur dirAng)
{
    vitesseAngulaire_ = vitAng;
    directionAngulaire_ = dirAng;
}

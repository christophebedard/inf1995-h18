/**
 * \file controle_moteurs.cpp
 * \brief implementation de la classe ControleMoteurs
 * \author 
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
    /// \todo experimental

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

    /// \todo #define DEMI_TOUR_VIT_ANG
    setVitesses(0, DirectionMoteur::Avant, 50, dirAng);
    /// \todo #define DEMI_TOUR_ATTENTE
    waitForMs(2200);
    /// \todo #define DEMI_TOUR_VIT_ANG_IMPULSION
    setVitesses(0, DirectionMoteur::Avant, 50, ((dirAng == DirectionMoteur::Arriere) ? DirectionMoteur::Avant : DirectionMoteur::Arriere));
    /// \todo #define DEMI_TOUR_ATTENTE_IMPULSION
    waitForMs(100);
    setVitesses(0, DirectionMoteur::Avant, 0, DirectionMoteur::Avant);
}

void ControleMoteurs::updateContournementMur(CoteMur murSuivi)
{
    /// \todo experimental
}

void ControleMoteurs::updateChangementCote(CoteMur nouvMur)
{
    /// \todo experimental
}

void ControleMoteurs::updateSuiviMur(CoteMur murSuivi, uint8_t cmdDist, uint8_t vitLin, uint8_t tolErr)
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
            vitAng = (0 <= err && err <= 20) ? 8 : 12;
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
                case 25: vitAng = 10; break;
                case 26:
                case 27:
                case 28:
                case 29:
                case 30: vitAng = 12; break;
                case 31:
                case 32:
                case 33:
                case 34:
                case 35: vitAng = 14; break;
                case 36:
                case 37:
                case 38:
                case 39:
                case 40: vitAng = 16; break;
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
    }

    setVitesses(vitLin, DirectionMoteur::Avant, vitAng, dirAng);

    Debug::out(lectDist);
    Debug::out(", ");
    Debug::out(err);
    Debug::out(", ");
    Debug::out(vitAng);
    Debug::out("\n");
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

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

    // si lecture valide
    if (isValide)
    {
        // selon la valeur de l'erreur
        uint8_t err = (lectDist >= cmdDist) ? (lectDist - cmdDist) : (cmdDist - lectDist);

        // initialise les variables de commande
        uint8_t vitAng = 0;
        DirectionMoteur dirAng = DirectionMoteur::Avant;

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
            
            // determine la vitesse angulaire a appliquer proportionnellement a l'erreur
            vitAng = err * 2;
        }

        setVitesses(vitLin, DirectionMoteur::Avant, vitAng, dirAng);
    }
    /// \todo peut-etre donner une vitesse par defaut aux roues si la lecture n'est pas valide?
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

void ControleMoteurs::setVitesses(uint8_t vitLin, DirectionMoteur dirLin, uint8_t vitAng, DirectionMoteur dirAng)
{
    setVitesseLineaire(vitLin, dirLin);
    setVitesseAngulaire(vitAng, dirAng);
    updateMoteurs();
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

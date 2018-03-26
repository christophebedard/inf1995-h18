/**
 * \file moteurs.cpp
 * \brief implementation de la classe Moteurs
 * \author 
 */

#include "moteurs.h"


void Moteurs::init()
{
    PWM::init();

    // direction initiale : avant
    setDirection(DirectionMoteur::Moteur_avant);
}

void Moteurs::setDirection(const DirectionMoteur& dir)
{
    setDirectionMoteurGauche(dir);
    setDirectionMoteurDroit(dir);
}

void Moteurs::setDirectionMoteurGauche(const DirectionMoteur& dirG)
{
    setDirectionBroche(dirG, BROCHE_MOTEUR_GAUCHE_DIRECTION);
}

void Moteurs::setDirectionMoteurDroit(const DirectionMoteur& dirD)
{
    setDirectionBroche(dirD, BROCHE_MOTEUR_DROIT_DIRECTION);
}

void Moteurs::setDirectionBroche(const DirectionMoteur& dir, uint8_t b)
{
    /// \todo verifier directions
    switch(dir)
    {
        default:
        case DirectionMoteur::Moteur_avant:
            DDRD |= _BV(_BROCHE_TO_PIN(b));
            break;
        case DirectionMoteur::Moteur_arriere:
            DDRD &= ~(_BV(_BROCHE_TO_PIN(b)));
            break;
    }
}

void Moteurs::setPourcentage(const uint8_t& pourcentage)
{
    setPourcentageGauche(pourcentage);
    setPourcentageDroite(pourcentage);
}

void Moteurs::setPourcentageGauche(const uint8_t& pourcentage)
{
    PWM::setPourcentageOCRnB(pourcentage);
}

void Moteurs::setPourcentageDroite(const uint8_t& pourcentage)
{
    PWM::setPourcentageOCRnA(pourcentage);
}

void Moteurs::virageDroit(const uint8_t& pourcentage)
{
	setPourcentageGauche(pourcentage);

    waitForMs(2000);

	setPourcentageGauche(0);
}

void Moteurs::virageGauche(const uint8_t& pourcentage)
{
	setPourcentageDroite(pourcentage);

    waitForMs(2000);

	setPourcentageDroite(0);
}
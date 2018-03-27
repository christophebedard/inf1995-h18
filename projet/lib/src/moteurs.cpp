/**
 * \file moteurs.cpp
 * \brief implementation de la classe Moteurs
 * \author 
 */

#include "moteurs.h"

uint8_t Moteurs::pourcentageMoteurGauche_ = 0;
uint8_t Moteurs::pourcentageMoteurDroit_ = 0;
DirectionMoteur Moteurs::directionMoteurGauche_ = DirectionMoteur::Avant;
DirectionMoteur Moteurs::directionMoteurDroit_ = DirectionMoteur::Avant;

void Moteurs::init()
{
    PWM::init();

    // broches de direction en sortie
    DDRD |= _BV(_BROCHE_TO_PIN(BROCHE_MOTEUR_GAUCHE_DIRECTION)) | _BV(_BROCHE_TO_PIN(BROCHE_MOTEUR_DROIT_DIRECTION));

    // direction initiale : avant
    /// \todo remarque : redondant avec l'initialisation des attributs statiques
    setDirection(DirectionMoteur::Avant);
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
    /// \todo verifier directions selon sens de connexion des moteurs
    switch(dir)
    {
        default:
        case DirectionMoteur::Avant:
            PORTD |= _BV(_BROCHE_TO_PIN(b));
            break;
        case DirectionMoteur::Arriere:
            PORTD &= ~(_BV(_BROCHE_TO_PIN(b)));
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
    pourcentageMoteurGauche_ = pourcentage;
    PWM::setPourcentageOCRnB(pourcentage);
}

void Moteurs::setPourcentageDroite(const uint8_t& pourcentage)
{
    pourcentageMoteurDroit_ = pourcentage;
    PWM::setPourcentageOCRnA(pourcentage);
}

void Moteurs::virageDroit(const uint8_t& pourcentage)
{
    setDirection(DirectionMoteur::Avant);
	setPourcentageGauche(pourcentage);

    /// \todo tester et ameliorer les virages
    waitForMs(2000);

	setPourcentageGauche(0);
}

void Moteurs::virageGauche(const uint8_t& pourcentage)
{
    setDirection(DirectionMoteur::Avant);
	setPourcentageDroite(pourcentage);

    /// \todo tester et ameliorer les virages
    waitForMs(2000);

	setPourcentageDroite(0);
}

DirectionMoteur Moteurs::getDirectionMoteurGauche()
{
    return directionMoteurGauche_;
}

DirectionMoteur Moteurs::getDirectionMoteurDroite()
{
    return directionMoteurDroit_;
}

uint8_t Moteurs::getPourcentageMoteurGauche()
{
    return pourcentageMoteurGauche_;
}

uint8_t Moteurs::getPourcentageMoteurDroite()
{
    return pourcentageMoteurDroit_;
}
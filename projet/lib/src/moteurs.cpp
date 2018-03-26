/**
 * \file moteurs.cpp
 * \brief implementation de la classe Moteurs
 * \author 
 */

#include "moteurs.h"


void Moteurs::init()
{
    PWM::init();
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
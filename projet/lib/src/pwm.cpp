/**
 * \file pwm.cpp
 * \brief implementation de la classe PWM
 * \author 
 * 
 * Brancher le moteur gauche entre BROCHE_MOTEUR_GAUCHE_PWM et BROCHE_MOTEUR_GAUCHE_DIRECTION
 * Brancher le moteur droit entre BROCHE_MOTEUR_DROIT_PWM et BROCHE_MOTEUR_DROIT_DIRECTION
 */

#include "pwm.h"


void PWM::init()
{
	// mettre les pins en sortie
	DDRD |= _BV(_BROCHE_TO_PIN(BROCHE_MOTEUR_GAUCHE_PWM));
	DDRD |= _BV(_BROCHE_TO_PIN(BROCHE_MOTEUR_DROIT_PWM));

	cli();

	Timer1::setCompareOutputMode(COM::COM_clear, COM::COM_clear);
	Timer1::setWaveformGenerationMode(WGM::WGM_1);
	Timer1::setPrescaler(Prescaler::Pres_8);

	sei();
}

void PWM::setPourcentage(const uint8_t& pourcentage)
{
	setPourcentageGauche(pourcentage);
	setPourcentageGauche(pourcentage);
}

void PWM::setPourcentageGauche(const uint8_t& pourcentage)
{
	Timer1::setOCRnB(getValOCRnFromPourcentage(pourcentage));
}

void PWM::setPourcentageDroite(const uint8_t& pourcentage)
{
	Timer1::setOCRnA(getValOCRnFromPourcentage(pourcentage));
}

void PWM::virageDroit(const uint8_t& pourcentage)
{
	PWM::setPourcentageGauche(pourcentage);

    waitForMs(2000);

	PWM::setPourcentageGauche(0);
}

void PWM::virageGauche(const uint8_t& pourcentage)
{
	PWM::setPourcentageDroite(pourcentage);

    waitForMs(2000);

	PWM::setPourcentageDroite(0);
}

uint16_t PWM::getValOCRnFromPourcentage(const uint8_t& pourcentage)
{
	return (uint16_t)pourcentage * 255 / 100;
}

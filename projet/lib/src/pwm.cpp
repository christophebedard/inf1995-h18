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

	Timer1::setCompareOutputMode(COM::Clear, COM::Clear);
	Timer1::setWaveformGenerationMode(WGM::Mode_1);
	Timer1::setPrescaler(Prescaler::Div_8);

	sei();
}

void PWM::setPourcentageOCRnB(const uint8_t& pourcentage)
{
	Timer1::setOCRnB(getValOCRnFromPourcentage(pourcentage));
}

void PWM::setPourcentageOCRnA(const uint8_t& pourcentage)
{
	Timer1::setOCRnA(getValOCRnFromPourcentage(pourcentage));
}

uint16_t PWM::getValOCRnFromPourcentage(const uint8_t& pourcentage)
{
	return (uint16_t)pourcentage * 255 / 100;
}

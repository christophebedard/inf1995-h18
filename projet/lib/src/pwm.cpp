/**
 * \file pwm.cpp
 * \brief implementation de la classe PWM
 * \author 
 * 
 * Brancher le moteur gauche entre BROCHE_MOTEUR_GAUCHE et BROCHE_MOTEUR_GAUCHE+2
 * Brancher le moteur droit entre BROCHE_MOTEUR_DROIT et BROCHE_MOTEUR_DROIT+2
 */

#include "pwm.h"


const uint8_t PWM::BROCHE_MOTEUR_GAUCHE = 6;
const uint8_t PWM::BROCHE_MOTEUR_DROIT = 5;

void PWM::init()
{
	// mettre les pins en sortie
	DDRD |= _BV(BROCHE_MOTEUR_GAUCHE - 1);
	DDRD |= _BV(BROCHE_MOTEUR_DROIT - 1);

	cli();

	Timer1::setCompareOutputMode(COM::COM_clear, COM::COM_clear);
	Timer1::setWaveformGenerationMode(WGM::WGM_1);
	Timer1::setPrescaler(Prescaler::Pres_8);

	sei();
}

void PWM::setPourcentage(const uint8_t& pourcentage)
{
	uint16_t val = (uint16_t)pourcentage * 255 / 100;
	Timer1::setOCRnA(val);
	Timer1::setOCRnB(val);
}

void PWM::virageDroit(const uint8_t& pourcentage)
{
	uint16_t val = (uint16_t)pourcentage * 255 / 100;
	Timer1::setOCRnB(val);

    waitForMs(2000);

	Timer1::setOCRnB(0);
}

void PWM::virageGauche(const uint8_t& pourcentage)
{
	uint16_t val = (uint16_t)pourcentage * 255 / 100;
	Timer1::setOCRnA(val);

    waitForMs(2000);

	Timer1::setOCRnA(0);
}

/**
 * \file horloge.cpp
 * \brief implementation de la classe Horloge
 * \author 
 */

#include "horloge.h"

Time Horloge::absTime_;

void callback1MHz()
{
	Horloge::systemTick();
}

void Horloge::init()
{
	cli();

	Timer0::setWaveformGenerationMode(WGM::Mode_2);
	Timer0::setPrescaler(Prescaler::Div_64);
	Timer0::setInterruptEnable(true, false, false);
	Timer0::setCompACallback(&callback1MHz);
	Timer0::setOCRnA(125);
	Timer0::resetTCNTn();

	sei();
}

void Horloge::systemTick()
{
	// incremente temps (dixieme de seconde)
	absTime_++;
}

bool Horloge::isEcoule(const Time& refT, const Time& deltaT)
{
	return isEcoule(refT, deltaT, getTime());
}

bool Horloge::isEcoule(const Time& refT, const Time& deltaT, const Time& absT)
{
	return ((refT + deltaT) > absT);
}

Time Horloge::getTime()
{
	return absTime_;
}

void Horloge::debug()
{
	Debug::out(absTime_);
}

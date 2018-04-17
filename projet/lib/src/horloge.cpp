/**
 * \file horloge.cpp
 * \brief implementation de la classe Horloge
 * \author 
 */

#include "horloge.h"

Time Horloge::absTime_;

volatile uint8_t postScalerCount = 0;

void callback122Hz()
{
	postScalerCount++;
	if (postScalerCount > POSTSCALER)
	{
		postScalerCount = 0;
		Horloge::systemTick();
	}
}

void Horloge::init()
{
	cli();

	// prescaler	= 1024
	// OCRnA		= 255
	// frequence	= (8 000 000 / (1024 * 255))
	//				= 30.6372
	// postscaler	= 3
	// frequence'	= frequence / postscaler
	//				= 30.6372 / 3
	//				= 10.2124 Hz
	// erreur freq	= 0.2124 Hz (donc trop lent)

	Timer0::setWaveformGenerationMode(WGM::Mode_2);
	Timer0::setPrescaler(Prescaler::Div_1024);
	Timer0::setInterruptEnable(true, false, false);
	Timer0::setCompACallback(&callback122Hz);
	Timer0::setOCRnA(255);
	Timer0::resetTCNTn();

	sei();
}

void Horloge::reinitialiser()
{
    Timer0::stop();
    Horloge::init();
}

void Horloge::systemTick()
{
	// incremente temps (dixieme de seconde)
	//absTime_.tick();
	absTime_++;
}

bool Horloge::isEcoule(const Time& refT, const Time& deltaT)
{
	return isEcoule(refT, deltaT, absTime_);
}

bool Horloge::isEcoule(const Time& refT, const Time& deltaT, const Time& absT)
{
	return (absT >= (refT + deltaT));
}

Time Horloge::getTime()
{
	return absTime_;
}

void Horloge::debug()
{
	Debug::out(absTime_);
}

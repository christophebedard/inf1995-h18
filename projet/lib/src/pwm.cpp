#include "pwm.h"


void initPWM()
{
	// mettre les pins en sortie (chap. "I/O ports")
	// OC1A : port D, pin 5/broche 6
	DDRD |= _BV(5);
	// OC1B : port D, pin 4/broche 5
	DDRD |= _BV(4);

	Timer1::setCompareOutputMode(COM::COM_clear, COM::COM_clear);
	Timer1::setWaveformGenerationMode(WGM::WGM_1);
	Timer1::setPrescaler(Prescaler::Pres_8);
}

void ajustementPWM(const uint8_t& pourcentage)
{
	uint16_t val = (uint16_t)pourcentage * 255 / 100;
	Timer1::setOCRnA(val);
	Timer1::setOCRnB(val);
}

void virageDroit(const uint8_t& pourcentage)
{
	uint16_t val = (uint16_t)pourcentage * 255 / 100;
	Timer1::setOCRnB(val);

    waitForMs(2000);

	Timer1::setOCRnB(0);
}

void virageGauche(const uint8_t& pourcentage)
{
	uint16_t val = (uint16_t)pourcentage * 255 / 100;
	Timer1::setOCRnA(val);

    waitForMs(2000);

	Timer1::setOCRnA(0);
}

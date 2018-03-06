#include "pwm.h"

void initPWM()
{
	// compare output mode 10 (Clear OCnA/OCnB on Compare Match (Set output to low level))
	// waveform generation mode 1 (PWM, Phase Correct, 8-bit)
	TCCR1A = (1 << COM1A1) | (1 << COM1B1)| (1 << WGM10);
	// division d'horloge par 8
	TCCR1B = (1 << CS11);
}


void ajustementPWM(const uint8_t& pourcentage)
{
	// mise à un des sorties OC1A et OC1B sur comparaison
	// réussie en mode PWM 8 bits, phase correcte
	// et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6
	// page 177 de la description technique du ATmega324PA)
	OCR1A = pourcentage * 255 / 100;
	OCR1B = pourcentage * 255 / 100;
}

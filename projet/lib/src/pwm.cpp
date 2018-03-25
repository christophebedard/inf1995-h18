#include "pwm.h"
#include "delai.h"
void initPWM()
{
	// mettre les pins en sortie (chap. "I/O ports")
	// OC1A : port D, pin 5
	DDRD |= _BV(5);
	// OC1B : port D, pin 4
	DDRD |= _BV(4);

	// compare output mode 10 (Clear OCnA/OCnB on Compare Match (Set output to low level))
	// waveform generation mode 1 (PWM, Phase Correct, 8-bit)
	TCCR1A = _BV(COM1A1) | _BV(COM1B1)| _BV(WGM10);
	// division d'horloge par 8
	TCCR1B = _BV(CS11);
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

void virageDroit(const uint8_t& pourcentage){

    OCR1B = pourcentage * 255 / 100;
    waitForMs(2000);
    OCR1B = 0;
}

void virageGauche(const uint8_t& pourcentage){
    OCR1A = pourcentage * 255 / 100;
    waitForMs(2000);
    OCR1A = 0;
}

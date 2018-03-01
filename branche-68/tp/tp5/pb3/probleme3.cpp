/* Fichier : probleme3.cpp
* Auteur : Bourque Bédard Christophe  & Mohamed Saddik
* Date : 15 février 2018
*
* Le programme utilise un PWM materiel pour faire tourner les 
* roues ou faire allumer un DEL a intensite variable.
*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Definition des constantes
const uint8_t SORTIE = 0xff;
const uint8_t ENTREE = 0X00;

/********************************************************************
* Cette fonction de de l'initialisation 
*********************************************************************/
void initialisation() {
	// de-activation des interruptions
	cli ();

	// configuration des ports
	DDRD = SORTIE; // Port D en mode entrée.

	// re-activation des interruptions
	sei ();
}

/********************************************************************
* Initialisation du PWM avec le timer1 
*********************************************************************/
void initPWM() {
	// compare output mode 10 (Clear OCnA/OCnB on Compare Match (Set output to low level))
	// waveform generation mode 1 (PWM, Phase Correct, 8-bit)
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 <<WGM10);
	// division d'horloge
	TCCR1B |= (1 << CS11);
	TCCR1C = 0;
}

/********************************************************************
* Ajustement du ratio du PWM
* 
* \param ratio : ratio du PWM en pourcent [0, 100]
*********************************************************************/
void ajustementPWM(uint8_t ratio) {
	// mise à un des sorties OC1A et OC1B sur comparaison
	// réussie en mode PWM 8 bits, phase correcte
	// et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6
	// page 177 de la description technique du ATmega324PA)
	OCR1A = ratio * 255 / 100;
	OCR1B = ratio * 255 / 100;
}

/*******************************************************************************
* Fonction principale. 
*******************************************************************************/
int main() {
	initialisation();
	initPWM();
	
	ajustementPWM(0);
	_delay_ms(2000);
	ajustementPWM(25);
	_delay_ms(2000);
	ajustementPWM(50);
	_delay_ms(2000);
	ajustementPWM(75);
	_delay_ms(2000);
	ajustementPWM(100);
	return 0;
}

/**
 * Fichier : probleme2.cpp
 * Auteur : Bourque Bédard Christophe & Mohamed Saddik
 * Date : 01 Mars 2018
 *
 * Le programme permet d'implementer le comportement decrit 
 * en utilisant une photoresistance externe.
 *
 * 
 * Branchements
 * 
 * LED						PORTB, broches 1 et 2		<--->		Del libre
 * Photoresistance (in)		Vcc/GND (p. ex. PORTA)		<--->		(voir enonce TP)
 * Photoresistance (out)	(voir enonce TP)			<--->		PORTA, broches 1 et 2
 */

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "can.h"

// Definition des constantes
const uint8_t SORTIE = 0xff;
const uint8_t ENTREE = 0X00;
const uint8_t ETEINT = 0x00;
const uint8_t ROUGE = 0x02;
const uint8_t VERT = 0x01;
const uint8_t DELAI_AMBRE = 10;
const uint8_t PINA_CAN = 1; // broche 2
const uint16_t THRESHOLD_BASSE = 0x166; // ~35%
const uint16_t THRESHOLD_FORTE = 0x366; // ~85%

/**
 * Fonction pour l'initialisation.
 */
void initialisation(void)
{
	// de-activation des interruptions
	cli();

	// configuration des ports
	DDRB = SORTIE; // Port B en mode sortie
	DDRA = ENTREE; // Port A en mode entrée

	// re-activation des interruptions
	sei();
}

/**
 * Fonction pour faire la couleur ambre.
 */
void couleurAmbre() {
	PORTB = ROUGE;
	_delay_ms(DELAI_AMBRE);
	PORTB = VERT;
	_delay_ms(DELAI_AMBRE);
}

/**
 * Fonction principale.
 */
int main()
{
	initialisation();
	can canWrapper;
	
	for (;;)
	{
		// lecture
		uint16_t valLecture = canWrapper.lecture(PINA_CAN);

		// condition pour lumiere
		if (valLecture < THRESHOLD_BASSE)
		{
			// basse
			PORTB = VERT;
		}
		else if (valLecture > THRESHOLD_FORTE)
		{
			// forte
			PORTB = ROUGE;
		}
		else
		{
			// bon niveau
			couleurAmbre();
		}
	}

	return 0;
}

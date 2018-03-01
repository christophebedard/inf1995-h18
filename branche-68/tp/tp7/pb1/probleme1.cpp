/**
 * Fichier : probleme1.cpp
 * Auteur : Bourque Bédard Christophe & Mohamed Saddik
 * Date : 01 Mars 2018
 *
 * Le programme permet d'implementer le comportement decrit 
 * en utilisant un bouton externe.
 *
 * 
 * Branchements
 * 
 * LED				PORTB, broches 1 et 2		<--->		Del libre
 * Bouton (in)		Vcc/GND (p. ex. PORTA)		<--->		(voir enonce TP)
 * Bouton (out)		(voir enonce TP)			<--->		PORTC, broches 1 et 2
 */

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Definition des constantes
const uint8_t PINC_BOUTON = 0X02;
const uint8_t SORTIE = 0xff;
const uint8_t ENTREE = 0X00;
const uint8_t ETEINT = 0x00;
const uint8_t ROUGE = 0x02;
const uint8_t VERT = 0x01;
const uint8_t LIMITE_COMPTEUR_DIX = 120;

/**
 * Fonction pour l'initialisation.
 */
void initialisation(void)
{
	// de-activation des interruptions
	cli();

	// configuration des ports
	DDRB = SORTIE; // Port B en mode sortie
	DDRC = ENTREE; // Port C en mode entrée

	// re-activation des interruptions
	sei();
}

/**
 * Fonction pour abstraire le polling et l'inversion du bouton.
 * 
 * \return etat du bouton
 */
bool isBoutonOn()
{
	// inversion pour compenser l'inversion de la logique du bouton
	return !(PINC & PINC_BOUTON);
}

/**
 * Fonction qui implemente le comportement demande.
 */
void behave()
{
	// attendre que le bouton soit enfonce
	while (!isBoutonOn());

	// incrementer le compteur
	uint8_t compteurDix = 0;
	while (isBoutonOn() && (compteurDix < LIMITE_COMPTEUR_DIX))
	{
		compteurDix++;
		_delay_ms(100);
	}

	// lumiere clignote vert pendant 1/2 seconde
	PORTB = VERT;
	_delay_ms(500);
	PORTB = ETEINT;

	// attente deux secondes
	_delay_ms(2000);

	// lumiere clignote rouge (compteur/2) fois @ 2 fois/seconde
	uint8_t nombreClignotements = compteurDix / 2;
	for (uint8_t i = 0; i < nombreClignotements; ++i)
	{
		// allume+eteint = 500 ms = 2 Hz
		PORTB = ROUGE;
		_delay_ms(250);
		PORTB = ETEINT;
		_delay_ms(250);
	}

	// lumiere verte pendant une seconde
	PORTB = VERT;
	_delay_ms(1000);
	PORTB = ETEINT;
}

/**
 * Fonction principale.
 */
int main()
{
	initialisation();
	
	for (;;)
	{
		behave();
	}

	return 0;
}

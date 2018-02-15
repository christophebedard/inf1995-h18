/* Fichier : probleme2.cpp
* Auteur : Bourque Bédard Christophe  & Mohamed Saddik
* Date : 01 février 2018
*
* Le programme permet de faire varier les couleurs de la LED 
* en fonction de la pression et du relachement du bouton poussoir.
*/



#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Definition des constantes
const uint8_t PIND_BOUTON = 0X04;
const uint8_t SORTIE = 0xff;
const uint8_t ENTREE = 0X00;
const uint8_t ETEINT = 0x00;
const uint8_t ROUGE = 0x02;
const uint8_t VERT = 0x01;
const uint8_t DELAI_1 = 10;



volatile uint8_t minuterieExpiree=0;
volatile uint8_t boutonPoussoir=0; 


/********************************************************************
* Cette fonction de de l'initialisation 
*********************************************************************/
void initialisation ( void ) {
	// de-activation des interruptions
	cli ();

	// configuration des ports
	DDRB = SORTIE; // Port B en mode sortie.
	DDRD = SORTIE; // Port D en mode entrée.
	
/*
	// interruption externe sur INT0
	EIMSK |= (1 << INT0) ;

	// interruption lors d'un rising ou falling edge
	EICRA |= (1 << ISC00) | (1 << ISC01);
*/
	// re-activation des interruptions
	sei ();
}

/********************************************************************
* L'initialisation du PWM dans le timer1 
*********************************************************************/
void initPWM () {
	// division d'horloge par 8 - implique une frequence de PWM fixe
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 <<WGM10);
	TCCR1B |= (1 << CS11); // division par 8
	TCCR1C = 0;
}

/********************************************************************
* L'ajustement du PWM dans le timer1 
*********************************************************************/
void ajustementPWM ( int ratio  ) {
	// mise à un des sorties OC1A et OC1B sur comparaison
	// réussie en mode PWM 8 bits, phase correcte
	// et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6
	// page 177 +++++++++++++++++++++
	OCR1B = ratio * 255 / 100  ;
}

/*******************************************************************************
* La fonction principale. 
*******************************************************************************/
int main() {
	initialisation ();
	initPWM();
	
	ajustementPWM (0);
	_delay_ms(2000);
	ajustementPWM (25);
	_delay_ms(2000);
	ajustementPWM (50);
	_delay_ms(2000);
	ajustementPWM (75);
	_delay_ms(2000);
	ajustementPWM (100);
	return 0;
}

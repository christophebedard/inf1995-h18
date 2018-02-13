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
* Cette fonction de rappel de l'interrruption ISR pour la minuterie
* 
*********************************************************************/
ISR ( TIMER1_COMPA_vect ) {
	minuterieExpiree = 1;
}
/********************************************************************
* Cette fonction de rappel de l'interrruption ISR 
* 
*********************************************************************/
ISR ( INT0_vect) {
	boutonPoussoir = 1;
	// anti-rebond
	// delai pour anti-rebond
	//_delay_ms(30);
}
/********************************************************************
* Fonction pour partir la minuterie
* 
*********************************************************************/
void partirMinuterie ( uint16_t duree ) {
	minuterieExpiree = 0;
	
	// mode CTC du timer 1 avec horloge divisée par 1024
	// interruption après la durée spécifiée
	TCNT1 = 0 ;
	OCR1A = duree*(F_CPU/1024);
	//TCCR1A |= 0 ;
	TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC et clk/1024
	TCCR1C = 0;
	TIMSK1 |= (1 << OCIE1A);
}

/********************************************************************
* Cette fonction de de l'initialisation 
*********************************************************************/
void initialisation ( void ) {
	// de-activation des interruptions
	cli ();

	// configuration des ports
	DDRB = SORTIE; // Port B en mode sortie.
	DDRD = ENTREE; // Port D en mode entrée.
	

	// interruption externe sur INT0
	EIMSK |= (1 << INT0) ;

	// interruption lors d'un rising ou falling edge
	EICRA |= (1 << ISC00) | (1 << ISC01);

	// re-activation des interruptions
	sei ();
}

/*******************************************************************************
* La fonction principale. 
*******************************************************************************/
int main() {
	initialisation();
	
	_delay_ms(10000);
	
	cli();
	PORTB = ROUGE; // LED allume rouge à l'état initial.
	_delay_ms(100);
	PORTB = ETEINT;
	boutonPoussoir = 0;
	sei();
	
	partirMinuterie(1000);
	while ( minuterieExpiree == 0 && boutonPoussoir == 0 );

	// Une interruption s'est produite. Arrêter toute
	// forme d'interruption. Une seule réponse suffit.
	cli ();
	
	// Verifier la réponse
	if( boutonPoussoir == 1 && minuterieExpiree == 0){
		PORTB = VERT;
	}
	else{ 
        PORTB = ROUGE;
	}
	
	return 0;
}

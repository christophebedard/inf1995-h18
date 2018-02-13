/* Fichier : probleme2.cpp
* Auteur : Bourque Bédard Christophe  & Mohamed Saddik
* Date : 08 février 2018
*
* Le programme permet de faire varier les couleurs de la LED 
* en fonction de la pression et du relachement du bouton poussoir
* en utilisant des interruptions.
*/

/* Tableau des états

|Etats Present |Bouton|Etats Suivant | LED         |
|--------------|------|--------------|-------------|
|Einit         |   0  |Einit         |rouge        |
|Einit         |   1  |E1            |rouge        |
|E1            |   1  |E1            |ambre        |
|E1            |   0  |E2            |ambre        |
|E2            |   0  |E2            |verte        |
|E2            |   1  |E3            |verte        |
|E3            |   1  |E3            |rouge        |
|E3            |   0  |E3            |rouge        |
|E4            |   0  |E4            |-            |
|E4            |   1  |E5            |-            |
|E5            |   1  |E5            |verte        |
|E5            |   0  |Einit         |verte        |

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

// Definition des etats 
enum Etats { Einit, E1, E2, E3,E4,E5};

// Variable d'etat
volatile Etats etat = Einit;

/********************************************************************
* Cette fonction de rappel de l'interrruption  ISR 
* 
*
*********************************************************************/
ISR ( INT0_vect ) {
	// delai pour anti-rebond
	_delay_ms(30);

	// se souvenir ici si le bouton est pressé ou relâché
	bool boutonPese = PIND & PIND_BOUTON;
	
	// changements d'etats
	switch (etat)
	{
	case Einit:
		if (boutonPese)
			etat = E1;
		break;
	case E1:
		if (!boutonPese)
			etat = E2;
		break;
	case E2:
		if (boutonPese)
			etat = E3;
		break;
	case E3:
		if (!boutonPese)
			etat = E4;
		break;
	case E4:
		if (boutonPese)
			etat = E5;
		break;
	case E5:
		if (!boutonPese)
			etat = Einit;
		break;
	}
	
	// clear le flag
	EIFR |= (1 << INTF0);
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
	PORTB = ROUGE; // LED allume rouge à l'état initial.

	// interruption externe sur INT0
	EIMSK |= (1 << INT0) ;

	// interruption lors d'un rising ou falling edge
	EICRA |= (1 << ISC00) ;

	// re-activation des interruptions
	sei ();
}

/*********************************************************************************
* Creation de la couleur Ambre.
**********************************************************************************/
void couleurAmbre() {
	PORTB = ROUGE;
	_delay_ms(DELAI_1);
	PORTB = VERT;
	_delay_ms(DELAI_1);
}

/*******************************************************************************
* Cette fonction permet d'implenter la machine a etat decrite dans le tableau
* des etats ci-dessus.
*******************************************************************************/
void implementer()
{
	switch (etat)
	{
	case Einit: 
		PORTB = ROUGE; // LED allume rouge à l'état initial.
		break;
	case E1: 
		couleurAmbre();
		break;
	case E2:  
		PORTB = VERT;
		break;
	case E3:  
		PORTB = ROUGE;
		break;
	case E4:   
		PORTB = ETEINT;
		break;
	case E5:   
		PORTB = VERT;
		break;
	}
}

/*******************************************************************************
* La fonction principale. 
*******************************************************************************/
int main()
{
    initialisation();
	for (;;) // boucle sans fin
	{
     implementer();
	}

	return 0;
}

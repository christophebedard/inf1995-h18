/* Fichier : probleme1.cpp
* Auteur : Bourque Bédard Christophe  & Mohamed Saddik
* Date : 01 Mars 2018
*
* Le programme permet de faire varier les couleurs de la LED 
* en fonction de la pression et du relachement du bouton poussoir
* en utilisant des interruptions.
*/

/* Tableau des états

|Etats Present |Bouton| compteur |Minitrie|Etats Suivant |   sortie    |
|--------------|------|--------- |--------|--------------|-------------|
|Einit         |   0  |          |		  |Einit         |             |
|Einit         |   1  |          |  	  |E1            |        	   |
|E1            |   0  |          |		  |E2            |     		   | compteur incremente 10 fois/s
|E1            |      |    >120  |		  |E2            |     		   | compteur incremente 10 fois/s
|E2            |      | 		 |1/2 sec |E3            |verte        | clignote 1/2 s
|E3            |      | 		 |	2 sec |E4            | 			   |
|E4            |      | 		 |		  |E5            |clignoteRouge| clignote selon compteur
|E5            |      | 		 | 1 sec  |Einit         |verte        | vert pendant 1 s

*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Definition des constantes
const uint8_t PIND_BOUTON = 0X02;//à vérifier 
const uint8_t SORTIE = 0xff;
const uint8_t ENTREE = 0X00;
const uint8_t ETEINT = 0x00;
const uint8_t ROUGE =  0x02;
const uint8_t VERT =   0x01;
const uint8_t LIMITE_COMPTEUR_DIX = 120; // 120 dec to hex

// Definition des etats 
enum Etats { Einit, E1, E2, E3, E4, E5 };

// Variable d'etat
volatile Etats etat = Einit;

// Autres variables
volatile uint8_t compteurDix = 0x00;
volatile uint8_t nombreClignotements = 0x00;
volatile uint8_t compteurClignotements = 0x00;
volatile bool etatBouton = false;

void partirMinuterie(uint16_t);

/********************************************************************
* Fonction de rappel de l'interrruption ISR pour la minuterie
*********************************************************************/
ISR ( TIMER1_COMPA_vect ) {
	PORTB = ROUGE; //test
	
	/*
	switch (etat)
	{
	case Einit:
	case E1:
	case E2:
	case E3:
		// incrementer le compteur
		PORTB = ETEINT;
		compteurDix++;
		// repartir la minuterie
		partirMinuterie(100);
		break;
	case E4:
		compteurClignotements++;
		if (compteurClignotements < nombreClignotements) {
			// continue de clignoter
			PORTB = ROUGE; //?
			partirMinuterie(500);
		} else {
			// prochain etat
			etat = E5;
		}
		break;
	case E5:
		break;
	}
	*/
}

/********************************************************************
* Fonction pour partir la minuterie
* 
* \param duree : duree en ms
*********************************************************************/
void partirMinuterie ( uint16_t duree) {
	// mode CTC du timer 1 avec horloge divisée par 1024
	// interruption après la durée spécifiée
	TCNT1 = 0;
	OCR1A = duree*(F_CPU/1024);
	//TCCR1A |= (1 << COM1A1) | (1 << COM1A0); //?
	TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC et clk/1024
	TCCR1C = 0;
	TIMSK1 |= (1 << OCIE1A);
}

/********************************************************************
* Fonction pour l'initialisation 
*********************************************************************/
void initialisation ( void ) {
	// de-activation des interruptions
	cli ();

	// configuration des ports
	DDRB = SORTIE; // Port B en mode sortie.
	DDRD = SORTIE;
	DDRC = ENTREE; // Port C en mode entrée.

	// re-activation des interruptions
	sei ();
}

/**********************************************************************
* Fonction qui permet d'implenter la machine a etat decrite dans 
* le tableau des etats ci-dessus.
***********************************************************************/
void implementer()
{
	switch (etat)
	{
	case Einit: 
		// pas de sortie
		compteurDix = 0;
		compteurClignotements = 0;
		break;
	case E1: 
		//if (!(PINC & PIND_BOUTON) || compteurDix >= LIMITE_COMPTEUR_DIX)
		if (compteurDix >= LIMITE_COMPTEUR_DIX)
			etat = E2;
		break;
	case E2:  
		PORTB = VERT;
		_delay_ms(500);
		PORTB = ETEINT;
		etat = E3;
		break;
	case E3: 
		_delay_ms(2000);
		
		// test
		/**/
		if (compteurDix == 0) {
			PORTB = ROUGE;
			_delay_ms(100);
			PORTB = ETEINT;
		}
		/**/
		nombreClignotements = compteurDix / 2;
		partirMinuterie(500);
		
		etat = E4;
		break;
	case E4:   
		// initialisation du compteur dans E3
		break;
	case E5:   
		PORTB = VERT;
		_delay_ms(1000);
		PORTB = ETEINT;
		etat = Einit;
		break;
	}
}

void updateBouton() {
		// se souvenir ici si le bouton est pressé ou relâché
		bool newEtat = !(PINC & PIND_BOUTON);
		
		if (newEtat != etatBouton) {
			etatBouton = newEtat;
		}
		
		// changements d'etats
		switch (etat)
		{
		case Einit:
			if (etatBouton) {
				partirMinuterie(100);
				etat = E1;
			}
			break;
		case E1:
			// premiere condition de changement d'etat (bouton)
			if (!etatBouton)
				etat = E2;
			break;
		default:
			break;
		}
 }

/***********************************************************************
* Fonction principale. 
************************************************************************/
int main()
{
    initialisation();
    
    partirMinuterie(500);
    
    /*
	for (;;) // boucle sans fin
	{
		updateBouton();
		
		implementer();
	}
	*/

	return 0;
}

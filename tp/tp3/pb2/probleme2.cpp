/* Fichier : probleme2.cpp
* Auteur : Bourque Bédard Christophe  & Mohamed Saddik
* Date : 01 février 2018
*
* Le programme permet de faire varier les couleurs de la LED 
* en fonction de la pression et du relachement du bouton poussoir.
*/
/* Tableau des états

|Etats Present |Bouton|Etats Suivant | LED         |
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

// Definition des variables 
Etats etat = Einit;

/********************************************************************
* Cette fonction permet de verifier si le bouton poussoir est presse
* 
* \return: etat du bouton.  
*********************************************************************/

bool lecture() {
	bool etat_ = false;

	if (PIND & PIND_BOUTON) {
		_delay_ms(DELAI_1);
		if (PIND & PIND_BOUTON) {
			etat_ = true;
		}
	}

	return etat_;
}

/*********************************************************************************
Initialisation des registres.
**********************************************************************************/

void setup()
{
	DDRB = SORTIE; // Port B en mode sortie.
	DDRD = ENTREE; // Port D en mode entrée.
	PORTB = ROUGE; // LED allume rouge à l'état initial.
}
/*********************************************************************************
Creation de la couleur Ambre.
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
void implementer() {

	switch (etat)
	{
	case Einit: 
		PORTB = ROUGE; // LED allume rouge à l'état initial.
		if (lecture())
			etat = E1;
		break;
	case E1: 
		couleurAmbre();
		if (!lecture())
			etat = E2;
		break;
	case E2:  
		PORTB = VERT;
		if (lecture())
			etat = E3;
		break;
	case E3:  
		PORTB = ROUGE;
		if (!lecture())
			etat = E4;
		break;
	case E4:   
		PORTB = ETEINT;
		if (lecture())
			etat = E5;
		break;
	case E5:   
		PORTB = VERT;
		if (!lecture())
			etat = Einit;
		break;
	}

}
/*******************************************************************************
* La fonction principale. 
*******************************************************************************/
int main()
{
	setup();
	for (;;) // boucle sans fin
	{
     implementer();
	}


	return 0;
}


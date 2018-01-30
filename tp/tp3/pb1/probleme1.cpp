/* Fichier : probleme1.cpp
* Auteur : Bourque Bédard Christophe  & Mohamed Saddik
* Date : 01 février 2018
*
* Le programme permet d'allumer la DEL suite à la pression cinq fois
* de suite du bouton poussoir
*/

/*  Tableau des états

|Etats Present  |Bouton|Etats Suivant | LED         |
|Einit          |   1  |E1            |eteint       |
|E1             |   1  |E2            |eteint       |
|E2             |   1  |E3            |eteint       |
|E3             |   1  |E4            |eteint       |
|E4             |   1  |E5            |rouge        |
|E5             |   0  |Einit         |eteint       |
|               |      |              |             |

*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

// Definition des constantes
const uint8_t PIND_BOUTON = 0X04;
const uint8_t SORTIE = 0xff;
const uint8_t ENTREE = 0X00;
const uint8_t ETEINT = 0x00;
const uint8_t ROUGE  = 0x02;
const uint8_t DELAI_1 = 10;





// Definition des etats 
enum Etats { Einit, E1, E2, E3, E4, E5 };

// Definition des variables 
Etats etat = Einit;

/********************************************************************
* Cette fonction permet de verifier si le bouton poussoir est presse 
*********************************************************************/

bool lecture(){
	bool etat = false;
	
	if ( PIND & PIND_BOUTON){
		_delay_ms(DELAI_1);
		if ( PIND & PIND_BOUTON){
			while (PIND & PIND_BOUTON)
			etat = true;
		}
	} 
	
	return etat;
}



/*********************************************************************************
Initialisation des registres
**********************************************************************************/

void setup()
{
	DDRB = SORTIE; // Port B en mode sortie
	DDRD = ENTREE; // Port D en mode entrée

}



/*******************************************************************************
* Cette fonction permet d'implenter la machine a etat decrite dans le tableau
* des etats ci-dessus.
*******************************************************************************/
void implementer() {

	switch (etat)
	{
	case Einit: PORTB = ETEINT;
		       if (lecture())
		      	  etat = E1;
		       break;
	case E1:  PORTB = ETEINT;
		      if (lecture())
			      etat = E2;
		      break;
	case E2:  PORTB = ETEINT;
		      if (lecture())
			     etat = E3;
		      break;
   case E3:  PORTB = ETEINT;
		     if (lecture())
			    etat = E4;
		     break;
   case E4:  PORTB = ETEINT;
		     if (lecture())
			    etat = E5;
		     break;
  case E5:   PORTB = ROUGE;
		    _delay_ms(1000);
		     PORTB = ETEINT;
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


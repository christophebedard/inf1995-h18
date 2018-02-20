/* Fichier : probleme1.cpp
* Auteur : Bourque Bédard Christophe  & Mohamed Saddik
* Date : 15 février 2018
*
* TP6 PB1
*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include "memoire_24.h"

// Definition des constantes
const uint8_t SORTIE = 0xff;
const uint8_t ENTREE = 0X00;
const uint8_t ROUGE = 0x02;
const uint8_t VERT = 0x01;
const uint16_t ADRESSE = 0x00;

/*******************************************************************************
* Fonction d'initialisation. 
*******************************************************************************/
void initialisation ( void ) {
	DDRB = SORTIE; // Port B en mode sortie.
}

/*******************************************************************************
* Fonction principale. 
*******************************************************************************/
int main() {
	initialisation ();
	
	Memoire24CXXX mem;
	
	uint8_t tableau[] = "*E*C*O*L*E* *P*O*L*Y*T*E*C*H*N*I*Q*U*E*";
	uint8_t tailleTableau = strlen((char*)tableau);
	
	mem.ecriture(ADRESSE,tableau,tailleTableau);
	
	_delay_ms(5);
	
	uint8_t tableauLecture[tailleTableau];
	mem.lecture(ADRESSE,tableauLecture,tailleTableau);
	
	// validation de la lecture/ecriture
	bool isResultatValide= true;
	for (int i =0; i<tailleTableau; ++i){
		if (tableau[i]!=tableauLecture[i])
			isResultatValide = false;
	}
	
	// affichage du resultat de la validation
	if(isResultatValide)
		PORTB= VERT;
	else
		PORTB= ROUGE;
	
	return 0;
}

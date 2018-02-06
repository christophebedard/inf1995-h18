/* INF1995 - TP4
 * Fichier : probleme1.cpp
 * Auteur : Bourque Bédard Christophe  & Mohamed Saddik
 * Date : 06 février 2018
 */

#define F_CPU 8000000
#define F_B 1000.0
#include <avr/io.h>
#include <util/delay.h>

// Definition des constantes
const uint8_t SORTIE = 0xff;
const uint8_t ETEINT = 0x00;
const uint8_t ROUGE = 0x02;
const uint8_t DELAI_1 = 1;

double rapport;

/*********************************************************************************
* Initialisation des registres.
**********************************************************************************/
void setup()
{
	DDRB = SORTIE; // Port B en mode sortie.
}

/**
 * Delai en microsecondes
 * 
 * \param us : nombre de microsecondes
 */
void waitForUs(uint16_t us)
{
	while (us > 0) {
		_delay_us(DELAI_1);
		us--;
	}
}

/*******************************************************************************
* La fonction principale. 
*******************************************************************************/
int main()
{
	setup();
	double attenuation = 1.0/(3.0 * F_B);
	
	for (;;) // boucle sans fin
	{
		rapport = 1.0;
		
		// attenuation
		while (rapport > 0.0) {
			PORTB = ROUGE;
	
			uint16_t tempsA = (uint16_t)(rapport * 1000000.0 / F_B);
			waitForUs(tempsA);
			
			PORTB = ETEINT;
			
			uint16_t tempsB = (uint16_t)((1.0-rapport) * 1000000.0 / F_B);
			waitForUs(tempsB);;
			
			rapport -= attenuation;
		}
	}

	return 0;
}

/* INF1995 - TP4
 * Fichier : probleme2.cpp
 * Auteur : Bourque Bédard Christophe  & Mohamed Saddik
 * Date : 06 février 2018
 */

#define F_CPU 8000000
#define F_PWM_1 60.0
#define F_PWM_2 400.0
#include <avr/io.h>
#include <util/delay.h>

// Definition des constantes
const uint8_t SORTIE = 0xff;
const uint8_t ETEINT = 0x00;
const uint8_t ROUGE = 0x02;
const uint8_t DELAI_1 = 1;

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

/**
 * Fait tourner la roue
 * 
 * \param rapport : rapport PWM
 * \param sec     : temps total
 * \param freqPWM : frequence PWM
 */
void turn(double rapport, double sec, double freqPWM)
{
	double periodePWM = 1.0/freqPWM; // longueur d'une periode de PWM [s]
	
	while (sec > 0.0) {
		PORTB = ROUGE;
		
		uint16_t tempsA = (uint16_t)(rapport * 1000000.0 / freqPWM);
		waitForUs(tempsA);
		
		PORTB = ETEINT;
		
		uint16_t tempsB = (uint16_t)((1.0-rapport) * 1000000.0 / freqPWM);
		waitForUs(tempsB);;
		
		sec -= periodePWM;
	}
}

/*******************************************************************************
* La fonction principale. 
*******************************************************************************/
int main()
{
	setup();
	
	turn(0.00, 2.0, F_PWM_1);
	turn(0.25, 2.0, F_PWM_1);
	turn(0.50, 2.0, F_PWM_1);
	turn(0.75, 2.0, F_PWM_1);
	turn(1.00, 2.0, F_PWM_1);
	
	turn(0.00, 2.0, F_PWM_2);
	turn(0.25, 2.0, F_PWM_2);
	turn(0.50, 2.0, F_PWM_2);
	turn(0.75, 2.0, F_PWM_2);
	turn(1.00, 2.0, F_PWM_2);
	
	return 0;
}

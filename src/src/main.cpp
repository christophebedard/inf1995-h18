/**
 * Fichier : main.cpp
 * Auteur : equipe 68116
 * Date : 06 Mars 2018
 *
 * Test de la librairie
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "interruption.h"
#include "minuterie.h"

/**
 * Callback pour INT0
 */
void callbackBouton()
{
    PORTB = VERT;
}

/**
 * Callback pour TIMER1
 */
void callbackMinuterie()
{
	PORTB = ROUGE;
}

/**
 * Fonction principale.
 */
int main(void)
{
    DDRB = SORTIE;

	initInterruption(&callbackBouton);

	initMinuterie(&callbackMinuterie);
	startMinuterie(2000);
	
	for (;;)
	{
		
	}

	return 0;
}

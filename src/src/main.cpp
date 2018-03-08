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

/**
 * Callback pour INT0
 */
void int0Callback()
{
    PORTB = ROUGE;
}

/**
 * Fonction principale.
 */
int main(void)
{
    DDRB = SORTIE;

	initInterruption(&int0Callback);
	
	for (;;)
	{
		//PORTB = VERT;
	}

	return 0;
}

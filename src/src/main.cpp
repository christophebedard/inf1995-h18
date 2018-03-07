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

#include "defines.h"
#include "interruption.h"

/**
 * Callback pour INT0
 */
ISR(INT0_vect)
{
    PORTB = ROUGE;
}

/**
 * Fonction principale.
 */
int main(void)
{
    DDRB = SORTIE;

	initInterruption();
	
	for (;;)
	{

	}

	return 0;
}

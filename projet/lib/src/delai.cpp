/**
 * \file delai.cpp
 * \brief implementation des fonctions de delai
 * \author Christophe Bourque Bedard
 * \author Simon Moreau
 * \author Fares Ouaissa
 * \author Mohamed Saddik
 */

#include "delai.h"


void waitForUs(uint16_t us)
{
	while (us > 0) {
		_delay_us(1);
		us--;
	}
}

void waitForMs(uint16_t ms)
{
	while (ms > 0) {
		_delay_ms(1);
		ms--;
	}
}

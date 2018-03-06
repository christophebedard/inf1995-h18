#ifndef LIB_MINUTERIE_H
#define LIB_MINUTERIE_H

#include <avr/io.h>
#include <avr/interrupt.h>

void Minuterie(const uint16_t duree);

void SetUpMinuterie();

#endif // LIB_MINUTERIE_H

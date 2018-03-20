#ifndef LIB_DEFINES_H
#define LIB_DEFINES_H

#ifndef F_CPU
#define F_CPU 8000000
#endif

// pointeur vers fonction sans argument et retour void
typedef void (*func_t)();

// Definition des constantes
const uint8_t SORTIE = 0xff;
const uint8_t ENTREE = 0X00;
const uint8_t ETEINT = 0x00;
const uint8_t ROUGE = 0x02;
const uint8_t VERT = 0x01;

#endif // LIB_DEFINES_H

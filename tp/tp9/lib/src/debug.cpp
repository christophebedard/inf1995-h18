/**
 * \file debug.cpp
 * \brief implementation de la classe Debug
 * \author 
 */

#include "debug.h"


/**
 * Inversion string
 * https://www.geeksforgeeks.org/implement-itoa/
 * 
 * \param num : le nombre
 * \param str : le pointeur vers le tableau de sortie
 * \param base : la base du nombre
 */
void reverse(char* str, uint8_t len)
{
    uint8_t debut = 0;
    uint8_t fin = len - 1;

    while (debut < fin)
    {
        char tmp = *(str + debut);
        str[debut] = *(str + fin);
        str[fin] = tmp;

        debut++;
        fin--;
    }
}

/**
 * Conversion entier a string
 * https://www.geeksforgeeks.org/implement-itoa/
 * 
 * \param num : le nombre
 * \param str : le pointeur vers le tableau de sortie
 * \param base : la base du nombre
 */
void itoa(uint8_t num, char* str, const uint8_t& base)
{
    uint8_t i = 0;
    bool isNegative = false;
 
    // cas special pour 0
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }
 
    // support des nombres negatifs seulement pour la base 10
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }
 
    // chiffres
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    // si nombre est negatif
    if (isNegative)
    {
        str[i++] = '-';
    }

    // si hex, ajouter 0x
    if (base == 16)
    {
        str[i++] = 'x';
        str[i++] = '0';
    }

    str[i] = '\0'; // fin du string
 
    // inversion du string
    reverse(str, i);
}

void Debug::out(const uint8_t& nombre)
{
    out(nombre, 10);
}

void Debug::out(const uint8_t& nombre, const uint8_t& base)
{
    char str[16] = {0};
    itoa(nombre, str, base);
    UART::transmission(str);
}

void Debug::out(const char* str)
{
    UART::transmission(str);
}

/**
 * \file test_debug_uart.cpp
 * \brief programme pour tester le debug via UART
 * \author 
 */

#include "debug.h"

int main()
{
    Debug::init();

    char str1[] = "un test ";
    char str2[] = "de newline \n";
    uint8_t buf[1] = {94};

    while(true)
    {
        Debug::out((uint8_t)0x62, 16);
        Debug::out(", ");
        Debug::out((uint8_t)44);
        Debug::out(", ");
        Debug::out(str1);
        Debug::out(str2);
        Debug::out(buf[0]);
        Debug::out("\n");
    }

    return 0;
}

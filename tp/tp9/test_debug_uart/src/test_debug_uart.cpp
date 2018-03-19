#include "debug.h"

int main()
{
    UART::init();

    char str1[] = "un test ";
    char str2[] = "de newline \n";

    while(true)
    {
        Debug::out(0x62, 16);
        Debug::out(", ");
        Debug::out(44);
        Debug::out(", ");
        Debug::out(str1);
        Debug::out(str2);
    }

    return 0;
}

#include "debug.h"

int main()
{
    UART::init();

    char str1[] = "un test ";
    char str2[] = "de newline \n";
    uint8_t buf[1] = {94};

    while(true)
    {
        Debug::out(0x62, 16);
        Debug::out(", ");
        Debug::out(44);
        Debug::out(", ");
        Debug::out(str1);
        Debug::out(str2);
        Debug::out(buf[0]);
        Debug::out("\n");
    }

    return 0;
}

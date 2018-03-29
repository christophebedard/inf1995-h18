#include "defines.h"
#include "enums_structs.h"
#include <avr/io.h>
#include <avr/interrupt.h>

class info
{
public:
    static void transmission();
    static void receiveInterrupt();
    static void interrupt();
private:
    uint8_t couleur;
    interrupteur etat;
}

#include "defines.h"
#include "enums_structs.h"
#include <avr/io.h>
#include <avr/interrupt.h>

class info
{
public:
    static void transmission(int id);
    static void receiveInterrupt();
    static void interrupt();
    Interrupteur getEtat();
private:
    uint8_t couleur;
    Interrupteur etat;
}

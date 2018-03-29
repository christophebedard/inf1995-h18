#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"
#include "enums_structs.h"
#include "delai.h"
#include "uart.h"
#include "moteurs.h"

class info
{
public:
    void transmission(int id);
    void receiveInterrupt();
    void interrupt();
    Interrupteur getEtat();
private:
    uint8_t couleur;
    Interrupteur etat;
};

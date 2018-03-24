/**
 * \file test_buzzer.cpp
 * \brief programme pour tester le buzzer
 * \author 
 */

#include "delai.h"
#include "buzzer.h"
#include "debug.h"


int main()
{
    UART::init(); // pour debug

    Buzzer::init();

    Debug::out("debut\n");

    Debug::out("45\n");
    Buzzer::play((uint16_t)45);
    
    waitForMs(1000);

    Debug::out("60\n");
    Buzzer::play((uint16_t)60);
    
    waitForMs(1000);
    
    Debug::out("70\n");
    Buzzer::play((uint16_t)70);
    
    waitForMs(1000);
    
    Debug::out("80\n");
    Buzzer::play((uint16_t)80);
    
    waitForMs(1000);

    Debug::out("stop\n");
    Buzzer::stop();

    while(true);

    return 0;
}

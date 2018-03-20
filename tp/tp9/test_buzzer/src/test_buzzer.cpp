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

    Buzzer::play(45);
    Debug::out("45\n");
    waitForMs(1000);
    Buzzer::play(60);
    Debug::out("60\n");
    waitForMs(1000);
    Buzzer::play(70);
    Debug::out("70\n");
    waitForMs(1000);
    Buzzer::play(80);
    Debug::out("80\n");
    waitForMs(1000);

    Buzzer::stop();
    Debug::out("stop\n");

    while(true);

    return 0;
}

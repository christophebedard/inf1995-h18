/**
 * \file test_buzzer.cpp
 * \brief programme pour tester le buzzer
 * \author 
 */

#include "delai.h"
#include "buzzer.h"


int main()
{
    Buzzer::init();

    Buzzer::play(45);
    waitForMs(1000);
    Buzzer::play(60);
    waitForMs(1000);
    Buzzer::play(70);
    waitForMs(1000);
    Buzzer::play(80);
    waitForMs(1000);
    Buzzer::stop();

    while(true);

    return 0;
}

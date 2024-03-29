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
    Debug::init();
    Buzzer::init();

    Debug::out("debut\n");

    Debug::out("12\n");
    Buzzer::play(12);
    
    waitForMs(1000);

    Debug::out("40\n");
    Buzzer::play(40);
    
    waitForMs(1000);
    
    Debug::out("80\n");
    Buzzer::play(80);
    
    waitForMs(1000);

    Debug::out("0\n");
    Buzzer::play(0);

    waitForMs(1000);
    
    Debug::out("100\n");
    Buzzer::play(100);
    
    waitForMs(1000);

    Debug::out("127\n");
    Buzzer::play(127);
    
    waitForMs(1000);

    Debug::out("stop\n");
    Buzzer::stop();

    waitForMs(2000);

    for(uint8_t i = 12; i < 128; i += 10)
    {
        Debug::out(i);
        Debug::out("\n");
        Buzzer::play(i);
        
        waitForMs(1000);

        Buzzer::stop();

        waitForMs(1000);
    }

    Buzzer::stop();

    Debug::out("enum Prescaler :\n");
    Debug::out(static_cast<uint16_t>(Prescaler::Div_1));
    Debug::out("\n");
    Debug::out(static_cast<uint16_t>(Prescaler::Div_8));
    Debug::out("\n");
    Debug::out(static_cast<uint16_t>(Prescaler::Div_32));
    Debug::out("\n");
    Debug::out(static_cast<uint16_t>(Prescaler::Div_64));
    Debug::out("\n");
    Debug::out(static_cast<uint16_t>(Prescaler::Div_128));
    Debug::out("\n");
    Debug::out(static_cast<uint16_t>(Prescaler::Div_256));
    Debug::out("\n");
    Debug::out(static_cast<uint16_t>(Prescaler::Div_1024));
    Debug::out("\n");

    while(true);

    return 0;
}

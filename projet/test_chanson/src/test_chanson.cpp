/**
 * \file test_buzzer.cpp
 * \brief programme pour tester le buzzer
 * \author 
 */

#include "chanson.h"
#include "debug.h"
#include "delai.h"


int main()
{
    Debug::init(); // pour debug
    Chanson::init();

    Debug::out("play\n");
    Chanson::play();

    waitForMs(5000);
    
    Debug::out("stop?\n");
    Chanson::stop();

    waitForMs(1000);

    Debug::out("play\n");
    Chanson::play();

    waitForMs(5000);

    Debug::out("stop?\n");
    Chanson::stop();

    while(true)
    {
        //Debug::out();
    }

    return 0;
}

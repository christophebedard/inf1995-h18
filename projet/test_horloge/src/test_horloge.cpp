/**
 * \file test_horloge.cpp
 * \brief programme pour tester Horloge
 * \author 
 */

#include "horloge.h"
#include "delai.h"
#include "debug.h"

int main()
{
    Debug::init();
    Horloge::init();

    DDRA |= BROCHES_LED;

    Time ref = Horloge::getTime();
    Debug::out(ref);

    Time delta = Time(5, 1, 0);
    Debug::out(delta);

    while(true)
    {
        if (Horloge::isEcoule(ref, delta))
        {
            PORTA ^= 0x1;
            ref = Horloge::getTime();
        }

        //Horloge::debug();
    }

    return 0;
}

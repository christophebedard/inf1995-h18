/**
 * \file test_time.cpp
 * \brief programme pour tester Time
 * \author 
 */

#include "time.h"
#include "delai.h"

int main()
{
    Debug::init();
    Time::init();

    DDRA |= BROCHES_LED;

    tm_t interval = Time::tm(0, 6, 0, 0);
    tm_t debut = Time::getTime();

    while(true)
    {
        //if (Time::isEcoule(debut, interval))
        //{
        //    PORTA |= 0x1;
        //}
        Time::debug();

        waitForMs(1000);
    }

    return 0;
}

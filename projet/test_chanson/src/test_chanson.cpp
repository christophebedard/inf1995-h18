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

    Debug::out("enum NoteMusicale :\n");
    Debug::out(static_cast<uint8_t>(NoteMusicale::Carree));
    Debug::out("\n");
    Debug::out(static_cast<uint8_t>(NoteMusicale::Ronde));
    Debug::out("\n");
    Debug::out(static_cast<uint8_t>(NoteMusicale::Blanche));
    Debug::out("\n");
    Debug::out(static_cast<uint8_t>(NoteMusicale::Noire));
    Debug::out("\n");
    Debug::out(static_cast<uint8_t>(NoteMusicale::Croche));
    Debug::out("\n");
    Debug::out(static_cast<uint8_t>(NoteMusicale::DoubleCroche));
    Debug::out("\n");
    Debug::out(static_cast<uint8_t>(NoteMusicale::TripleCroche));
    Debug::out("\n");
    Debug::out(static_cast<uint8_t>(NoteMusicale::QuadrupleCroche));
    Debug::out("\n");


    while(true);

    return 0;
}

/**
 * \file test_lecteur_chanson.cpp
 * \brief programme pour tester le lecteur de chanson
 * \author 
 */

#include "lecteur_chanson.h"
#include "debug.h"
#include "delai.h"


int main()
{
    Debug::init();
    LecteurChanson::init();

    Debug::out("play\n");
    LecteurChanson::setChanson(Chansons::chansonTeletubbies);
    LecteurChanson::play();

    while(LecteurChanson::isPlaying());
    Debug::out("chanson finie\n");

    waitForMs(1000);

    Debug::out("play\n");
    LecteurChanson::setChanson(Chansons::chansonMario);
    LecteurChanson::play();

    while(LecteurChanson::isPlaying());
    Debug::out("chanson finie\n");

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

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
    LecteurChanson::setChanson(Chansons::starWarsMarcheImperiale);
    LecteurChanson::play();

    while(LecteurChanson::isPlaying());
    Debug::out("chanson finie\n");

    waitForMs(1000);

    Debug::out("play\n");
    LecteurChanson::setChanson(Chansons::mario);
    LecteurChanson::play();

    while(LecteurChanson::isPlaying());
    Debug::out("chanson finie\n");

    Debug::out("enum FigureDeNote :\n");
    Debug::out(static_cast<uint8_t>(FigureDeNote::Carree));
    Debug::out("\n");
    Debug::out(static_cast<uint8_t>(FigureDeNote::Ronde));
    Debug::out("\n");
    Debug::out(static_cast<uint8_t>(FigureDeNote::Blanche));
    Debug::out("\n");
    Debug::out(static_cast<uint8_t>(FigureDeNote::Noire));
    Debug::out("\n");
    Debug::out(static_cast<uint8_t>(FigureDeNote::Croche));
    Debug::out("\n");
    Debug::out(static_cast<uint8_t>(FigureDeNote::DoubleCroche));
    Debug::out("\n");
    Debug::out(static_cast<uint8_t>(FigureDeNote::TripleCroche));
    Debug::out("\n");
    Debug::out(static_cast<uint8_t>(FigureDeNote::QuadrupleCroche));
    Debug::out("\n");


    while(true);

    return 0;
}

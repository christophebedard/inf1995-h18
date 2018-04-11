/**
 * \file test_controle_moteurs.cpp
 * \brief programme pour tester le controle des moteurs
 * \author 
 */

#include "delai.h"
#include "debug.h"
#include "controle_moteurs.h"
#include "capteurs_distance.h"

#define DELAI_MS 2000

int main()
{
    Debug::init();
    ControleMoteurs::init();
    CapteursDistance::init();

    Debug::out("debut\n");

    // Debug::out("l:80, a:0\n");
    // ControleMoteurs::setVitesses(80, DirectionMoteur::Avant,
    //                              0, DirectionMoteur::Avant);

    // waitForMs(DELAI_MS);

    // Debug::out("l:-50, a:0\n");
    // ControleMoteurs::setVitesses(50, DirectionMoteur::Arriere,
    //                              0, DirectionMoteur::Avant);

    // waitForMs(DELAI_MS);

    // Debug::out("l:80, a:40\n");
    // ControleMoteurs::setVitesses(80, DirectionMoteur::Avant,
    //                              40, DirectionMoteur::Avant);

    // waitForMs(DELAI_MS);

    // Debug::out("l:80, a:-40\n");
    // ControleMoteurs::setVitesses(80, DirectionMoteur::Avant,
    //                              40, DirectionMoteur::Arriere);

    // waitForMs(DELAI_MS);

    // Debug::out("l:0, a:50\n");
    // ControleMoteurs::setVitesses(0, DirectionMoteur::Avant,
    //                              50, DirectionMoteur::Avant);

    // waitForMs(DELAI_MS);

    // Debug::out("l:0, a:-50\n");
    // ControleMoteurs::setVitesses(0, DirectionMoteur::Avant,
    //                              50, DirectionMoteur::Arriere);

    // waitForMs(DELAI_MS);

    // Debug::out("fin\n");
    // ControleMoteurs::setVitesses(0, DirectionMoteur::Avant,
    //                              0, DirectionMoteur::Avant);

    while(true)
    {
        ControleMoteurs::updateSuiviMur(Murs::Gauche,
                                        30,
                                        0,
                                        10);

        // delai
        waitForMs(10);
    }

    return 0;
}

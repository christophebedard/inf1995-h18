/**
 * \file test_controle_moteurs.cpp
 * \brief programme pour tester le controle des moteurs
 * \author 
 */

#include "delai.h"
#include "debug.h"
#include "controle_moteurs.h"
#include "diagnostic.h"
#include "buzzer.h"

#define DELAI_MS 2000

int main()
{
    Debug::init();
    Buzzer::init();
    ControleMoteurs::init();
    CapteursDistance::init();

    //Diagnostic::init(true);
    // Debug::out("debut\n");

    //Debug::out("l:80, a:0\n");
    //ControleMoteurs::setVitesses(35, DirectionMoteur::Avant,
      //                         20, DirectionMoteur::Avant);
    //waitForMs(DELAI_MS);
    Buzzer::play(50);
    ControleMoteurs::setVitesses(35, DirectionMoteur::Avant, 0, DirectionMoteur::Arriere);
//     waitForMs(2000);
//     Buzzer::play(70);
//     ControleMoteurs::setVitesses(35, DirectionMoteur::Avant, CHANGEMENT_VITESSE_ANG, DirectionMoteur::Arriere);
//     waitForMs(CHANGEMENT_ATTENTE*2);
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
    //                               50, DirectionMoteur::Avant);
    // waitForMs(DELAI_MS);
    // Debug::out("l:0, a:-50\n");
    // ControleMoteurs::setVitesses(0, DirectionMoteur::Avant,
    //                              50, DirectionMoteur::Arriere);
    // waitForMs(DELAI_MS);
    // Debug::out("fin\n");
    // ControleMoteurs::setVitesses(0, DirectionMoteur::Avant,
    //                              0, DirectionMoteur::Avant);

    // ControleMoteurs::doDemiTour(CoteMur::Gauche);
    // waitForMs(DELAI_MS);
    // ControleMoteurs::doDemiTour(CoteMur::Droit);
    // waitForMs(DELAI_MS);

    /*while(true)
    {
        //Diagnostic::update();
        
        ControleMoteurs::updateSuiviMur(CoteMur::Droit,
                                        SUIVI_MUR_DISTANCE,
                                        SUIVI_MUR_VIT_LIN,
                                        SUIVI_MUR_TOL);

        // delai
        //waitForMs(10);
    }
*/
    return 0;
}

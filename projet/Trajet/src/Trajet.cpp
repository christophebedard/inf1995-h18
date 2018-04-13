#include "trajet.h"
#include "timer0.h"

int main()
{
    
   
    /*
     * Test de controle des virages
    ControleMoteurs::setVitesses(0,DirectionMoteur::Avant, CHANGEMENT_VITESSE_ANG, DirectionMoteur::Avant);
    waitForMs(CHANGEMENT_ATTENTE);
    ControleMoteurs::setVitesses(50, DirectionMoteur::Avant, 0, DirectionMoteur::Arriere);
    waitForMs(500);
    ControleMoteurs::setVitesses(0,DirectionMoteur::Avant, CHANGEMENT_VITESSE_ANG, DirectionMoteur::Arriere);
    waitForMs(CHANGEMENT_ATTENTE_RETOUR);
    ControleMoteurs::setVitesses(0, DirectionMoteur::Avant, 0, DirectionMoteur::Arriere);
    */
    
    //Suivi besoin deux capteurs
    /*ControleMoteurs::updateSuiviMur(CoteMur::Droit, SUIVI_MUR_DISTANCE, 40, SUIVI_MUR_TOL);
    */
    //Test Poteau (Doit faire fonctionner les callback pour tester
    Trajet::execute();
   
    return 0;
}


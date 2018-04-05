/**
 * \file test_switch_programme.cpp
 * \brief programme pour tester le switch entre deux programmes
 * \author 
 */

#include "delai.h"
#include "debug.h"
#include "memoire_24.h"

#define ADRESSE_ETAT_PROGRAMME 0x0

int main()
{
    Debug::init();

    // initialisation du lecteur de memoire
    Memoire24CXXX mem;

    // lecture du bit d'etatPrecedent
    uint8_t etatPrecedent = 2;
    mem.lecture(ADRESSE_ETAT_PROGRAMME, &etatPrecedent);

    // update du nouvel etat
    uint8_t etatNouveau = (etatPrecedent == 0) ? 0x1 : 0x0;
    // ecriture du nouvel etat
    mem.ecriture(ADRESSE_ETAT_PROGRAMME, etatNouveau);

    // affichage de l'etat par debug
    switch(etatNouveau)
    {
        case 0:
            Debug::out("diagnostic\n");
            //Diagnostic::execute();
            break;
        case 1:
            Debug::out("trajet\n");
            //Trajet::execute();
            break;
        default:
            Debug::out("erreur\n");
            break;
    }

    while(true);

    return 0;
}

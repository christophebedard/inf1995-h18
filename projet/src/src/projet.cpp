/**
 * \file projet.cpp
 * \brief point d'entree du projet
 * \author Christophe Bourque Bedard
 * \author Simon Moreau
 * \author Fares Ouaissa
 * \author Mohamed Saddik
 */

#include "defines.h"
#include "delai.h"
#include "debug.h"
#include "memoire_24.h"
#include "diagnostic.h"
#include "trajet.h"
#include "lecteur_wav.h"
#include "data_tinkywinky.h"


int main()
{
    // sequence initiale : lecture fichier wav
    LecteurWav::init();
    LecteurWav::setWav(tinkywinky_data, tinkywinky_longueur);
    LecteurWav::play();

    // ========== execution du programme ========== 

    // initialisation du lecteur de memoire
    Memoire24CXXX mem;

    // lecture du bit d'etatPrecedent
    uint8_t etatPrecedent = 2;
    mem.lecture(ADRESSE_ETAT_PROGRAMME, &etatPrecedent);

    // update et ecriture du nouvel etat
    uint8_t etatNouveau = (etatPrecedent == 0) ? 0x1 : 0x0;
    mem.ecriture(ADRESSE_ETAT_PROGRAMME, etatNouveau);

    // execution du programme correspondant
    switch(etatNouveau)
    {
        case 0:
            Diagnostic::execute();
            break;
        case 1:
            Trajet::execute();
            break;
        default:
            PORTA = ROUGE;
            break;
    }
    
    return 0;
}

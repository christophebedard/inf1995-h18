/**
 * \file bouton.cpp
 * \brief implementation de la classe Bouton
 * \author 
 */

#include "bouton.h"

volatile EtatBouton Bouton::etat_ = EtatBouton::Relache;
bool Bouton::utiliseInterruption_ = false;

void callbackInterruptionBouton()
{
    // inverse l'etat
    Bouton::etat_ = (Bouton::etat_ == EtatBouton::Enfonce)
                    ? EtatBouton::Relache : EtatBouton::Enfonce;
}

void Bouton::init(bool utiliseInterruption)
{
    utiliseInterruption_ = utiliseInterruption;

    if (utiliseInterruption_)
    {
        Interruption::initInt0(&callbackInterruptionBouton,
                               TypesTriggerInterrupt::RisingOrFallingEdge);
    }
}

EtatBouton Bouton::getEtat()
{
    if (utiliseInterruption_)
    {
        return etat_;
    }
    else
    {
        return (PIND & _BV(_BROCHE_TO_PIN(BROCHE_BOUTON))
                ? EtatBouton::Enfonce : EtatBouton::Relache);
    }
}

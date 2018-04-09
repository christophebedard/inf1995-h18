/**
 * \file diagnostic.cpp
 * \brief implementation de la classe Diagnostic
 * \author 
 */

#include "diagnostic.h"


void callbackRx()
{
    // reception de l'instruction
    uint8_t msg = UART::reception();
    uint8_t donnee = UART::reception();

    // selon le message
    switch (msg)
    {
        case (uint8_t)MessagesLogicielRobot::RequeteEnvoiInfos:
            Diagnostic::transmettreInfos();
            break;
        case (uint8_t)MessagesLogicielRobot::CouleurDel:
            // valeur assignee au port A
            PORTA &= ~(0x3);
            PORTA |= donnee;
            break;
        case (uint8_t)MessagesLogicielRobot::VitesseRoueDroite:
            if ((donnee >> 7) == 1)
            { 
                donnee = ~donnee + 0x01;
                Moteurs::setDirectionMoteurDroit(DirectionMoteur::Arriere);            
            }
            else
            {
                Moteurs::setDirectionMoteurDroit(DirectionMoteur::Avant);
            }
            Moteurs::setPourcentageDroite(donnee);
            break;
        case (uint8_t)MessagesLogicielRobot::VitesseRoueGauche:
            if ((donnee >> 7) == 1)
            { 
                donnee = ~donnee + 0x01;
                Moteurs::setDirectionMoteurGauche(DirectionMoteur::Arriere); 
            }
            else
            {
                Moteurs::setDirectionMoteurGauche(DirectionMoteur::Avant);
            }
            Moteurs::setPourcentageGauche(donnee);
            break;
    }
}

void Diagnostic::init()
{
    // LED (en sortie)
    DDRA |= 0x3;

    UART::init();
    UART::setRxCallback(&callbackRx);

    initInterruption(diagnosticInterrupt, RisingOrFallingEdge);
    Moteurs::init();
    CapteursDistance::init();

    // commencer par transmettre infos du robot
    transmettreInfos();
}

void Diagnostic::execute()
{
    // init
    init();

    // envoyer les informations sur les capteurs en continu
    while(true)
    {
        // etat du bouton
        transmissionMessage(MessagesRobotLogiciel::EtatBoutonInterrupt,
                            (PIND & 0x04) ? 0x0 : 0x1);
        
        // distance capteur gauche
        transmissionMessage(MessagesRobotLogiciel::DistanceCapteurGauche,
                            CapteursDistance::getDistanceDroit());
        
        // distance capteur droit
        transmissionMessage(MessagesRobotLogiciel::DistanceCapteurDroit,
                            CapteursDistance::getDistanceGauche());
    }
}

void Diagnostic::transmissionMessage(MessagesRobotLogiciel msg, uint8_t donnee)
{
    transmissionMessage((uint8_t)msg, donnee);
}

void Diagnostic::transmissionMessage(MessagesRobotLogiciel msg, const char* donnees, const uint8_t longueur)
{
    UART::transmission((uint8_t)msg);
    for (uint8_t i = 0; i < longueur; i++){
        UART::transmission(donnees[i]);
    }
}

void Diagnostic::transmissionMessage(uint8_t type, uint8_t donnee)
{
    UART::transmission(type);
    UART::transmission(donnee);
}

void Diagnostic::transmettreInfos()
{
        // nom du robot
        transmissionMessage(MessagesRobotLogiciel::NomRobot,
                            INFO_NOM_ROBOT,
                            LONGUEUR_INFO_NOM_ROBOT);
        
        // equipe
        transmissionMessage(MessagesRobotLogiciel::NumeroEquipe,
                            INFO_EQUIPE,
                            LONGUEUR_INFO_EQUIPE);

        // groupe
        transmissionMessage(MessagesRobotLogiciel::NumeroSection,
                            INFO_GROUPE); // prend une valeur decimale

        // session
        transmissionMessage(MessagesRobotLogiciel::Session,
                            INFO_SESSION,
                            LONGUEUR_INFO_SESSION);

        // couleur robot
        transmissionMessage(MessagesRobotLogiciel::CouleurBaseRobot,
                            (NUMERO_ROBOT == 1) ? COULEUR_ROBOT1 : COULEUR_ROBOT2);
}

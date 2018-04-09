/**
 * \file diagnostic.cpp
 * \brief implementation de la classe Diagnostic
 * \author 
 */

#include "diagnostic.h"

uint8_t Diagnostic::bouton = 0x00;


void callbackRx()
{
    cli();
    
    // pour LED
    DDRA = SORTIE;

    // reception de l'instruction
    uint8_t instruction[2] = {0x00, 0x00};
    for (uint8_t i = 0; i < 2; i++)
    {
        instruction[i] = UART::reception();
        waitForMs(5);
    }

    // selon le message
    switch (instruction[0])
    {
        case (uint8_t)MessagesLogicielRobot::RequeteEnvoiInfos:
            // Changer parametre a 0 si on utilise le robot vert, 1 pour gris
            Diagnostic::transmettreInfos(1);
            break;
        case (uint8_t)MessagesLogicielRobot::CouleurDel:
            // Valeur assignee au port A
            PORTA = instruction[1];
            break;
        case (uint8_t)MessagesLogicielRobot::VitesseRoueDroite:
            if ((instruction[1] >> 7) == 1)
            { 
                instruction[1] = ~instruction[1] + 0x01;
                Moteurs::setDirectionMoteurDroit(DirectionMoteur::Arriere);            
            }
            else
            {
                Moteurs::setDirectionMoteurDroit(DirectionMoteur::Avant);
            }
            Moteurs::setPourcentageDroite(instruction[1]);
            break;
        case (uint8_t)MessagesLogicielRobot::VitesseRoueGauche:
            if ((instruction[1] >> 7) == 1)
            { 
                instruction[1] = ~instruction[1] + 0x01;
                Moteurs::setDirectionMoteurGauche(DirectionMoteur::Arriere); 
            }
            else
            {
                Moteurs::setDirectionMoteurGauche(DirectionMoteur::Avant);
            }
            Moteurs::setPourcentageGauche(instruction[1]);
            break;
    }

    sei();
}

void Diagnostic::init()
{
    UART::init();
    UART::setRxCallback(&callbackRx);

    initInterruption(diagnosticInterrupt, RisingOrFallingEdge);
    Moteurs::init();
    CapteursDistance::init();

    // commencer par transmettre infos du robot
    transmettreInfos(1);
}

void Diagnostic::execute()
{
    // init
    init();

    // envoyer les informations sur les capteurs en continu
    while(true)
    {
        // etat du bouton
        uint8_t etatBouton = (PIND & 0x04) ? 0x0 : 0x1;
        transmissionMessage(MessagesRobotLogiciel::EtatBoutonInterrupt,
                            etatBouton);
        
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
    waitForMs(5);
    for (uint8_t i = 0; i < longueur; i++){
        UART::transmission(donnees[i]);
        waitForMs(5);
    }
}

void Diagnostic::transmissionMessage(uint8_t type, uint8_t donnee)
{
    UART::transmission(type);
    waitForMs(5);
    UART::transmission(donnee);
    waitForMs(5);
}

void Diagnostic::transmettreInfos(int id)
{
        // nom du robot
        transmissionMessage(MessagesRobotLogiciel::NomRobot,
                            INFO_NOM_ROBOT,
                            12);
        
        // equipe
        transmissionMessage(MessagesRobotLogiciel::NumeroEquipe,
                            INFO_EQUIPE,
                            5);

        // groupe
        transmissionMessage(MessagesRobotLogiciel::NumeroSection,
                            INFO_GROUPE); // prend une valeur decimale

        // session
        transmissionMessage(MessagesRobotLogiciel::Session,
                            INFO_SESSION,
                            4);

        // couleur robot
        if (id == 1)
        {
            transmissionMessage(MessagesRobotLogiciel::CouleurBaseRobot,
                                COULEUR_ROBOT1);
        }
        else if (id == 0)
        {
            transmissionMessage(MessagesRobotLogiciel::CouleurBaseRobot,
                                COULEUR_ROBOT2);
        }
}

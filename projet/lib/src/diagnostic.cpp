/**
 * \file diagnostic.cpp
 * \brief implementation de la classe Diagnostic
 * \author Simon Moreau
 * \author Mohamed Saddik
 * \author Fares Ouaissa
 * \author Christophe Bourque Bedard
 */

#include "diagnostic.h"


bool Diagnostic::modeDebug_ = false;


void callbackRx()
{
    if (!Diagnostic::modeDebug_)
    {
        // reception de l'instruction
        uint8_t msg = UART::reception();
        uint8_t donnee = UART::reception();

        /// \todo garder le message en memoire et le traiter dans la prochaine boucle?
        // selon le message
        switch (msg)
        {
            case (uint8_t)MessagesLogicielRobot::RequeteEnvoiInfos:
                Diagnostic::transmettreInfos();
                break;
            case (uint8_t)MessagesLogicielRobot::CouleurDel:
                // valeur assignee au port A
                PORTA &= ~(BROCHES_LED);
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
}

void Diagnostic::init(bool modeDebug)
{
    // mode de fonctionnement
    // (si true, les moteurs, les capteurs la LED sont desactives)
    modeDebug_ = modeDebug;

    // LED (en sortie)
    DDRA |= BROCHES_LED;

    UART::init();
    UART::setRxCallback(&callbackRx);
    Bouton::init();

    if (!modeDebug_)
    {
        Moteurs::init();
        CapteursDistance::init();

        // commencer par transmettre infos du robot
        transmettreInfos();
    }
}

void Diagnostic::update()
{
    // envoyer les informations sur les capteurs

    // etat du bouton
    transmissionMessage(MessagesRobotLogiciel::EtatBoutonInterrupt,
                        (uint8_t)Bouton::getEtat());
    
    // distance capteur gauche
    uint8_t distGauche = 0;
    CapteursDistance::getDistanceGauche(&distGauche);
    //CapteursDistance::formatDistance(&distGauche);
    transmissionMessage(MessagesRobotLogiciel::DistanceCapteurGauche,
                        distGauche);
    
    // distance capteur droit
    uint8_t distDroit = 0;
    CapteursDistance::getDistanceDroit(&distDroit);
    //CapteursDistance::formatDistance(&distDroit);
    transmissionMessage(MessagesRobotLogiciel::DistanceCapteurDroit,
                        distDroit);
}

void Diagnostic::execute()
{
    init();

    while(true)
    {
        update();
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
                        (NUMERO_ROBOT == 0) ? COULEUR_ROBOT1 : COULEUR_ROBOT2);
}

/**
 * \file trajet.cpp
 * \brief implementation de la classe Diagnostic
 * \author 
 */

#include "trajet.h"




void callbackRx() {
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

void Diagnostic::init() {
    UART::init();
    UART::setRxCallback(&callbackRx);

    initInterruption(diagnosticInterrupt, RisingOrFallingEdge);
    Moteurs::init();
    CapteursDistance::init();

    // commencer par transmettre infos du robot
    transmettreInfos(1);
}

void Diagnostic::execute() {
    // init
    init();

    // envoyer les informations sur les capteurs en continu
    while(true)
    {
        // etat du bouton
        // semble considerer que l'interrupteur est utilise sans qu'il soit appuye, aucun changement lorsqu'appuye
        uint8_t etatBouton = (PIND & 0x04) ? 0x0 : 0x1;
        transmissionMessage((uint8_t)MessagesRobotLogiciel::EtatBoutonInterrupt,
                            etatBouton);
        
        // distance capteur gauche
        transmissionMessage((uint8_t)MessagesRobotLogiciel::DistanceCapteurGauche,
                            CapteursDistance::getDistanceDroit());
        
        // distance capteur droit
        transmissionMessage((uint8_t)MessagesRobotLogiciel::DistanceCapteurDroit,
                            CapteursDistance::getDistanceGauche());
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
        uint8_t instruction = 0xf0;
        UART::transmission(instruction); //Nom
        waitForMs(5);
        for (uint8_t i = 0; i < 12; i++){
            UART::transmission(INFO_NOM_ROBOT[i]);
            waitForMs(5);
        }
        UART::transmission(++instruction); //Equipe
        waitForMs(5);
        for (uint8_t i = 0; i < 5; i++){
            UART::transmission(INFO_EQUIPE[i]);
            waitForMs(5);
        }
        UART::transmission(++instruction); //Groupe
        waitForMs(5);
        //UART::transmission(0x03); // ==> "031" 
        //UART::transmission('3');  // ==> "051"  dec 3
        //UART::transmission(0x03); // ==> "031 
        //UART::transmission('9');  // ==> "057" 57 is dec of char 9
        UART::transmission(INFO_GROUPE);  // ==> prend une valeur decimale"
        waitForMs(5);
        UART::transmission(++instruction); //Session
        waitForMs(5);
        for (uint8_t i = 0; i < 4; i++){
            UART::transmission(INFO_SESSION[i]);
            waitForMs(5);
        }
        UART::transmission(++instruction); //Couleur
        waitForMs(5);
        if (id == 1)
            UART::transmission(COULEUR_ROBOT1);
        else if (id == 0)
            UART::transmission(COULEUR_ROBOT2);
        waitForMs(5);
}

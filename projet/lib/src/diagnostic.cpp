/**
 * \file diagnostic.cpp
 * \brief implementation de la classe Diagnostic
 * \author 
 */

#include "diagnostic.h"

uint8_t Diagnostic::bouton = 0x00;
uint8_t Diagnostic::instruction = 0xf5;


void callbackRx() {
    cli();
    DDRA = SORTIE;
    DDRD = SORTIE;
    uint8_t instruction[2] = {0x00, 0x00};
    for (int i = 0; i < 2; i++){
        instruction[i] = UART::reception();
        waitForMs(5);
    }
    switch (instruction[0]){
        case 0xfb:
            Diagnostic::transmettre(1); 
            //Changer parametre à 0 si on utilise le robot vert, 1 pour gris
            break;
            
        case 0xfa:
            PORTA = instruction[1];
            //Valeur assignée au port A
            break;
            
        case 0xf9://droite
            if (instruction[1] >> 7 == 1){ 
                instruction[1] = ~instruction[1] + 0x01;
                Moteurs::setDirectionMoteurDroit(DirectionMoteur::Arriere);            
            }
            else
                Moteurs::setDirectionMoteurDroit(DirectionMoteur::Avant);
            Moteurs::setPourcentageDroite(instruction[1]);
            break;
    
        case 0xf8://gauche
            if (instruction[1] >> 7 == 1){ 
                instruction[1] = ~instruction[1] + 0x01;
                Moteurs::setDirectionMoteurGauche(DirectionMoteur::Arriere); 
            }
            else
                Moteurs::setDirectionMoteurGauche(DirectionMoteur::Avant);
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

    transmettre(1);
}

void Diagnostic::execute() {
    // init
    init();

    // loop
    while(true)
    {
        UART::transmission(instruction);
        waitForMs(5);
        //etat interrupt
        if (getEtat() == Enfonce)
            UART::transmission(bouton); //semble considerer que l'interrupteur est utilise sans qu'il soit appuye, aucun changement lorsqu'appuye
        else
            UART::transmission(bouton + 1); 
        waitForMs(5);
        UART::transmission(instruction + 1);
        waitForMs(5);
        //distance gauche
        UART::transmission(CapteursDistance::getDistanceDroit());
        waitForMs(5);
        UART::transmission(instruction + 2);
        waitForMs(5);
        //distance droite
        UART::transmission(CapteursDistance::getDistanceGauche());
        waitForMs(5);
    }
}

void Diagnostic::transmettre(int id)
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

#include "info.h"
#include "uart.h"
/*
 * Transmet les informations d'identification du robot 
 * \param id:  l'identificateur du robot, 0 pour le robot 2 et 1 pour le robot 1 
 */
static void info::transmission(int id)
{
        UART::transmit(0xf0); //Nom
        waitForMs(5);
        for (uint8_t i = 0; i < 12; i++){
            UART::transmit(INFO_NOM_ROBOT[i]);
            waitForMs(5);
        }
        UART::transmit(0xf1); //Equipe
        waitForMs(5);
        for (uint8_t i = 0; i < 5; i++){
            UART::transmit(INFO_EQUIPE[i]);
            waitForMs(5);
        }
        UART::transmit(0xf2); //Groupe
        waitForMs(5);
        for (uint8_t i = 0; i < 2; i++){
            UART::transmit(INFO_GROUPE[i]);
            waitForMs(5);
        }
        UART::transmit(0xf3); //Session
        waitForMs(5);
        for (uint8_t i = 0; i < 4; i++){
            UART::transmit(INFO_SESSION[i]);
            waitForMs(5);
        }
        UART::transmit(0xf4); //Couleur
        waitForMs(5);
        if (id == 1)
            couleur = COULEUR_ROBOT1;
        else if (id == 0)
            couleur = COULEUR_ROBOT2;
        UART::transmit(couleur);
}

/*
 * Change l'etat de l'interrupteur pour 
 */
void info::receiveInterrupt()
{
    switch etat:{
        case Enfonce:
            etat = Relache;
        break;
        
        case Relache:
            etat = Enfonce;
        break;
        
        default:
        break;
    }
}
    
void info::interrupt()
{
    cli();
    DDRA = SORTIE;
    DDRD = SORTIE;
    for (int i = 0; i < 2; i++){
        uint8_t instruction[i] = UART::reception();
        waitForMs(5);
    }
    switch instruction[0]:{
        case 0xfb:
            Info::transmission(1); 
            //Changer parametre à 0 si on utilise le robot vert, 1 pour gris
            break;
            
        case 0xfa:
            PORTA = instruction[1];
            //Valeur assignée au port A
            break;
            
        case 0xf9://droite
            if (instruction[1] >> 7 == 1){ 
                instruction[1] = ~instruction[1] + 0x01;
                Moteurs::setDirectionMoteurDroit(DirectionMoteur::arriere);            
            }
            else
                Moteurs::setDirectionMoteurDroit(DirectionMoteur::avant);
            Moteurs::setPourcentageDroite(instruction[1]);
            break;
    
        case 0xf8://gauche
            if (instruction[1] >> 7 == 1){ 
                instruction[1] = ~instruction[1] + 0x01;
                Moteurs::setDirectionMoteurGauche(DirectionMoteur::arriere); 
            }
            else
                Moteurs::setDirectionMoteurGauche(DirectionMoteur::avant);
            Moteurs::setPourcentageGauche(instruction[1]);
            break;
    }
    sei();
}

Interrupteur info::getEtat()
{
    return etat;
}

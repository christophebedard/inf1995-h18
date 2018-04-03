/**
 * \file debug.cpp
 * \brief implementation de la classe UART
 * \author 
 */

#include "uart.h"
#include "delai.h"
#include "moteurs.h"
#include "defines.h"
#include "enums_structs.h"

ISR(__vector_USART_RXC)
{
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
            UART::transmettre(1); 
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
    
void UART::init()
{
	init(2400);
}

void UART::init(uint16_t rate)
{
	// selon le baud rate specifie
	// attention : >2400 semble causer trop d'erreurs de transmission
	UBRR0H = ((F_CPU / (16 * rate)) - 1) >> 8;
	UBRR0L = ((F_CPU / (16 * rate)) - 1);

	// reception et transmission
	UCSR0A = 0;
	UCSR0B |= _BV(RXEN0) | _BV(TXEN0) | _BV(RXCIE0);

	// format des trames : 8 bits
	// (asynchronous, 1 stop bit, none parity)
	UCSR0C |= _BV(UCSZ01) | _BV(UCSZ00);
}

/*
 * Transmet les informations d'identification du robot 
 * \param id:  l'identificateur du robot, 0 pour le robot 2 et 1 pour le robot 1 
 */
void UART::transmettre(int id)
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


void UART::transmission(const uint8_t& donnee)
{
	while(!(UCSR0A & _BV(UDRE0)));
	UDR0 = donnee;
}

void UART::transmission(const char* str)
{
	// transmission des caracteres un par un
	while (*str != '\0')
	{
		transmission((uint8_t)*str);
		++str;
	}
}

uint8_t UART::reception()
{
    while(!(UCSR0A & _BV(RXC0)));
    return UDR0;
}

void UART::stop()
{
	UBRR0H = 0;
	UBRR0L = 0;
	UCSR0A = 0;
	UCSR0B &= ~(_BV(RXEN0) | _BV(TXEN0));
	UCSR0C &= ~(_BV(UCSZ01) | _BV(UCSZ00));
}

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t nMinuterie = 0; 
const uint16_t DUREE = 0x30D;
void Initialisation(); 
void Minuterie(const uint16_t duree);
void fMinuterie();

int main (){
    const uint8_t eteint = 0x00;                          //Initialisation des variables qui identifient l'affichage de la DEL libre par couleur
	const uint8_t vert = 0x01;                    
	const uint8_t rouge = 0x02;
    Initialisation();
    for(;;){
        PORTA = eteint;
        do{
        }while ((nMinuterie < 120 && !(PIND & 0x04))  || nMinuterie == 0);    //Tant que l'interrupteur est presse et que la minuterie ne s'est pas faite 120 fois ou que la minuterie n'est pas lancee
        fMinuterie();                                                         //On ferme la minuterie
        PORTA = vert;
        _delay_ms(500);
        PORTA = eteint;
        _delay_ms(2000);
        for (uint8_t i = 0; i < ((nMinuterie + 1)/2); i++){                                
            PORTA = rouge;
            _delay_ms(250);
            PORTA = eteint;
            _delay_ms(250);
            PORTA = rouge;
            _delay_ms(250);
            PORTA = eteint;
            _delay_ms(250);
        }
        nMinuterie = 0;
        PORTA = vert;
        _delay_ms(1000);
        }
    
    return 0;    
}

ISR(INT0_vect){
_delay_ms(30);
if (!(PIND & 0x04)){                                             //Si l'interrupteur est presse, on lance la minuterie
    Minuterie(DUREE);
}
EIFR |= (1 << INTF0);    
}

ISR(TIMER1_COMPA_vect){
    nMinuterie++;
}



void Minuterie(const uint16_t duree){

    TCNT1 =  0;
    
    OCR1A = duree;

    TCCR1A |= (1 << COM1A1) | (1 << COM1A0) ;                    //Set OCA on Compare Match(Output High Level)

    TCCR1B |= (1 << WGM12)  | (1 << CS12) | (1 << CS10) ;        //comparaison avec top a OCR1A, clock/1024

    TIMSK1 |=  (1 << OCIE1A);                                    
}

void fMinuterie(){                                               //Met fin a la minuterie en replacant des 0 dans les registres
    OCR1A = 0;
    TCCR1A = 0;  
    TCCR1B = 0;
    TIMSK1 = 0;
    
}
void Initialisation(){
    cli();
    DDRA = 0x03;
    DDRD = 0x00;
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC01);                                       //Configuration de l'interrupt pour detecter falling edge
    sei();
}

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile bool minuterieExpiree = false;
volatile bool interrupteur = false;
void Initialisation();
void Minuterie(const uint16_t duree);

int main(){
    const uint8_t ROUGE = 0x02;
    const uint8_t VERT = 0x01;  
    const uint8_t ETEINT = 0x00;
    const uint16_t DUREE = 0x1E84;
    Initialisation();
    _delay_ms(3000);
    PORTA = ROUGE;
    _delay_ms(100);
    PORTA = ETEINT;
    Minuterie(DUREE); 
    do{
    }while ((interrupteur == false) && (minuterieExpiree == false));
    cli();
    if ((interrupteur == true) && (minuterieExpiree == false))
        PORTA = VERT;
    if ((interrupteur == false) && (minuterieExpiree == true))
        PORTA = ROUGE;
    return 0;
}



ISR(TIMER1_COMPA_vect){
    minuterieExpiree = true;    
}

ISR(INT0_vect){ 
        _delay_ms(30);
        interrupteur = true;
        EIFR |= (1 << INTF0);
}


void Minuterie(const uint16_t duree){
    TCNT1 =  0;
    
    OCR1A = duree;

    TCCR1A |= (1 << COM1A1) | (1 << COM1A0) ;  

    TCCR1B |= (1 << WGM12)  | (1 << CS12) | (1 << CS10) ;

    TIMSK1 |=  (1 << OCIE1A);
    
}

void Initialisation(){
    cli();
    DDRA = 0x03;                                    //On place les deux premier ports de A en sorties
	DDRD = 0x00;                                    //On place tous les ports de D en entrees
    EIMSK |= (1 << INT0);
    EICRA |= (11 << ISC00);                          //Configuration de l'interrupt pour detecter falling et rising edge (pour les push et release)
    
    sei();
}

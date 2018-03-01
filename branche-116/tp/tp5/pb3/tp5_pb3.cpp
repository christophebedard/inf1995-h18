#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void ajustementPWM(const int& pourcentage);
uint8_t incrementation(const int& pourcentage);
int main(){
    DDRD = 0xFF;
    int pourcentage = 0;
    while (pourcentage < 125){
    ajustementPWM(incrementation(pourcentage));
    _delay_ms(2000);
    pourcentage += 25;
    }
    ajustementPWM(0x00);                                        //Arret du moteur
    return 0;
}

uint8_t incrementation(const int& pourcentage) {
    uint8_t top;
    if (pourcentage == 0){
        top = 0x00;
    }
    else if (pourcentage == 25){
        ajustementPWM(0xFF);                                    //Donne une courte impulsion a 100% au moteur pour faciliter le passage de 0 a 25%
        _delay_ms(200);
        top = 0x40;
    }
    else if (pourcentage == 50){
        top = 0x80;
    }
    else if (pourcentage == 75){
        top = 0xC0;
    }
    else if (pourcentage == 100){
        top = 0xFF;
    }
    return top;
}

void ajustementPWM (const int& pourcentage ) {

// mise à un des sorties OC1A et OC1B sur comparaison

// réussie en mode PWM 8 bits, phase correcte

// et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6

// page 177 de la description technique du ATmega324PA)

OCR1A = pourcentage ;

OCR1B = pourcentage ;


// division d'horloge par 8 - implique une frequence de PWM fixe

TCCR1A = (1 << COM1A1) | (1 << COM1B1)| (1 << WGM10);

TCCR1B = (1 << CS11);


}

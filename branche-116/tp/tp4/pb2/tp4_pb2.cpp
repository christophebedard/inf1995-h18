/*
 * Auteurs : Simon Moreau(1902475) & Fares Ouaissa(1824669)
 * Date de remise:  Fevrier 2018
 * Nom du fichier: tp4_pb2.cpp
 * Description: Faire tourner une roue a differentes intensite pendant 20 secondes
 */


#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>



void PWM (int nDelais); 
void Move(int f);


int main(){
    DDRA = 0x03;
    int f = 60;
    Move(f);
    f = 400;
    Move(f);

    return 0;
}

void PWM(int nDelais){
        for (int i = 0; i < nDelais; i++)
            _delay_ms(1); 
}

void Move(int f){
    double a = 0, b, c;
    if (f == 60){
        b = 16.67;
        c = 600;
    }
    if (f == 400){
        b = 2.5;
        c = 4000;
    }
    uint8_t FORWARD = 0x01;
    uint8_t NOT_FORWARD = 0x00;
    for (int i = 0; i <= c; i++){ 
        PORTA = FORWARD;
        PWM(a);
        PORTA = NOT_FORWARD;
        PWM(b);
        if (!(i % 120) && (f == 60)){
            a += 4.17;
            b -= 4.17;
        }
        if (!(i % 800) && (f == 400)){
            a += 0.625;
            b -= 0.625;
        }    
}
}


#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "can.h"

int main(){
    const uint8_t ROUGE = 0x02;
    const uint8_t VERT = 0x01;  
    const uint8_t PIN = 0x02;  //Selection du pin 2 comme position de lecture pour la classe can
    const uint16_t VH = 254;    //Doit etre elevee pour que l'on puisse obtenir l'ambre avec seulement un peu d'ombrage
    const uint16_t VL = 150;    //En cachant bien la photoresistance avec ce seuil on controle bien l'affichage de vert
    uint16_t numerique;         
    DDRA = 0x03;
    //Les deux premieres broches du port A en sortie
    can c;
    for (;;){
        numerique = (0xFF & (c.lecture(PIN) >> 2));    //Convertis la valeur obtenue en lecture en entier non signe 8 bit 
         if(numerique > VH){                          
            PORTA = ROUGE;
         }
        else if(numerique < VL)
         {
            PORTA = VERT;
         }
         else{ 
            PORTA = ROUGE;                     
            _delay_ms(4);              
            PORTA = VERT;               
            _delay_ms(3); 
        }
    }
    return 0;
}






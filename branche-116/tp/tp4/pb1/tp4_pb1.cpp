/*
 * Auteurs : Simon Moreau(1902475) & Fares Ouaissa(1824669)
 * Date de remise: 
 * Nom du fichier: tp4_pb1.cpp
 * Description: Controle des DEL avec signaux PWM
 */


#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>


void PWM (int nDelais); 

int main()
{   int a = 1750;
    DDRA = 0x03;                                         //On place les deux premier ports de A en sorties
    uint8_t ROUGE = 0x02;
    uint8_t VERT = 0x01;
    uint8_t ETEINT = 0x00;                               //Initialisation des variables qui identifient l'affichage de la DEL libre par couleur
    PORTA = ROUGE;
    while (a > 0){
        PORTA = ROUGE;
        PWM(a);
        PORTA = ETEINT;
        PWM(1750 - a);
        a--;
       }
    a = 1750;
    PORTA = VERT;
    while (a > 0){
        PORTA = VERT;
       PWM(a);
        PORTA = ETEINT;
       PWM(1750 - a);
        a--;
       
    }
    PORTA = ETEINT;    
    return 0;

}

void PWM(int nDelais){

    for (int i = 0; i < nDelais; i++)
        _delay_ms(1/1750);
}

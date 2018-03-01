#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
enum State {P0, R0, P1, R1, P2, R2};
       
void Initialisation(); //Prototypage de l'initialisation
//Variables globales
volatile State etat = P0;                                //Variable de type State qui permettra de passer d'un etat a l'autre    
int main(){

   
    const uint8_t eteint = 0x00;                          //Initialisation des variables qui identifient l'affichage de la DEL libre par couleur
	const uint8_t vert = 0x01;                    
	const uint8_t rouge = 0x02;

    Initialisation();
    for(;;){              
        switch (etat) {                             //Machine a etat logicielle 
        
            case P0:{
                PORTA = rouge;                      //La DEL affiche la couleur rouge
            break;}
            case R0:{
                PORTA = rouge;                      //La DEL alterne rapidement entre les lumieres rouge et verte qui donne la couleur ambre
                _delay_ms(6);              
                PORTA = vert;               
                _delay_ms(3);               //La DEL affiche la couleur ambre et verifie que l'interrupteur est relache            
            break;}
            case P1:{
                PORTA = vert;                       //La DEL affiche la couleur verte

            break;}
            case R1:{
                PORTA = rouge;

            break;}
            case P2:{
                PORTA = eteint;

            break;}
            case R2:{
                PORTA = vert;
            break;}
            default :
            break;
        
        }
    }        
    return 0;
}

ISR(INT0_vect){
    
_delay_ms(30);
if (etat == P0){
    etat = R0;
}
else if (etat == R0){
    etat = P1;
}
else if (etat == P1){
    etat = R1;
}
else if (etat == R1){
    etat = P2;
}
else if (etat == P2){
    etat = R2;
}
else if (etat == R2){
    etat = P0;
}
EIFR |= (1 << INTF0);    
}


void Initialisation(){
    cli();
    DDRA = 0x03;                                    //On place les deux premier ports de A en sorties
	DDRD = 0x00;                                    //On place tous les ports de D en entrees
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);                          //Configuration de l'interrupt pour detecter falling et rising edge (pour les push et release)
    sei();
}

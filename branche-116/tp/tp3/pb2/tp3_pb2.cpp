/*
 * Auteurs : Simon Moreau(1902475) & Fares Ouaissa(1824669)
 * Date de remise: 1 Fevrier 2018
 * Nom du fichier: tp3_pb2.cpp
 * Description: Implementation logicielle d'une machine a etat decrivant le comportement demande
 */

// Table d'etat
/*  PRESS  STATE   eteint    rouge    vert   NSTATE
 *    0      P0      0         1       0       P0
 *    1      P0      0         1       0       R0
 *    0      R0      0         1       1       P1      rouge et vert donne ambre
 *    1      R0      0         1       1       R0
 *    0      P1      0         0       1       P1
 *    1      P1      0         0       1       R1
 *    0      R1      0         1       0       P2
 *    1      R1      0         1       0       R1
 *    0      P2      1         0       0       P2
 *    1      P2      1         0       0       R2
 *    0      R2      0         0       1       P0
 *    1      R2      0         0       1       R2 
 */
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

enum State {P0, R0, P1, R1, P2, R2};

void Press(bool& interrupteur);                     //Prototypage des fonctions Press et Ambre 
void Ambre(bool& interrupteur);

int main(){

    
    DDRA = 0x03;                                    //On place les deux premier ports de A en sorties
	DDRD = 0x00;                                    //On place tous les ports de D en entrees
    uint8_t eteint = 0x00;                          //Initialisation des variables qui identifient l'affichage de la DEL libre par couleur
	uint8_t vert = 0x01;                    
	uint8_t rouge = 0x02;
	bool interrupteur = false;                      //Variable booleenne permettant de verifier si le bouton est appuie ou relache
    State etat = P0;                                //Variable de type State qui permettra de passer d'un etat a l'autre
    for(;;){              
        switch (etat) {                             //Machine a etat logicielle 
        
            case P0:{
                PORTA = rouge;                      //La DEL affiche la couleur rouge
                Press(interrupteur);                //On verifie si l'interrupteur est appuie
                if (interrupteur)                   //Passage au prochain etat si l'interrupteur est appuie
                    etat = R0;
            break;}
            case R0:{
                Ambre(interrupteur);                //La DEL affiche la couleur ambre et verifie que l'interrupteur est relache
                if (!interrupteur)                  //Passage au prochain etat si l'interrupteur est relache
                    etat = P1;               
            break;}
            case P1:{
                PORTA = vert;                       //La DEL affiche la couleur verte
                Press(interrupteur);                //On verifie si l'interrupteur est appuie
                if (interrupteur)                   //Passage au prochain etat si l'interrupteur est appuie
                    etat = R1;
            break;}
            case R1:{
                PORTA = rouge;
                Press(interrupteur);
                if (!interrupteur)
                    etat = P2;
            break;}
            case P2:{
                PORTA = eteint;
                Press(interrupteur);
                if (interrupteur)
                    etat = R2;
            break;}
            case R2:{
                PORTA = vert;
                Press(interrupteur);
                if (!interrupteur)
                    etat = P0;
            break;}
            default :
            break;
        
        }
    }        
    return 0;
}
/*
 * Verifie si l'interrupteur est actif ou non
 *@param interrupteur l'addresse de la variable interrupteur  
*/
void Press(bool& interrupteur){  
    if (PIND & 0x04){                               //Verifie si bouton pressoir de la section interupt est appuie
                _delay_ms(10);                      //(Anti-rebond)
                if (PIND & 0x04){                   //S'il est encore appuie apres le delais 
                    interrupteur = true;            //La variable booleenne interrupteur prends la valeur true
                }
    }
    else if (!(PIND & 0x04)){                       //Si le bouton pressoir de la section interupt n'est pas appuie
        interrupteur = false;                       //La variable booleenne interrupteur prends la valeur false
    }
}
/*
 * Permet l'affichage de la couleur ambre sur la DEL libre du robot
 *@param interrupteur l'addresse de la variable interrupteur 
 */
void Ambre(bool& interrupteur){
        uint8_t vert = 0x01;                        //Identification des sorties par couleurs (type: entier non signe de 8 bit)
	    uint8_t rouge = 0x02;
        while (interrupteur){                       //Tant que l'interupteur est appuie
                PORTA = rouge;                      //La DEL alterne rapidement entre les lumieres rouge et verte qui donne la couleur ambre
                _delay_ms(6);              
                PORTA = vert;               
                _delay_ms(3);
                Press(interrupteur);                //Permet de sortir de la boucle lorsque l'interrupteur est relache
                
        }
}

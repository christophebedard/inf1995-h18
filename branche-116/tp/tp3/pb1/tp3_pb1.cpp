/*
 * Auteurs : Simon Moreau(1902475) & Fares Ouaissa(1824669)
 * Date de remise: 1 Fevrier 2018
 * Nom du fichier: tp3_pb1.cpp
 * Description: Implementation logicielle d'une machine a etat decrivant le comportement demande
 */

// Table d'etat
/*  PRESS    RELEASE  STATE   Rouge    NSTATE
 *    0         x       P0      0         P0
 *    1         1       P0      0         P0
 *    1         0       P0      0         P1
 *    0         x       P1      0         P1
 *    1         1       P1      0         P1
 *    1         0       P1      0         P2
 *    0         x       P2      0         P2
 *    1         1       P2      0         P2
 *    1         0       P2      0         P3
 *    0         x       P3      0         P3
 *    1         1       P3      0         P3
 *    1         0       P3      0         P4
 *    0         x       P4      0         P4
 *    1         1       P4      0         P4
 *    1         0       P4      0         DEL
 *    x         x       DEL     1         P0
 */
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

enum State{P0, P1, P2, P3, P4, DEL};

void Press(bool& interrupteur);                     //Prototypage de la fonction Press

int main()
{

DDRA = 0x03;                                        //On place les deux premier ports de A en sorties
DDRD = 0x00;                                        //On place tous les ports de D en entrees
bool interrupteur = false;
bool relache = true;
uint8_t ROUGE = 0x02;                               //Initialisation des variables qui identifient l'affichage de la DEL libre par couleur
State etat = P0;
PORTA = 0x00;                                       //Initialisation de l'affichage de la DEL a l'etat eteint

    for (;;){
        switch (etat){                              //Machine a etat logicielle
            case P0: {	 
                Press(interrupteur);                //On verifie si l'interrupteur est appuie (PRESS)
                if (interrupteur)                   //S'il est appuie
                    relache = false;                //La variable booleenne relache prends la valeur false
                Press(interrupteur);                
                if ((!interrupteur) && !relache){   //Passage au prochain etat si l'interrupteur est relache apres avoir ete appuie (RELEASE)
                    etat = P1;
                    relache = true;                 //On reinitialise la variable booleenne relache a true pour le prochain etat
                }
                break;}
        
            case P1 :{
                Press(interrupteur);               
                if (interrupteur)
                    relache = false;
                Press(interrupteur);            
                if ((!interrupteur) && !relache){           
                    etat = P2;
                    relache = true;
                }
                break;}
                
            case P2 :{
                Press(interrupteur);                
                if (interrupteur)
                    relache = false;
                Press(interrupteur);            
                if ((!interrupteur) && !relache){              
                    etat = P3;
                    relache = true;
                }
                break;}
                
            case P3 :{
                Press(interrupteur);                
                if (interrupteur)
                    relache = false;
                Press(interrupteur);            
                if ((!interrupteur) && !relache){              
                    etat = P4;
                    relache = true;
                }
                break;}
                
            case P4 :{
                Press(interrupteur);                
                if (interrupteur)
                    relache = false;
                Press(interrupteur);            
                if ((!interrupteur) && !relache){             
                    etat = DEL;
                    relache = true;
                }
                break;}
                
            case DEL :{
                PORTA = ROUGE;                      //La DEL libre affiche la couleur rouge pendant 1 seconde
                _delay_ms(1000);
                PORTA = 0x00;                       //La DEL libre est eteinte
                etat = P0;                          //Retour a l'etat initial
                break;}
            
            default :{
                etat = P0;
                break;}
                
            };
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
                    interrupteur = true;            //La variable booleenne interrupteur prends la valeur true (PRESS)
                }
    }
    else if (!(PIND & 0x04)){                       //Si le bouton pressoir de la section interupt n'est pas appuie
        interrupteur = false;                       //La variable booleenne interrupteur prends la valeur false (RELEASE)
    }
}

#include "pwm.h"
#include "uart.h"
#include "buzzer.h"
#include "delai.h"
#include "memoire_24.h"
#include "defines.h"
#include "capteurs_distance.h"
#include "moteurs.h"

int main()
{
    DDRB = SORTIE;
    DDRA = SORTIE:
    DDRD = SORTIE;
    CapteursDistance::init();
    
    /*Debut de prototype de code pour le trajet
     for(;;){
         uint8_t droit = CapteursDistance::getDistanceDroit();
         uint8_t gauche = CapteursDistance::getDistanceGauche();
        //Maintient de la direction
         while (droit == 15 || gauche == 15)
        {
            setDirection(DirectionMoteur::Avant);
            setPourcentage(40);
            
     
        }
        
        if (droit < 15 && gauche > 15)
            virageGauche(); //utiliser fct appropriees
        if (droit > 15 && gauche < 15)
            virageDroit();
        //Exception del ajustement
        if (droit < 15 && ) //cas ou un mur tourne va en angle et on doit le suivre 
            virageDroit();
        if (gauche < 15 && )
            virageGauche();
        //Fin exception del ajustement    
        //fin d'un mur
        if (droit && gauche){
           if (){
            virageGauche();
            virageGauche();
            }
           else {
            virageDroit();
            virageDroit();
            }
        }
    
        //Differencier mur/poteau
        timer(0?, 2 pour buzzer et 1 pour moteurs) pour mesurer temps distance mesuree puis interruption contenant
            buzzer::play();
            waitForMs(200);
            buzzer::play();
            waitForMs(200);
            buzzer::play();
            WaitForMs(200);
        //Changement mur
        while{
        while (droit) || while (gauche){ //oppose du cote ou on doit rester
            setDirection(DirectionMoteur::Avant);
            setPourcentage(40);
        }
        virageDroit() || virageGauche(); //utiliser fct appropriees
        }
        //interrupteur
        virageGauche(); //combiner en une instruction
        virageGauche();
        //del ajustement lors des virage
        PORTA = ROUGE; 
    }
     */
    return 0;
}

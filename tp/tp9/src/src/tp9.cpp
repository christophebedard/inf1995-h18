#include "pwm.h"
#include "uart.h"
#include "buzzer.h"
#include "delai.h"
#include "memoire_24.h"
#include "defines.h"

int main(){
    DDRA = SORTIE;
    DDRD = SORTIE;   
    DDRB = SORTIE;                                          //Toutes les broches de A et de D sont en sortie    
    /*Sequence initiale*/
    PORTA = ROUGE;
    waitForMs(250);
    PORTA = VERT;
    waitForMs(250);
    PORTA = ROUGE;
    waitForMs(250);
    PORTA = VERT;
    waitForMs(250);
    PORTA = ETEINT;
    
    /*Debut interpretation*/
    Memoire24CXXX M;
    uint16_t adr = 0x00;
    uint8_t tailleH = 0;
    uint8_t tailleL = 0;
    uint16_t taille = 0;
    
    M.lecture(adr++, &tailleH);
    waitForMs(5);
    M.lecture(adr++, &tailleL);
    waitForMs(5);
    
    taille |= tailleH << 8;
    taille |= tailleL;
    taille -= 2;                                                //Permet de ne pas considerer les octets donnant la taille 
    
    uint8_t lire[taille];
    
    for (uint16_t i = 0; i < taille;i++){
        M.lecture(adr++, &lire[i]);                             //Lecture de la donnee ecrite en memoire
        waitForMs(5);
    }
    
    bool couleur = false;
    bool interpretation = false;
    bool boucle = false;
    uint8_t debutBoucle = 0;
    uint8_t incrementation = 0;
    
    initPWM();
    Buzzer::init();
    
    for (uint8_t i = 0; i < taille; i++){   
        if (lire[i] == 0x01)
             interpretation = true;                             //S'assure que l'interpretation se fasse uniquement lorsque la commande dbt du pseudocode est entree
             
        else if (interpretation){     
            switch (lire[i]) {                             
                case 0xFF:{
                    interpretation = false;                     //Si fin, on arrete d'interpreter
                break;}
                
                case 0x02:{
                    waitForMs(25*(lire[i+1]));                  //25 ms fois l'operande en memoire
                break;}
            
                case 0x44:{
                    if (!couleur){                              //Affichage des couleurs sur la DEL, condition simplement pour alterner l'affichage
                        PORTA = VERT;
                        couleur = true;
                    }
                    else{
                        PORTA = ROUGE;
                        couleur = false;
                    }
                break;}
            
                case 0x45:{
                    PORTA = ETEINT;                             //On eteint la DEL
                break;}
            
                case 0x48:{                                     //Son
                   Buzzer::play(lire[i + 1]);
                break;}
            
                case 0x09:{                                     //Fin son
                   Buzzer::stop();
                break;}
                
                case 0x60:{ //Arret moteur                      //Deux commandes provoquent l'arret du moteur
                    ajustementPWM(0);           
                break;}
                
                case 0x61:{ //Arret moteur
                    ajustementPWM(0);
                break;}
                
                case 0x62:{ //Avancer              
                    PORTD = 0x00;                               
                    ajustementPWM((lire[i + 1]/0xff) * 100);    //Operande/0xff * 100 pour obtenir valeur utilisee par la fonction
                break;}
                
                case 0x63:{ //Reculer
                    PORTD = 0x0C;                               //Meme chose que pour avancer, mais avec le bit de direction oppose
                    ajustementPWM((lire[i + 1]/0xff) * 100);
                break;}
                
                case 0x64:{ //Droite
                    PORTD = 0x00; 
                    virageDroit(55);                            //55% de vitesse, voir la fonction dans la librairie, fait le virage 90 degré
                break;}
                
                case 0x65:{ //Gauche    
                    PORTD = 0x00;                               //55% de vitesse, voir la fonction dans la librairie, fait le virage 90 degré
                    virageGauche(55);
                break;}
                
                case 0xC0:{ //DBoucle
                    if ((incrementation = 0) && (!boucle)){     //Si l'incrementation est a 0 et qu'il n'y a aucune boucle active
                     incrementation += lire[i+1];               //On passe l'operande a la variable incrementation
                     boucle = true;                             //Booleen pour s'assurer qu'une seule boucle est active a la fois
                     debutBoucle = i;                           //Sauvegarde la position i pour y retourner 
                    }
                    if ((incrementation = 0) && (boucle)){
                    
                        boucle = false;                         //Pour pouvoir faire un autre boucle après la fin de la premiere
                    }
                break;}
                
                case 0xC1:{ //FBoucle
                    if (incrementation != 0){                   
                        incrementation--;                       //On decremente avant de passer à la prochaine iteration 
                        i = debutBoucle;                        //On retourne au debut de la boucle
                    }
                break;}
                
                default:
                break;}
        }
    i++;                                                        //Ce deuxieme i++ permet de ne pas interpreter les operandes
    }
return 0;
}

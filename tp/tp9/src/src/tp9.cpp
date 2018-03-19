#include "pwm.h"
#include "uart.h"
#include "buzzer.h"
#include "delai.h"
#include "memoire_24.h"
#include "defines.h"

int main(){
    DDRA = SORTIE;
    DDRD = SORTIE;                          //Toutes les broches de A et de D sont en sortie 
    Buzzer::init();
    /*Ecriture des donnees*/
    UART::init();
    uint8_t donnee[6];
    uint8_t taille = 8*sizeof(uint8_t);     //Valeurs numériques utilisées pour le test
    int i = 0;
    donnee[0] = 0x01;//Test
    donnee[1] = 0x00;
    donnee[2] = 0x62;
    donnee[3] = 0x80;
    donnee[4] = 0xFF;
    donnee[5] = 0x00;
    PORTA = ROUGE;                          //Verification du debut du programme
    waitForMs(250);
    while(!(UCSR0A & (1 << UDRE0))){        //Pas certain, l'opposé de la condition dans transmissionUART()
        donnee[i++] = UART::reception();      //Ajoute une donnee au tableau
        taille += sizeof(uint8_t);          //Incremente la taille
    }
    Memoire24CXXX M = Memoire24CXXX();      //Objet pour la lecture/ecriture
    M.ecriture(0x00, donnee, taille);                      
    PORTA = VERT;                    /*Vérifie la fin de l'ecriture*/
    waitForMs(250);
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
    uint8_t lire[8];                 //Valeur numerique pour test
    M.lecture(0x00, lire, taille);   //Lecture de la donnee ecrite en memoire
    waitForMs(5);
    bool couleur = false;
    bool interpretation = false;
    bool boucle = false;
    uint8_t debutBoucle = 0;
    uint8_t incrementation = 0;
    initPWM();                        
    for (uint8_t i = 0; i < taille; i++){   
        if (lire[i] == 0x01)
             interpretation = true; //S'assure que l'interpretation se fasse uniquement si la commande dbt du pseudocode est entree
        else if (interpretation){     
            PORTA = ROUGE;          //test
            waitForMs(500);
            switch (lire[i]) {                             
                case 0xFF:{
                    interpretation = false;     //Si fin, on arrete d'interpreter
                
                break;}
                case 0x02:{
                    waitForMs(25*lire[i+1]);    //25 ms fois l'operande en memoire
                break;}
            
                case 0x44:{
                    if (!couleur){            //Affichage des couleurs sur la DEL, condition simplement pour alterner l'affichage
                        PORTA = VERT;
                        couleur = true;
                    }
                    else{
                        PORTA = ROUGE;
                        couleur = false;
                    }
                break;}
            
                case 0x45:{
                    PORTA = ETEINT;            //On eteint la DEL
                break;}
            
                case 0x48:{ //Son
                    Buzzer::play(lire[i + 1]);
                break;}
            
                case 0x09:{ //Fin son
                    Buzzer::stop();
                break;}
                
                case 0x60:{ //Arret moteur          //Deux commandes provoquent l'arret du moteur
                    ajustementPWM(0);           
                break;}
                case 0x61:{ //Arret moteur
                    ajustementPWM(0);
                break;}
                case 0x62:{ //Avancer               //Affichage de del pour test
                    PORTA = VERT;
                    waitForMs(250);
                    PORTD = 0x00;                               
                    ajustementPWM((lire[i + 1]/0xff) * 100); //Operande/0xff * 100 pour obtenir valeur utilisee par la fonction
                    
                break;}
                case 0x63:{ //Reculer
                    PORTD = 0x0C;                           //Meme chose que pour avancer, mais avec le bit de direction oppose
                    ajustementPWM((lire[i + 1]/0xff) * 100);
                    
                break;}
                case 0x64:{ //Droite
                    PORTD = 0x00; 
                    virageDroit(55);                 //55% de vitesse, voir la fonction dans la librairie, fait le virage 90 degré
                break;}
                case 0x65:{ //Gauche    
                    PORTD = 0x00;                   //55% de vitesse, voir la fonction dans la librairie, fait le virage 90 degré
                    virageGauche(55);
                break;}
                case 0xC0:{ //DBoucle
                    if ((incrementation = 0) && (!boucle)){     //Si l'incrementation est a 0 et qu'il n'y a aucune boucle active
                     incrementation += lire[i+1];               //On passe l'operande a la variable incrementation
                     boucle = true;                             //Booleen pour s'assurer qu'une seule boucle est active a la fois
                     debutBoucle = i;                           //Sauvegarde la position i pour y retourner 
                    }
                    if ((incrementation = 0) && (boucle)){
                    
                        boucle = false;                       //Pour pouvoir faire un autre boucle après la fin de la premiere
                    }
                    
                     
                break;}
                case 0xC1:{ //FBoucle
                    if (incrementation != 0){                   
                        incrementation--;                      //On decremente avant de passer à la prochaine iteration 
                        i = debutBoucle;                       //On retourne au debut de la boucle
                    }
                break;}
                default:
                break;
                
        
        }
        }
        i++;                                                    //Ce deuxieme i++ permet de ne pas interpreter les operandes
    }
    return 0;
}

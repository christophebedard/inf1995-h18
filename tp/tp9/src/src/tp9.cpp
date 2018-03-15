#include "pwm.h"
#include "uart.h"
#include "delai.h"
#include "memoire_24.h"
#include "defines.h"

int main(){

    DDRA = 0xff;
    DDRD = SORTIE;
    /*Ecriture des donnees*/
    initialisationUART();
    uint8_t donnee[6];
    uint8_t taille = 8*sizeof(uint8_t);
    int i = 0;
    donnee[0] = 0x01;//Test
    donnee[1] = 0x00;
    donnee[2] = 0x62;
    donnee[3] = 0x80;
    donnee[4] = 0xFF;
    donnee[5] = 0x00;
    PORTA = ROUGE;
    
    waitForMs(250);
    while(!(UCSR0A & (1 << UDRE0))){
        donnee[i++] = receptionUART();
        taille += sizeof(uint8_t);
    }
    Memoire24CXXX M = Memoire24CXXX();
    M.ecriture(0x00, donnee, taille);                  
    PORTA = VERT;                    /*Fin de l'ecriture*/
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
    uint8_t lire[8];
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
             interpretation = true;
        else if (interpretation){
            PORTA = ROUGE;
            waitForMs(500);
            switch (lire[i]) {                             
                case 0xFF:{
                    interpretation = false;
                
                break;}
            
                case 0x02:{
                    waitForMs(25*lire[i+1]);
                break;}
            
                case 0x44:{
                    if (!couleur){
                        PORTA = VERT;
                        couleur = true;
                    }
                    else{
                        PORTA = ROUGE;
                        couleur = false;
                    }
                break;}
            
                case 0x45:{
                    PORTA = ETEINT;
                break;}
            
                case 0x48:{ //Son
                   // debutSon((lire[i + 1]/0xff) * 100);
                break;}
            
                case 0x09:{ //Fin son
                   // finSon();
                break;}
                
                case 0x60:{ //Arret moteur
                    ajustementPWM(0);
                break;}
                case 0x61:{ //Arret moteur
                    ajustementPWM(0);
                break;}
                case 0x62:{ //Avancer
                    PORTA = VERT;
                    waitForMs(250);
                    PORTD = 0x00;
                    ajustementPWM((lire[i + 1]/0xff) * 100); //Bas direction
                    
                break;}
                case 0x63:{ //Reculer
                    PORTD = 0x0C;
                    ajustementPWM((lire[i + 1]/0xff) * 100);
                    
                break;}
                case 0x64:{ //Droite
                    PORTD = 0x00; 
                    virageDroit(55);   
                break;}
                case 0x65:{ //Gauche
                    PORTD = 0x00; 
                    virageGauche(55);
                break;}
                case 0xC0:{ //DBoucle
                    if ((incrementation = 0) && (!boucle)){
                     incrementation += lire[i+1];
                     boucle = true;
                     debutBoucle = i;
                    }
                    
                     
                break;}
                case 0xC1:{ //FBoucle
                    if (incrementation != 0){
                        incrementation--;
                        i = debutBoucle;
                    }
                break;}
                default:
                break;
                
        
        }
        }
        i++;
    }
    return 0;
}

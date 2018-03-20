#include "pwm.h"
#include "uart.h"
#include "buzzer.h"
#include "delai.h"
#include "memoire_24.h"
#include "debug.h"
#include "defines.h"

int main()
{
    // Toutes les broches de A, B et de D sont en sortie
    DDRA = SORTIE;
    DDRB = SORTIE;
    DDRD = SORTIE;   
    
    /* Sequence initiale */
    PORTA = ROUGE;
    waitForMs(250);
    PORTA = VERT;
    waitForMs(250);
    PORTA = ROUGE;
    waitForMs(250);
    PORTA = VERT;
    waitForMs(250);
    PORTA = ETEINT;
    
    // initialisations
    UART::init(); // pour debug

    /* Debut interpretation */
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
    // Permet de ne pas considerer les octets donnant la taille
    taille -= 2;
    
    uint8_t lire[taille];
    
    Debug::out("debut lecture memoire\n");
    for (uint16_t i = 0; i < taille;i++)
    {
        // Lecture de la donnee ecrite en memoire
        M.lecture(adr++, &lire[i]);
        waitForMs(5);
    }
    Debug::out("fin lecture memoire\n");
    
    initPWM();
    Buzzer::init();

    // flags d'interpretation
    bool couleur = false;
    bool interpretation = false;
    bool boucle = false;
    uint8_t debutBoucle = 0;
    uint8_t incrementation = 0;
    
    Debug::out("debut execution\n");
    for (uint8_t i = 0; i < taille; i++)
    {   
        if (lire[i] == 0x01)
        {
            Debug::out("debut interpretation\n");
            // S'assure que l'interpretation se fasse uniquement lorsque la commande dbt du pseudocode est entree
            interpretation = true;
        }
        else if (interpretation)
        {     
            switch (lire[i])
            {                             
                case 0xFF:{
                    Debug::out("fin interpretation\n");
                    // Si fin, on arrete d'interpreter
                    interpretation = false;
                break;}
                
                case 0x02:{ // attendre 25 ms fois l'operande en memoire
                    Debug::out("att : ");
                    Debug::out(25*(lire[i+1]));
                    Debug::out("\n");
                    waitForMs(25*(lire[i+1]));
                break;}
            
                case 0x44:{ // Affichage des couleurs sur la DEL, condition simplement pour alterner l'affichage
                    if (!couleur)
                    {
                        Debug::out("vert\n");
                        PORTA = VERT;
                        couleur = true;
                    }
                    else
                    {
                        Debug::out("rouge\n");
                        PORTA = ROUGE;
                        couleur = false;
                    }
                break;}
            
                case 0x45:{ // On eteint la DEL
                    Debug::out("etteint DELs");
                    PORTA = ETEINT;
                break;}
            
                case 0x48:{ // Son
                    Debug::out("buzzer : ");
                    Debug::out(lire[i + 1]);
                    Debug::out("\n");
                    Buzzer::play(lire[i + 1]);
                break;}
            
                case 0x09:{ // Fin son
                    Debug::out("stop buzzer\n");
                    Buzzer::stop();
                break;}
                
                // Deux commandes provoquent l'arret du moteur
                case 0x60:{ // Arret moteur
                    Debug::out("stop moteur\n");
                    ajustementPWM(0);           
                break;}
                
                case 0x61:{ // Arret moteur
                    Debug::out("stop moteur\n");
                    ajustementPWM(0);
                break;}
                
                case 0x62:{ // Avancer              
                    Debug::out("avance : ");
                    Debug::out((lire[i + 1]/0xff) * 100);
                    Debug::out("\n");
                    PORTD = 0x00;
                    // Operande/0xff * 100 pour obtenir valeur utilisee par la fonction    
                    ajustementPWM((lire[i + 1]/0xff) * 100);
                break;}
                
                case 0x63:{ //Reculer
                    Debug::out("recule : ");
                    Debug::out((lire[i + 1]/0xff) * 100);
                    Debug::out("\n");
                    // Meme chose que pour avancer, mais avec le bit de direction oppose
                    PORTD = 0x0C;
                    ajustementPWM((lire[i + 1]/0xff) * 100);
                break;}
                
                case 0x64:{ //Droite
                    Debug::out("virage droit\n");
                    PORTD = 0x00;
                    // 55% de vitesse, voir la fonction dans la librairie, fait le virage 90 degres
                    virageDroit(55);
                break;}
                
                case 0x65:{ //Gauche    
                    Debug::out("virage gauche\n");
                    // 55% de vitesse, voir la fonction dans la librairie, fait le virage 90 degres
                    PORTD = 0x00;
                    virageGauche(55);
                break;}
                
                case 0xC0:{ // DBoucle
                    Debug::out("debut boucle\n");
                    if ((incrementation = 0) && (!boucle)){     // Si l'incrementation est a 0 et qu'il n'y a aucune boucle active
                        incrementation += lire[i+1];            // On passe l'operande a la variable incrementation
                        boucle = true;                          // Booleen pour s'assurer qu'une seule boucle est active a la fois
                        debutBoucle = i;                        // Sauvegarde la position i pour y retourner 
                    }
                    if ((incrementation = 0) && (boucle)){
                        boucle = false;                         // Pour pouvoir faire un autre boucle après la fin de la premiere
                    }
                break;}
                
                case 0xC1:{ // FBoucle
                    if (incrementation != 0){
                        Debug::out("boucle\n");
                        incrementation--;                       // On decremente avant de passer à la prochaine iteration 
                        i = debutBoucle;                        // On retourne au debut de la boucle
                    }
                break;}
                
                default:
                    break;
            }
        }
        // Ce deuxieme i++ permet de ne pas interpreter les operandes
        i++;
    }
    Debug::out("fin execution\n");

    return 0;
}

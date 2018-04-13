/**
 * \file lecteur_wav.cpp
 * \brief implementation de la classe LecteurWav
 * \author 
 */

#include "lecteur_wav.h"


volatile uint16_t LecteurWav::position_ = 0;
volatile uint8_t LecteurWav::compteurUpdate_ = INTERVALLE_MISE_A_JOUR;
bool LecteurWav::loop_ = false;
bool LecteurWav::isPlaying_ = false;
const uint8_t* LecteurWav::donnees_ = nullptr;
uint16_t LecteurWav::longueurDonnees_ = 0;


void callbackDonnee()
{
    if(LecteurWav::isPlaying_)
    {
        LecteurWav::compteurUpdate_--;
        
        if(LecteurWav::compteurUpdate_ == 0) 
        {
            // reset le compteur de mise a jour
            LecteurWav::compteurUpdate_ = INTERVALLE_MISE_A_JOUR;
            
            // update la valeur
            OCR0A = pgm_read_byte(&LecteurWav::donnees_[LecteurWav::position_++]);
            
            // verification fin des donnees
            if(LecteurWav::position_ >= LecteurWav::longueurDonnees_)
            {
                // si loop fichier
                if(LecteurWav::loop_)
                {
                    // recommence
                    LecteurWav::position_ = 0;
                }
                else
                {
                    // sinon, arret
                    LecteurWav::stop();
                }
            }
        }
    }
}

void LecteurWav::init()
{
    // pin OC0A en sortie pour le buzzer
    DDRB |= _BV(_BROCHE_TO_PIN(BROCHE_BUZZER_WAV));
}

void LecteurWav::setWav(const uint8_t* donnees, uint16_t longueur)
{
    donnees_ = donnees;
    longueurDonnees_ = longueur;
}

void LecteurWav::play(bool loop)
{
    loop_ = loop;

    if(donnees_ != nullptr)
    {
        startTimers();

        // initialisation du compteur de mise a jour
        compteurUpdate_ = INTERVALLE_MISE_A_JOUR;
        // set le flag de lecture en cours
        isPlaying_ = true;
        // reset la position de lecture
        position_ = 0;
    }
}

void LecteurWav::stop()
{
    Timer0::stop();
    Timer2::stop();
    isPlaying_ = false;
}

bool LecteurWav::isPlaying()
{
    return isPlaying_;
}

void LecteurWav::startTimers()
{
    cli();

    // initialise le timer0 pour PWM sur A
    Timer0::setCompareOutputMode(COM::Set, COM::Normal);
    Timer0::setWaveformGenerationMode(WGM::Mode_1);
    Timer0::setPrescaler(Prescaler::Div_1);
    Timer0::setOCRnA(0);

    // initialise le timer2 pour la mise a jour des notes
    Timer2::setOverflowCallback(&callbackDonnee);
    Timer2::setWaveformGenerationMode(WGM::Mode_1);
    Timer2::setPrescaler(Prescaler::Div_1);
    Timer2::setInterruptEnable(false, false, true);
    Timer2::resetTCNTn();

    sei();
}
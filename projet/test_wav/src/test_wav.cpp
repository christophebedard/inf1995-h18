/**
 * \file test_wav.cpp
 * \brief programme pour tester la lecture de donnees de fichiers wav
 * \author 
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "wav_data.h"

#define SAMPLE_COUNT_SCALE 2
volatile uint16_t sample;
volatile int sample_count;
bool loop = false;
volatile bool lecture;


void init(void)
{
    cli();

    // pin OC1A en sortie pour le buzzer
    DDRD = _BV(PD5);

    // clear OC1A on compare match 
    // set OC1A at BOTTOM, non-inverting mode
    // fast PWM, 8bit
    TCCR1A = _BV(COM1A1) | _BV(WGM10);
    
    // fast PWM, 8bit
    // prescaler : clk/1 = 8 MHz
    // PWM frequency = 8 MHz / (255 + 1) = 31.25 kHz
    TCCR1B = _BV(WGM12) | _BV(CS10);
    
    // reset
    OCR1A = 0;
    
    // timer0 pour la mise a jour des valeurs  
    TCCR0A |= (1 << CS00);
    TCCR0B |= (1 << CS00);
    TCNT0 = 0;
    TIMSK0 |= (1 << TOIE0);

    // initialisation du compteur de scale
    sample_count = SAMPLE_COUNT_SCALE;
    // initialisation de la lecture
    lecture = true;

    sei();
}

ISR(TIMER0_OVF_vect)
{
    if(lecture)
    {
        sample_count--;
        
        if(sample_count == 0) 
        {
            // reset le compteur de scale
            sample_count = SAMPLE_COUNT_SCALE;
            
            // update la valeur
            OCR1A = pgm_read_byte(&pcm_samples[sample++]);
            
            // verification fin des donnees
            if(sample >= pcm_length)
            {
                // si loop fichier
                if(loop)
                {
                    // recommence
                    sample = 0;
                }
                else
                {
                    // sinon, arret
                    lecture = false;
                }
            }
        }
    }
} 

int main(void)
{
    init();
    
    while(true);

    return 0;
}

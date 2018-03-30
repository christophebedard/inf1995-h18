/**
 * \file test_wav.cpp
 * \brief programme pour tester la lecture de donnees de fichiers wav
 * \author 
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "samples.h"


volatile uint16_t sample;
int sample_count;


void init(void)
{
    cli();

    /* use OC1A pin as output */
    DDRD = _BV(PD5);

    /* 
    * clear OC1A on compare match 
    * set OC1A at BOTTOM, non-inverting mode
    * Fast PWM, 8bit
    */
    TCCR1A = _BV(COM1A1) | _BV(WGM10);
    
    /* 
    * Fast PWM, 8bit
    * Prescaler: clk/1 = 8MHz
    * PWM frequency = 8MHz / (255 + 1) = 31.25kHz
    */
    TCCR1B = _BV(WGM12) | _BV(CS10);
    
    /* set initial duty cycle to zero */
    OCR1A = 0;
    
    /* Setup Timer0 */  
    TCCR0A |= (1 << CS00);
    TCCR0B |= (1 << CS00);
    TCNT0 = 0;
    TIMSK0 |= (1 << TOIE0);
    sample_count = 4;

    sei();
}

ISR(TIMER0_OVF_vect)
{
    sample_count--;
    if (sample_count == 0) 
    {
        sample_count = 4;           
        OCR1A = pgm_read_byte(&pcm_samples[sample++]);
        if(sample>=pcm_length)sample=0;
    }
} 

int main(void)
{
    init();
    
    while(true);

    return 0;
}

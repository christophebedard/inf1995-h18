/**
 * \file test_wav.cpp
 * \brief programme pour tester la lecture de donnees de fichiers wav
 * \author 
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "lecteur_wav.h"
#include "wav_data.h"


int main(void)
{
    LecteurWav::init();
    LecteurWav::setWav(pcm_samples, pcm_length);
    LecteurWav::play(false);
    
    while(true);

    return 0;
}

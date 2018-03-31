/**
 * \file test_wav.cpp
 * \brief programme pour tester la lecture de donnees de fichiers wav
 * \author 
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "lecteur_wav.h"
#include "data_tinkywinky.h"
#include "data_laalaa.h"


int main(void)
{
    LecteurWav::init();
    
    LecteurWav::setWav(tinkywinky_data, tinkywinky_longueur);
    LecteurWav::play(false);

    while(LecteurWav::isPlaying());

    LecteurWav::setWav(laalaa_data, laalaa_longueur);
    LecteurWav::play(false);
    
    while(true);

    return 0;
}

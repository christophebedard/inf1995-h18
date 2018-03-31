/**
 * \file test_wav.cpp
 * \brief programme pour tester la lecture de donnees de fichiers wav
 * \author 
 */

#include "lecteur_wav.h"
#include "data_tinkywinky.h"
#include "data_laalaa.h"

int main(void)
{
    LecteurWav::init();
    
    LecteurWav::setWav(tinkywinky_data, tinkywinky_longueur);
    LecteurWav::play();

    while(LecteurWav::isPlaying());

    LecteurWav::setWav(laalaa_data, laalaa_longueur);
    LecteurWav::play(true);
    
    while(true);

    return 0;
}

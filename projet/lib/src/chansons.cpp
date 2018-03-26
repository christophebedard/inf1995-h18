/**
 * \file chansons.cpp
 * \brief definition de chansons
 * \author 
 */

#include "chansons.h"

ChansonMusique Chansons::chansonMario = {
    66,
    { // https://gist.github.com/CodyJung/2315618
        {76, NoteMusicale::DoubleCroche}, {76, NoteMusicale::DoubleCroche},
        {20, NoteMusicale::DoubleCroche}, {76, NoteMusicale::DoubleCroche},
        {20, NoteMusicale::DoubleCroche}, {72, NoteMusicale::DoubleCroche},
        {76, NoteMusicale::DoubleCroche}, {20, NoteMusicale::DoubleCroche},
        {79, NoteMusicale::DoubleCroche}, {20, NoteMusicale::Noire},
        {67, NoteMusicale::DoubleCroche}, {20, NoteMusicale::Noire},

        {72, NoteMusicale::DoubleCroche}, {20, NoteMusicale::Croche},
        {67, NoteMusicale::DoubleCroche}, {20, NoteMusicale::Croche},
        {64, NoteMusicale::DoubleCroche}, {20, NoteMusicale::Croche},
        {69, NoteMusicale::DoubleCroche}, {20, NoteMusicale::DoubleCroche},
        {71, NoteMusicale::DoubleCroche}, {20, NoteMusicale::DoubleCroche},
        {70, NoteMusicale::DoubleCroche}, {69, NoteMusicale::DoubleCroche},
        {20, NoteMusicale::DoubleCroche}, {67, NoteMusicale::DoubleCroche},
        {76, NoteMusicale::DoubleCroche}, {79, NoteMusicale::DoubleCroche},
        {81, NoteMusicale::DoubleCroche}, {20, NoteMusicale::DoubleCroche},
        {77, NoteMusicale::DoubleCroche}, {79, NoteMusicale::DoubleCroche},
        {20, NoteMusicale::DoubleCroche}, {76, NoteMusicale::DoubleCroche},
        {20, NoteMusicale::DoubleCroche}, {72, NoteMusicale::DoubleCroche},
        {74, NoteMusicale::DoubleCroche}, {71, NoteMusicale::DoubleCroche},
        {20, NoteMusicale::Croche},
        
        {72, NoteMusicale::DoubleCroche}, {20, NoteMusicale::Croche},
        {67, NoteMusicale::DoubleCroche}, {20, NoteMusicale::Croche},
        {64, NoteMusicale::DoubleCroche}, {20, NoteMusicale::Croche},
        {69, NoteMusicale::DoubleCroche}, {20, NoteMusicale::DoubleCroche},
        {71, NoteMusicale::DoubleCroche}, {20, NoteMusicale::DoubleCroche},
        {70, NoteMusicale::DoubleCroche}, {69, NoteMusicale::DoubleCroche},
        {20, NoteMusicale::DoubleCroche}, {67, NoteMusicale::DoubleCroche},
        {76, NoteMusicale::DoubleCroche}, {79, NoteMusicale::DoubleCroche},
        {81, NoteMusicale::DoubleCroche}, {20, NoteMusicale::DoubleCroche},
        {77, NoteMusicale::DoubleCroche}, {79, NoteMusicale::DoubleCroche},
        {20, NoteMusicale::DoubleCroche}, {76, NoteMusicale::DoubleCroche},
        {20, NoteMusicale::DoubleCroche}, {72, NoteMusicale::DoubleCroche},
        {74, NoteMusicale::DoubleCroche}, {71, NoteMusicale::DoubleCroche},
        {20, NoteMusicale::Croche}
    },
    Tempo::Tempo_Vivace
};

ChansonMusique Chansons::chansonTeletubbies = {
    41,
    {
        {98, NoteMusicale::DoubleCroche}, {0, NoteMusicale::DoubleCroche},
        {98, NoteMusicale::DoubleCroche}, {0, NoteMusicale::DoubleCroche},
        {62, NoteMusicale::DoubleCroche}, {0, NoteMusicale::DoubleCroche},
        {98, NoteMusicale::DoubleCroche}, {0, NoteMusicale::DoubleCroche},
        {122, NoteMusicale::DoubleCroche}, {0, NoteMusicale::DoubleCroche},
        {74, NoteMusicale::DoubleCroche}, {0, NoteMusicale::DoubleCroche},
        {98, NoteMusicale::DoubleCroche}, {0, NoteMusicale::DoubleCroche},
        {62, NoteMusicale::DoubleCroche}, {0, NoteMusicale::DoubleCroche},
        {105, NoteMusicale::DoubleCroche}, {0, NoteMusicale::DoubleCroche},
        {98, NoteMusicale::DoubleCroche}, {0, NoteMusicale::DoubleCroche},
        {98, NoteMusicale::DoubleCroche}, {0, NoteMusicale::DoubleCroche},
        {62, NoteMusicale::DoubleCroche}, {0, NoteMusicale::DoubleCroche},
        {81, NoteMusicale::DoubleCroche}, {0, NoteMusicale::DoubleCroche},
        {122, NoteMusicale::DoubleCroche}, {0, NoteMusicale::DoubleCroche},
        {122, NoteMusicale::DoubleCroche}, {0, NoteMusicale::DoubleCroche},
        {74, NoteMusicale::DoubleCroche}, {0, NoteMusicale::DoubleCroche},
        {122, NoteMusicale::DoubleCroche}, {0, NoteMusicale::DoubleCroche},
        {0, NoteMusicale::DoubleCroche}, {98, NoteMusicale::DoubleCroche},
        {0, NoteMusicale::DoubleCroche}, {98, NoteMusicale::DoubleCroche},
        {91, NoteMusicale::DoubleCroche}, {0, NoteMusicale::DoubleCroche},
        {103, NoteMusicale::DoubleCroche}
    },
    Tempo::Tempo_Prestissimo
};

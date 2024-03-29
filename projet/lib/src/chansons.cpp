/**
 * \file chansons.cpp
 * \brief definition de chansons
 * \author Christophe Bourque Bedard
 * \author Simon Moreau
 * \author Fares Ouaissa
 * \author Mohamed Saddik
 */

#include "chansons.h"

ChansonMusique Chansons::mario = {
    66,
    { // https://gist.github.com/CodyJung/2315618
        {76, FigureDeNote::DoubleCroche}, {76, FigureDeNote::DoubleCroche},
        {20, FigureDeNote::DoubleCroche}, {76, FigureDeNote::DoubleCroche},
        {20, FigureDeNote::DoubleCroche}, {72, FigureDeNote::DoubleCroche},
        {76, FigureDeNote::DoubleCroche}, {20, FigureDeNote::DoubleCroche},
        {79, FigureDeNote::DoubleCroche}, {20, FigureDeNote::Noire},
        {67, FigureDeNote::DoubleCroche}, {20, FigureDeNote::Noire},

        {72, FigureDeNote::DoubleCroche}, {20, FigureDeNote::Croche},
        {67, FigureDeNote::DoubleCroche}, {20, FigureDeNote::Croche},
        {64, FigureDeNote::DoubleCroche}, {20, FigureDeNote::Croche},
        {69, FigureDeNote::DoubleCroche}, {20, FigureDeNote::DoubleCroche},
        {71, FigureDeNote::DoubleCroche}, {20, FigureDeNote::DoubleCroche},
        {70, FigureDeNote::DoubleCroche}, {69, FigureDeNote::DoubleCroche},
        {20, FigureDeNote::DoubleCroche}, {67, FigureDeNote::DoubleCroche},
        {76, FigureDeNote::DoubleCroche}, {79, FigureDeNote::DoubleCroche},
        {81, FigureDeNote::DoubleCroche}, {20, FigureDeNote::DoubleCroche},
        {77, FigureDeNote::DoubleCroche}, {79, FigureDeNote::DoubleCroche},
        {20, FigureDeNote::DoubleCroche}, {76, FigureDeNote::DoubleCroche},
        {20, FigureDeNote::DoubleCroche}, {72, FigureDeNote::DoubleCroche},
        {74, FigureDeNote::DoubleCroche}, {71, FigureDeNote::DoubleCroche},
        {20, FigureDeNote::Croche},
        
        {72, FigureDeNote::DoubleCroche}, {20, FigureDeNote::Croche},
        {67, FigureDeNote::DoubleCroche}, {20, FigureDeNote::Croche},
        {64, FigureDeNote::DoubleCroche}, {20, FigureDeNote::Croche},
        {69, FigureDeNote::DoubleCroche}, {20, FigureDeNote::DoubleCroche},
        {71, FigureDeNote::DoubleCroche}, {20, FigureDeNote::DoubleCroche},
        {70, FigureDeNote::DoubleCroche}, {69, FigureDeNote::DoubleCroche},
        {20, FigureDeNote::DoubleCroche}, {67, FigureDeNote::DoubleCroche},
        {76, FigureDeNote::DoubleCroche}, {79, FigureDeNote::DoubleCroche},
        {81, FigureDeNote::DoubleCroche}, {20, FigureDeNote::DoubleCroche},
        {77, FigureDeNote::DoubleCroche}, {79, FigureDeNote::DoubleCroche},
        {20, FigureDeNote::DoubleCroche}, {76, FigureDeNote::DoubleCroche},
        {20, FigureDeNote::DoubleCroche}, {72, FigureDeNote::DoubleCroche},
        {74, FigureDeNote::DoubleCroche}, {71, FigureDeNote::DoubleCroche},
        {20, FigureDeNote::Croche}
    },
    Tempo::Vivace
};

ChansonMusique Chansons::starWarsMarcheImperiale = {
    43,
    {
        {G4, FigureDeNote::DoubleCroche},
        {G4, FigureDeNote::DoubleCroche},
        {G4, FigureDeNote::DoubleCroche},
        {Ds4, FigureDeNote::DoubleCroche},
        {As4, FigureDeNote::DoubleCroche},
        {G4, FigureDeNote::DoubleCroche},
        {Ds4, FigureDeNote::DoubleCroche},
        {As4, FigureDeNote::DoubleCroche},
        {G4, FigureDeNote::DoubleCroche},
        {D5, FigureDeNote::DoubleCroche},
        {D5, FigureDeNote::DoubleCroche},
        {D5, FigureDeNote::DoubleCroche},
        {Ds5, FigureDeNote::DoubleCroche},
        {As4, FigureDeNote::DoubleCroche},
        {Fs4, FigureDeNote::DoubleCroche},
        {Ds4, FigureDeNote::DoubleCroche},
        {As4, FigureDeNote::DoubleCroche},
        {G4, FigureDeNote::DoubleCroche},
        {G5, FigureDeNote::DoubleCroche},
        {G4, FigureDeNote::DoubleCroche},
        {G4, FigureDeNote::DoubleCroche},
        {G5, FigureDeNote::DoubleCroche},
        {Fs5, FigureDeNote::DoubleCroche},
        {F5, FigureDeNote::DoubleCroche},
        {E5, FigureDeNote::DoubleCroche},
        {Ds5, FigureDeNote::DoubleCroche},
        {E5, FigureDeNote::DoubleCroche},
        {0, FigureDeNote::DoubleCroche},
        {G4, FigureDeNote::DoubleCroche},
        {0, FigureDeNote::DoubleCroche},
        {Cs5, FigureDeNote::DoubleCroche},
        {C5, FigureDeNote::DoubleCroche},
        {B4, FigureDeNote::DoubleCroche},
        {As4, FigureDeNote::DoubleCroche},
        {A4, FigureDeNote::DoubleCroche},
        {As4, FigureDeNote::DoubleCroche},
        {0, FigureDeNote::DoubleCroche},
        {Ds4, FigureDeNote::DoubleCroche},
        {0, FigureDeNote::DoubleCroche},
        {Fs4, FigureDeNote::DoubleCroche},
        {Ds4, FigureDeNote::DoubleCroche},
        {As4, FigureDeNote::DoubleCroche},
        {G4, FigureDeNote::DoubleCroche},
        {Ds4, FigureDeNote::DoubleCroche},
        {As4, FigureDeNote::DoubleCroche},
        {G4, FigureDeNote::DoubleCroche}
    },
    Tempo::Vivace
};

ChansonMusique Chansons::twentieth = {
    73,
    {
        {62, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {62, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {58, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {62, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {59, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {62, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {63, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {62, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {63, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {62, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {62, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {62, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {53, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {62, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {62, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {58, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {62, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {62, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {58, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {58, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {60, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {62, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {62, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {62, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {58, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {48, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {48, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {55, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {55, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {58, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {51, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {51, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {53, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {62, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {58, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {60, FigureDeNote::TripleCroche},
        {0, FigureDeNote::TripleCroche},
        {62, FigureDeNote::TripleCroche}
    },
    Tempo::Prestissimo
};

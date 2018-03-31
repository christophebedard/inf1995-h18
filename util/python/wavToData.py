#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""

@author: Christophe Bourque Bedard
@date: 2018-03-29
"""
from __future__ import print_function # pour avoir print() de python 3
import sys
import itertools
import wave


# nombre de resultats par ligne
NB_VAL_PAR_LIGNE = 5


def wavToData(nom_fichier):
    """

    :param nom_fichier: le nom du fichier .wav
    """
    w = wave.open(nom_fichier, 'r')
    
    print("infos\n")
    print("nb channels  :", w.getnchannels())
    print("sample width :", w.getsampwidth())
    print("framerate    :", w.getframerate())
    print("nb frames    :", w.getnframes())
    print("compression  :", w.getcomptype())

    # get frames
    nb_frames = w.getnframes()
    frames = w.readframes(nb_frames)

    # conversion des frames en entiers
    frames_int = [ord(f) for f in frames]

    return frames_int


def formatWavData(data, file):
    print("\necriture dans le fichier :", file)
    with open(file, 'w') as f:
        print('const long pcm_length = ', len(data), ';', sep='', file=f)
        print(file=f)
        print('const unsigned char pcm_samples[] PROGMEM = {', file=f)
        for i, d in enumerate(data):
            # tab
            if (i % NB_VAL_PAR_LIGNE) == 0:
                print('\t', sep='', end='', file=f)
            
            # data
            print(d, sep='', end='', file=f)
            
            # separateur
            if i != len(data) - 1:
                if (i % NB_VAL_PAR_LIGNE) == (NB_VAL_PAR_LIGNE - 1):
                    print(',', file=f)
                else:
                    print(', ', sep='', end='', file=f)
            else:
                print(file=f)
        print('};', file=f)


def main():
    # verifie le nombre d'arguments
    narg = len(sys.argv)
    if narg <= 1:
        print("erreur : specifiez au moins le nom du fichier .wav avec l'extension")
    elif narg >= 2:
        # condition normale
        # parse les arguments des noms de fichier
        nom_fichier_wav = sys.argv[1]
        if narg == 2:
            nom_fichier_data = "samples.h"
        else:
            nom_fichier_data = sys.argv[2]

        # execute
        data = wavToData(nom_fichier_wav)
        formatWavData(data, nom_fichier_data)


if __name__ == "__main__":
    main()

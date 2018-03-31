#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Lecture d'un fichier .wav et formatage en 
fichier .h pour lecture avec le buzzer du robot
@author: Christophe Bourque Bedard
@date: 2018-03-29

Utilisation : python wav_to_data.py input.wav [output.h]
"""
from __future__ import print_function # pour avoir print() de python 3
import sys
import itertools
import wave
import librosa
import soundfile as sf


# taux d'echantillonnage voulu [Hz]
TAUX_ECHANTILLONNAGE = 8000
# nombre de resultats par ligne
NB_VAL_PAR_LIGNE = 5
# nom du fichier header des donnees exportees
NOM_FICHIER_DATA_DEFAULT = "wav_data.h"


def wav_to_data(nom_fichier):
    """
    Lecture du fichier et recuperation des donnees
    :param nom_fichier: le nom du fichier .wav
    :return: donnees
    """
    w = wave.open(nom_fichier, 'r')

    # verifie le sample rate
    if w.getframerate() != TAUX_ECHANTILLONNAGE:
        print("attention : taux d'echantillonnage !=", TAUX_ECHANTILLONNAGE, "Hz\n")
        """
        print("[re-echantillonnage a", TAUX_ECHANTILLONNAGE, "Hz]\n")
        w.close()
        nom_fichier_resampled = 's_' + nom_fichier
        # re-load et re-sample
        data, sample_rate = librosa.load(nom_fichier, sr=TAUX_ECHANTILLONNAGE, mono=True, res_type='scipy')
        # ecrit le fichier en WAV PCM unsigned 8 bit
        sf.write(nom_fichier_resampled, data, sample_rate, subtype='PCM_U8')
        # re-load le fichier pour continuer
        w = wave.open(nom_fichier_resampled, 'r')
        """

    print("infos\n")
    print("nb channels  :", w.getnchannels())
    print("sample width :", w.getsampwidth())
    print("framerate    :", w.getframerate())
    print("nb frames    :", w.getnframes())
    print("compression  :", w.getcomptype())

    # get frames
    nb_frames = w.getnframes()
    frames = w.readframes(nb_frames)
    w.close()

    # conversion des frames en entiers
    frames_int = [ord(f) for f in frames]

    return frames_int


def export_wav_data(data, nom_fichier_export):
    """
    Formatage des donnees pour ecriture dans un fichier
    :param data: donnees
    :param nom_fichier_export: nom du fichier d'exportation
    :
    """
    print("\necriture dans le fichier :", nom_fichier_export)
    with open(nom_fichier_export, 'w') as f:
        print('const uint16_t pcm_length = ', len(data), ';', sep='', file=f)
        print(file=f)
        print('const uint8_t pcm_samples[] PROGMEM = {', file=f)
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
        print("erreur : specifiez au moins le nom du fichier avec l'extension .wav")
    elif narg >= 2:
        # condition normale
        # parse les arguments des noms de fichier
        nom_fichier_wav = sys.argv[1]
        if narg == 2:
            nom_fichier_data = NOM_FICHIER_DATA_DEFAULT
        else:
            nom_fichier_data = sys.argv[2]

        # execute
        data = wav_to_data(nom_fichier_wav)
        export_wav_data(data, nom_fichier_data)


if __name__ == "__main__":
    main()

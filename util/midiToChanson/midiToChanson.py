#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Generation des NoteChanson selon un fichier MIDI
@author: Christophe Bourque Bedard
@date: 2018-03-26
"""
from __future__ import print_function # pour avoir print() de python 3
#import mido # https://mido.readthedocs.io/en/latest/
#import midi # https://github.com/vishnubob/python-midi
import iomidi
import itertools

# nom des enums correspondant aux Tempo
TEMPO_ENUMS_PREFIX = 'Tempo::'
TEMPO_ENUMS = ['Largo', 'Lento', 'Adagio', 'Andante', 'Moderato', 'Allegreto', 'Allegro', 'Vivace', 'Presto', 'Prestissimo']
TEMPO_ENUMS_VALEURS = [50.0, 60.0, 70.0, 88.0, 100.0, 114.0, 136.0, 140.0, 170.0, 188.0]
# nom des enums correspondant aux NoteMusicale
NOTE_MUSICALE_ENUMS_PREFIX = 'NoteMusicale::'
NOTE_MUSICALE_ENUMS = ['Carree', 'Ronde', 'Blanche', 'Noire', 'Croche', 'DoubleCroche', 'TripleCroche', 'QuadrupleCroche']
NOTE_MUSICALE_ENUMS_VALEURS = [8.0, 4.0, 2.0, 1.0, 0.5, 0.25, 0.125, 0.0625]
# nombre de resultats par ligne
NB_VAL_PAR_LIGNE = 5
# notes
MIN_NOTE = 12
MAX_NOTE = 127



def midi2Chanson(nom_fichier, nom_chanson, channel):
    """

    :param nom_fichier: le nom du fichier .mid
    :param channel: le channel voulu
    """
    midi = iomidi.read(nom_fichier)
    
    print("infos     :")
    print("nb tracks :", len(midi.tracks))
    print("track     :", channel)

    events = midi.tracks[channel].events

    #print(events)

    # filtre pour avoir seulement les iomidi.NoteOnEvent et iomidi.NoteOffEvent
    events = [e for e in events if isinstance(e, iomidi.NoteOnEvent) or isinstance(e, iomidi.NoteOffEvent)]

    # filtre pour prendre seulement les premiers events d'une suite d'events de meme type
    prev_event = None
    events_filtres = []
    for event in events:
        # si il n'y a pas de previous event ou si l'event courant est egal au precedent
        if (prev_event is None) or not (isinstance(prev_event, iomidi.NoteOnEvent) and isinstance(event, iomidi.NoteOnEvent) or isinstance(prev_event, iomidi.NoteOffEvent) and isinstance(event, iomidi.NoteOffEvent)):
            events_filtres.append(event)            
        prev_event = event
    events = events_filtres

    # calcule le temps et recupere les notes
    durees = []
    notes = []
    prev_delta = None
    for event in events:
        if prev_delta is not None:
            durees.append(event.delta)
        
        if isinstance(event, iomidi.NoteOnEvent):
            notes.append(event.key)
        if isinstance(event, iomidi.NoteOffEvent):
            notes.append(0)

        prev_delta = event.delta
    
    # enleve derniere note
    notes.pop()

    print()

    # print data
    espaces_tab = "    "
    print("ChansonMusique Chansons::", nom_chanson, " = {", sep="")
    print(espaces_tab,  len(notes), ",", sep="")
    print(espaces_tab,  "{", sep="")
    for i in range(0, len(durees)):
        # \todo choisir la bonne mesure  
        #print("{", notes[i], ", ", durees[i], "},", sep="")
        print(espaces_tab, espaces_tab, "{", notes[i], ", ", "NoteMusicale::TripleCroche", "}", sep="", end="")
        
        # print une virgule si pas la derniere note
        if i == (len(durees) - 1):
            print()
        else:
            print(",")
    print(espaces_tab,  "},", sep="")
    print(espaces_tab,  "Tempo::Prestissimo", sep="")
    print("};", sep="")

def main():
    midi2Chanson("Movie_Themes_-_20th_Century_Fox.mid", "twentieth", 2)
    #midi2Chanson("Main_Title_The_Imperial_March_Darth_Vaders_Theme.mid", "imperialMarch", 6)


if __name__ == "__main__":
    main()

#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Generation des valeurs pour le registre OCRn et le prescaler pour les notes MIDI
@author: Christophe Bourque Bedard
@date: 2018-03-24
"""
from __future__ import print_function # pour avoir print() de python 3


# CONSTANTES
# frequence du CPU
F_CPU = 8000000.0
# s --> ms
SECOND_TO_MILLISECOND = 1000.0
# s --> us
SECOND_TO_MICROSECOND = 1000000.0
# valeurs de prescalers disponibles
PRESCALERS = [1, 8, 32, 64, 128, 256, 1024]
# nom des enums correspondant aux valeurs de prescalers
PRESCALERS_ENUMS_PREFIX = 'Prescaler::'
PRESCALERS_ENUMS = ['Div_1', 'Div_8', 'Div_32', 'Div_64', 'Div_128', 'Div_256', 'Div_1024']
# nombre de bits du registre
NB_BITS = 8
# valeur maximale pour OCRn (8 bits)
OCRN_MAX = 2**NB_BITS - 1
# nombre de resultats par ligne
NB_VAL_PAR_LIGNE = 5
# notes
MIN_NOTE = 12
MAX_NOTE = 127


def frequenceSelonNote(note):
    """
    Calcule la frequence correspondant a la note MIDI
    :param note: la note MIDI
    :return: la frequence correspondante
    """
    return (2.0 ** ((note - 69.0) / 12.0) * 440.0)


def demiPeriodeSelonNote(note, facteur_conversion=SECOND_TO_MILLISECOND):
    """
    Calcule la demi periode correspondant a la note MIDI
    :param note: la note MIDI
    :return: la demi periode correspondante (en millisecondes)
    """
    return facteur_conversion * (1.0 / frequenceSelonNote(note)) / 2.0


def valeurOCRnSelonDemiPeriodeEtPrescaler(demi_periode, prescaler):
    """
    Calcule la valeur du registre OCRn correspondant a la demi periode et au prescaler
    :param demi_periode: la demi periode (en millisecondes)
    :param prescaler: la valeur choisie pour le prescaler
    :return: la valeur du registre OCRn
    """
    return (demi_periode / SECOND_TO_MILLISECOND) * (F_CPU / prescaler)


def main():
    notes = range(MIN_NOTE, MAX_NOTE+1)

    pres_choisis = []
    val_ocrn_choisies = []

    # pour chaque note, effectue les calculs necessaires
    for note in notes:
        # calcule la frequence et la demi periode
        freq = frequenceSelonNote(note)
        demi_periode = demiPeriodeSelonNote(note)
        print('note = ', note, '; frequence = ', freq, '; demi_periode = ', demi_periode, sep='')

        # cherche les valeurs de prescaler valides
        print('prescalers valides (valeur de OCRn) :')
        pres_valides = []
        val_ocrn_valides = []
        # pour chaque valeur de prescaler possible
        for pre in PRESCALERS:
            # calcule valeur de OCRn correspondante
            val_ocrn = valeurOCRnSelonDemiPeriodeEtPrescaler(demi_periode, pre)
            # si valeur est valide et qu'on a pas encore trouve une valeur
            if val_ocrn < OCRN_MAX and val_ocrn >= 1.0:
                pres_valides.append(pre)
                val_ocrn_valides.append(val_ocrn)
                print('\t', pre, ' (', val_ocrn, '), ', sep='')
        
        # identifie une valeur de prescaler choisie
        # (on veut selectionner le prescaler le plus 
        #  bas afin d'avoir une resolution plus elevee)
        pres_choisis.append(min(pres_valides))
        val_ocrn_choisies.append(max(val_ocrn_valides))

        print()

    # genere le resultat final
    for note in notes:
        index_note = note - MIN_NOTE

        # recuperation du nom de l'enum correspondant a la valeur du prescaler
        enum_pres = PRESCALERS_ENUMS[PRESCALERS.index(pres_choisis[index_note])]
        # recuperation de la valeur entiere de OCRn
        val_ocrn = int(val_ocrn_choisies[index_note])

        print('{', PRESCALERS_ENUMS_PREFIX, enum_pres, ', ', val_ocrn,'}', sep='', end='')
        if (index_note % NB_VAL_PAR_LIGNE) == (NB_VAL_PAR_LIGNE - 1):
            print(',')
        else:
            print(', ', sep='', end='')
    
    print()


if __name__ == "__main__":
    main()

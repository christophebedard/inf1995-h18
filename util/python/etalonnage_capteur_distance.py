#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Etalonnage du capteur de distance dans le but d'ameliorer la lecture

Etapes :
    1. prise de donnees avec une regle et un capteur
        (distance [cm], valeur CAN)
    2. interpolation pour trouver une equation
    3. discretisation

@author: Christophe Bourque Bedard
@date: 2018-04-12
"""
from __future__ import print_function # pour avoir print() de python 3
import numpy as np
import matplotlib.pyplot as plt
import itertools
# donnees
from data_capteurs_distance import data_datasheet, data_mesures_raw, data_mesures_valides, data_mesures_invalides


def fit(degre, data, data_invalides):
    # separe les donnees
    val_can = data[:,0]
    distance = data[:,1]

    # polyfit
    fit = np.polyfit(val_can, distance, degre)
    eq = np.poly1d(fit)

    # calcul des valeurs interpolees
    val_can_fit = np.linspace(val_can[0], val_can[-1], 50)
    distance_fit = eq(val_can_fit)
    # formule specifique
    distance_formule = (6787.0 / (val_can_fit - 3.0)) - 4.0

    # plot
    plt.plot(val_can, distance, 'o-', label='mesures')
    plt.plot(val_can_fit, distance_fit, 'g', label='interpolation deg '+str(degre))
    plt.plot(val_can_fit, distance_formule, 'b-.', label='formule')
    plt.plot(data_invalides[:,0], data_invalides[:,1], 'o-r', label='mesures invalides')
    plt.xlim([0, 750.0])
    plt.ylim([0, 90.0])
    plt.title("degre = " + str(degre), fontsize=12)
    plt.xlabel("valeur CAN [0, 1023]")
    plt.ylabel("distance (cm)")
    plt.legend(loc="upper right", fontsize=8)
    plt.grid()
    
    # infos
    print("degre            =", degre)
    print("coefs            =", fit)
    print("equation         =\n", eq)
    print()


def multi_fit(degrees, data, data_invalides):
    num_plots = len(degrees)
    num_rows = 1
    num_cols = num_plots

    fig = plt.figure()
    fig.suptitle("Interpolation des donnees distance/valeur CAN", fontsize=16)

    # subplots
    for idx, degre in enumerate(degrees):
        plt.subplot(num_rows, num_cols, idx+1)
        fit(degre, data, data_invalides)

    # affiche a la fin
    plt.show()


def fit_data(degre, data):
    # separe les donnees
    x = data[:,0]
    y = data[:,1]

    # polyfit
    fit = np.polyfit(x, y, degre)
    eq = np.poly1d(fit)

    # calcul des valeurs interpolees
    #x_fit = np.linspace(min(x), max(x), max(x)-min(x)+1)
    x_min = 150
    x_max = 480
    x_fit = np.linspace(x_min, x_max, x_max - x_min + 1)
    y_fit = eq(x_fit)
    data_fit = np.column_stack((x_fit, y_fit))

    return data_fit


def plot_data(degre, data, data_invalides, data_fit):
    # separe les donnees
    val_can = data[:,0]
    distance = data[:,1]

    # calcul des valeurs interpolees
    val_can_fit = data_fit[:,0]
    distance_fit = data_fit[:,1]
    # formule specifique
    distance_formule = (6787.0 / (val_can_fit - 3.0)) - 4.0

    # plot
    plt.rc('text', usetex=True)
    plt.rc('font', family='serif')
    plt.title(r'Interpolation des donn\'ees distance/valeur CAN', fontsize=20)
    plt.plot(val_can, distance, 'o-', label=r'mesures')
    plt.plot(data_invalides[:,0], data_invalides[:,1], 'o-r', label=r'mesures invalides')
    plt.plot(val_can_fit, distance_fit, 'g', label=r'interpolation degr\'e '+str(degre), linewidth=2.0)
    plt.plot(val_can_fit, distance_formule, 'b-.', label=r'formule courante', linewidth=2.0)
    plt.xlim([150.0, 750.0])
    plt.ylim([0, 90.0])
    plt.xlabel(r'valeur CAN', fontsize=17)
    plt.ylabel(r'distance (cm)', fontsize=17)
    plt.legend(loc="upper right", fontsize=17)
    plt.grid()

    # affiche
    plt.show()


def export_data_fit(data_fit, nom):
    nom_fichier_export = nom + ".h"
    print("\necriture dans le fichier :", nom_fichier_export)
    with open(nom_fichier_export, 'w') as f:
        print('switch (canVal)', file=f)
        print('{', file=f)
        for i, data in enumerate(data_fit):
            # data
            print('\tcase ', int(data[0]), ': *dist = ', int(data[1]), '; break;', sep='', end='', file=f)
            
            print(file=f)
        print('}', file=f)


def main():
    #multi_fit([3, 4, 5, 6, 7, 8, 9], data_mesures_valides, data_mesures_invalides)
    data_fit = fit_data(7, data_mesures_valides)
    plot_data(7, data_mesures_valides, data_mesures_invalides, data_fit)
    export_data_fit(data_fit, 'interpolation')


if __name__ == "__main__":
    main()

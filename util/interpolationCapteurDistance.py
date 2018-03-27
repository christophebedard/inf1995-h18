#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Interpolation des donnees du graphique distance/voltage
dans le but de trouver une equation pour faire la correspondance

@author: Christophe Bourque Bedard
@date: 2018-03-27
"""
from __future__ import print_function # pour avoir print() de python 3
import numpy as np
import matplotlib.pyplot as plt
import itertools


# selon le graphique dans la datasheet du capteur
#   (voltage, distance)
data = np.array([(2.6, 10),
                 (2.45, 11),
                 (2.12, 12),
                 (1.87, 14),
                 (1.66, 16),
                 (1.51, 18),
                 (1.39, 20),
                 (1.13, 25),
                 (0.97, 30),
                 (0.85, 35),
                 (0.75, 40),
                 (0.67, 45),
                 (0.61, 50),
                 (0.58, 55),
                 (0.52, 60),
                 (0.50, 65),
                 (0.48, 70),
                 (0.44, 75),
                 (0.41, 80)])

def fit(degre):
    # separe les donnees
    voltage = data[:,0]
    distance = data[:,1]

    # polyfit
    fit = np.polyfit(voltage, distance, degre)
    eq = np.poly1d(fit)

    # calcul des valeurs interpolees
    voltage_fit = np.linspace(voltage[0], voltage[-1], 50)
    distance_fit = eq(voltage_fit)

    # plot
    plt.plot(voltage, distance, 'o', voltage_fit, distance_fit)
    plt.xlim([0, 3.0])
    plt.ylim([0, 90.0])
    plt.title("degre = " + str(degre), fontsize=12)
    plt.xlabel("voltage (V)")
    plt.ylabel("distance (cm)")
    plt.grid()
    
    # infos
    print("degre    =", degre)
    print("coefs    =", fit)
    print("equation =\n", eq)
    print()


def multi_fit(degrees):
    num_plots = len(degrees)
    num_rows = 1
    num_cols = num_plots

    fig = plt.figure()
    fig.suptitle("Interpolation des donnees distance/voltage de la datasheet", fontsize=16)

    # subplots
    for idx, degre in enumerate(degrees):
        plt.subplot(num_rows, num_cols, idx+1)
        fit(degre)

    # affiche a la fin
    plt.show()


def main():
    multi_fit([1, 2, 3, 4])


if __name__ == "__main__":
    main()

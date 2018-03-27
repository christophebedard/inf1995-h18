#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Interpolation des donnees du graphique distance/voltage
@author: Christophe Bourque Bedard
@date: 2018-03-27
"""
from __future__ import print_function # pour avoir print() de python 3
import numpy as np
import matplotlib.pyplot as plt

# selon la datasheet du capteur
data = np.array([(1, 1), (2, 4), (3, 1), (9, 3)])

def frequenceSelonNote(note):
    """
    Calcule la frequence correspondant a la note MIDI
    :param note: la note MIDI
    :return: la frequence correspondante
    """
    return (2.0 ** ((note - 69.0) / 12.0) * 440.0)



def main():
    # get x and y vectors
    x = data[:,0]
    y = data[:,1]

    # calculate polynomial
    z = np.polyfit(x, y, 2)
    f = np.poly1d(z)

    # calculate new x's and y's
    x_new = np.linspace(x[0], x[-1], 50)
    y_new = f(x_new)

    plt.plot(x,y,'o', x_new, y_new)
    plt.xlim([x[0]-1, x[-1] + 1 ])
    plt.show()


if __name__ == "__main__":
    main()

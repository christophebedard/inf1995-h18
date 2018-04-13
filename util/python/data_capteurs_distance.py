#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Donnees du capteurs de distance

@author: Christophe Bourque Bedard
@date: 2018-04-12
"""
import numpy as np

# - selon le graphique dans la datasheet du capteur (pour comparaison)
#   (voltage, distance)
data_datasheet = np.array([(2.6, 10),
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

# - selon des mesures a la main
#   (valeur CAN, distance)
data_mesures_raw = np.array([(401, 0),
                             (637, 1),
                             (702, 2),
                             (752, 3),
                             (741, 4),
                             (694, 5),
                             (633, 6),
                             (575, 7),
                             (525, 8),
                             (485, 9),
                             (450, 10),
                             (424, 11),
                             (392, 12),
                             (365, 13),
                             (347, 14),
                             (326, 15),
                             (315, 16),
                             (302, 17),
                             (292, 18),
                             (275, 19),
                             (265, 20),
                             (251, 21),
                             (242, 22),
                             (235, 23),
                             (228, 24),
                             (219, 25),
                             (214, 26),
                             (208, 27),
                             (204, 28),
                             (200, 29),
                             (202, 30),
                             (198, 31),
                             (195, 32),
                             (189, 33),
                             (186, 34),
                             (186, 35),
                             (188, 36),
                             (189, 37),
                             (186, 38),
                             (186, 39),
                             (185, 40),
                             (188, 41),
                             (191, 42),
                             (190, 43),
                             (191, 44),
                             (195, 45),
                             (196, 46),
                             (199, 47),
                             (199, 48),
                             (196, 49),
                             (195, 50),
                             (200, 51),
                             (195, 52),
                             (191, 53),
                             (186, 54),
                             (186, 55),
                             (186, 56),
                             (189, 57),
                             (186, 58),
                             (189, 59),
                             (190, 60),
                             (186, 61),
                             (189, 62),
                             (190, 63),
                             (194, 64),
                             (193, 65),
                             (191, 66),
                             (194, 67),
                             (199, 68),
                             (197, 69),
                             (195, 70),
                             (194, 71),
                             (192, 72),
                             (190, 73),
                             (189, 74),
                             (186, 75),
                             (185, 76),
                             (183, 77),
                             (180, 78),
                             (179, 79),
                             (172, 80)])

# valides : toutes sauf les distances de 0 a 9 cm
data_mesures_valides = data_mesures_raw[10:]
#data_mesures_valides = data_mesures_raw[10:60]
# invalides : les distances de 0 a 9 cm
data_mesures_invalides = data_mesures_raw[:10]
#data_mesures_invalides = np.concatenate((data_mesures_raw[:10], data_mesures_raw[61:]), axis=0)

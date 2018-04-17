/**
 * \file capteurs_distance.cpp
 * \brief implementation de la classe CapteursDistance
 * \author 
 */

#include "capteurs_distance.h"


can CapteursDistance::can_;
uint16_t CapteursDistance::memCanGauche[LONGUEUR_MEMOIRE_LECTURES];
uint16_t CapteursDistance::memCanDroit[LONGUEUR_MEMOIRE_LECTURES];
uint16_t CapteursDistance::totalCanGauche = 0;
uint16_t CapteursDistance::totalCanDroit = 0;
uint8_t CapteursDistance::indexCanGauche = 0;
uint8_t CapteursDistance::indexCanDroit = 0;

void CapteursDistance::init()
{
    // mettre les pins des CANs en entree
	DDRA &= ~(_BV(_BROCHE_TO_PIN(BROCHE_CAPTEUR_DISTANCE_GAUCHE)));
	DDRA &= ~(_BV(_BROCHE_TO_PIN(BROCHE_CAPTEUR_DISTANCE_DROIT)));
}

bool CapteursDistance::getDistanceGauche(uint8_t* dist)
{
    return canToDistance(ajoutNouvelleLecture(can_.lecture(_BROCHE_TO_PIN(BROCHE_CAPTEUR_DISTANCE_GAUCHE)),
                                              memCanGauche,
                                              indexCanGauche,
                                              totalCanGauche),
                         dist);
}

bool CapteursDistance::getDistanceDroit(uint8_t* dist)
{
    return canToDistance(ajoutNouvelleLecture(can_.lecture(_BROCHE_TO_PIN(BROCHE_CAPTEUR_DISTANCE_DROIT)),
                                              memCanDroit,
                                              indexCanDroit,
                                              totalCanDroit),
                         dist);
}

bool CapteursDistance::isDistanceValide(uint8_t* dist)
{
    return (CAPTEUR_DISTANCE_MIN <= *dist
                                 && *dist <= CAPTEUR_DISTANCE_MAX);
}

uint16_t CapteursDistance::ajoutNouvelleLecture(uint16_t lectCan, uint16_t* memCan, uint8_t& indexMemCan, uint16_t& totCan)
{
    // selon le principe de rolling average
    // https://en.wikipedia.org/wiki/Moving_average#Simple_moving_average
    // nouveau total = ancien total + nouvelle lecture - plus vieille lecture
    // nouvelle valeur = nouveau total / n
    totCan -= memCan[indexMemCan];
    totCan += lectCan;
    memCan[indexMemCan] = lectCan;
    indexMemCan = (indexMemCan < (LONGUEUR_MEMOIRE_LECTURES - 1)) ? (indexMemCan + 1) : 0;
    return (uint16_t)((double)totCan / (double)LONGUEUR_MEMOIRE_LECTURES);
}

void CapteursDistance::formatDistance(uint8_t* dist)
{
    // si la distance est plus petite que le minimum, on lui donne 0
    // si la distance est plus grande que le maximum, on lui donne le maximum
    // sinon, on ne la modifie pas
    *dist = (CAPTEUR_DISTANCE_MIN <= *dist)
             ? ((*dist <= CAPTEUR_DISTANCE_FORMAT_MAX) ? *dist : CAPTEUR_DISTANCE_FORMAT_MAX)
               : CAPTEUR_DISTANCE_FORMAT_MIN;
}

bool CapteursDistance::canToDistance(uint16_t canVal, uint8_t* dist)
{
    // voir util/python/etalonnage_capteur_distance.py
    
    // verification validite
    bool isValide = false;
    if (!(CAPTEUR_DISTANCE_CAN_VAL_MIN <= canVal && canVal <= CAPTEUR_DISTANCE_CAN_VAL_MAX))
    {
        // invalide, donner une valeur de distance adequate
        // (pour savoir si la distance est tres grande ou tres petite)
        if (canVal < CAPTEUR_DISTANCE_CAN_VAL_MIN)
        {
            *dist = CAPTEUR_DISTANCE_CAN_VAL_INVALIDE_MIN;
        }
        else
        {
            *dist = CAPTEUR_DISTANCE_CAN_VAL_INVALIDE_MAX;
        }
    }
    else
    {
        // valide
        isValide = true;
        //*dist = ((6787.0 / ((double)canVal - 3.0)) - 4.0);
        // // convertir en distance
         switch (canVal)
         {
             case 150: *dist = 104; break;
             case 151: *dist = 103; break;
             case 152: *dist = 102; break;
            case 153: *dist = 101; break;
            case 154: *dist = 100; break;
            case 155: *dist = 99; break;
            case 156: *dist = 97; break;
            case 157: *dist = 96; break;
            case 158: *dist = 95; break;
            case 159: *dist = 94; break;
            case 160: *dist = 93; break;
            case 161: *dist = 91; break;
            case 162: *dist = 90; break;
            case 163: *dist = 89; break;
            case 164: *dist = 87; break;
            case 165: *dist = 86; break;
            case 166: *dist = 85; break;
            case 167: *dist = 83; break;
            case 168: *dist = 82; break;
            case 169: *dist = 81; break;
            case 170: *dist = 79; break;
            case 171: *dist = 78; break;
            case 172: *dist = 77; break;
            case 173: *dist = 75; break;
            case 174: *dist = 74; break;
            case 175: *dist = 73; break;
            case 176: *dist = 71; break;
            case 177: *dist = 70; break;
            case 178: *dist = 69; break;
            case 179: *dist = 67; break;
            case 180: *dist = 66; break;
            case 181: *dist = 65; break;
            case 182: *dist = 63; break;
            case 183: *dist = 62; break;
            case 184: *dist = 61; break;
            case 185: *dist = 60; break;
            case 186: *dist = 58; break;
            case 187: *dist = 57; break;
            case 188: *dist = 56; break;
            case 189: *dist = 55; break;
            case 190: *dist = 54; break;
            case 191: *dist = 53; break;
            case 192: *dist = 51; break;
            case 193: *dist = 50; break;
            case 194: *dist = 49; break;
            case 195: *dist = 48; break;
            case 196: *dist = 47; break;
            case 197: *dist = 46; break;
            case 198: *dist = 45; break;
            case 199: *dist = 44; break;
            case 200: *dist = 43; break;
            case 201: *dist = 42; break;
            case 202: *dist = 41; break;
            case 203: *dist = 40; break;
            case 204: *dist = 40; break;
            case 205: *dist = 39; break;
            case 206: *dist = 38; break;
            case 207: *dist = 37; break;
            case 208: *dist = 36; break;
            case 209: *dist = 36; break;
            case 210: *dist = 35; break;
            case 211: *dist = 34; break;
            case 212: *dist = 33; break;
            case 213: *dist = 33; break;
            case 214: *dist = 32; break;
            case 215: *dist = 31; break;
            case 216: *dist = 31; break;
            case 217: *dist = 30; break;
            case 218: *dist = 30; break;
            case 219: *dist = 29; break;
            case 220: *dist = 28; break;
            case 221: *dist = 28; break;
            case 222: *dist = 27; break;
            case 223: *dist = 27; break;
            case 224: *dist = 26; break;
            case 225: *dist = 26; break;
            case 226: *dist = 25; break;
            case 227: *dist = 25; break;
            case 228: *dist = 25; break;
            case 229: *dist = 24; break;
            case 230: *dist = 24; break;
            case 231: *dist = 23; break;
            case 232: *dist = 23; break;
            case 233: *dist = 23; break;
            case 234: *dist = 22; break;
            case 235: *dist = 22; break;
            case 236: *dist = 22; break;
            case 237: *dist = 22; break;
            case 238: *dist = 21; break;
            case 239: *dist = 21; break;
            case 240: *dist = 21; break;
            case 241: *dist = 21; break;
            case 242: *dist = 20; break;
            case 243: *dist = 20; break;
            case 244: *dist = 20; break;
            case 245: *dist = 20; break;
            case 246: *dist = 20; break;
            case 247: *dist = 20; break;
            case 248: *dist = 19; break;
            case 249: *dist = 19; break;
            case 250: *dist = 19; break;
            case 251: *dist = 19; break;
            case 252: *dist = 19; break;
            case 253: *dist = 19; break;
            case 254: *dist = 19; break;
            case 255: *dist = 19; break;
            case 256: *dist = 18; break;
            case 257: *dist = 18; break;
            case 258: *dist = 18; break;
            case 259: *dist = 18; break;
            case 260: *dist = 18; break;
            case 261: *dist = 18; break;
            case 262: *dist = 18; break;
            case 263: *dist = 18; break;
            case 264: *dist = 18; break;
            case 265: *dist = 18; break;
            case 266: *dist = 18; break;
            case 267: *dist = 18; break;
            case 268: *dist = 18; break;
            case 269: *dist = 18; break;
            case 270: *dist = 18; break;
            case 271: *dist = 18; break;
            case 272: *dist = 18; break;
            case 273: *dist = 18; break;
            case 274: *dist = 18; break;
            case 275: *dist = 18; break;
            case 276: *dist = 18; break;
            case 277: *dist = 18; break;
            case 278: *dist = 18; break;
            case 279: *dist = 18; break;
            case 280: *dist = 17; break;
            case 281: *dist = 17; break;
            case 282: *dist = 17; break;
            case 283: *dist = 17; break;
            case 284: *dist = 17; break;
            case 285: *dist = 17; break;
            case 286: *dist = 17; break;
            case 287: *dist = 17; break;
            case 288: *dist = 17; break;
            case 289: *dist = 17; break;
            case 290: *dist = 17; break;
            case 291: *dist = 17; break;
            case 292: *dist = 17; break;
            case 293: *dist = 17; break;
            case 294: *dist = 17; break;
            case 295: *dist = 17; break;
            case 296: *dist = 17; break;
            case 297: *dist = 17; break;
            case 298: *dist = 17; break;
            case 299: *dist = 17; break;
            case 300: *dist = 17; break;
            case 301: *dist = 17; break;
            case 302: *dist = 17; break;
            case 303: *dist = 17; break;
            case 304: *dist = 17; break;
            case 305: *dist = 17; break;
            case 306: *dist = 17; break;
            case 307: *dist = 17; break;
            case 308: *dist = 17; break;
            case 309: *dist = 17; break;
            case 310: *dist = 17; break;
            case 311: *dist = 16; break;
            case 312: *dist = 16; break;
            case 313: *dist = 16; break;
            case 314: *dist = 16; break;
            case 315: *dist = 16; break;
            case 316: *dist = 16; break;
            case 317: *dist = 16; break;
            case 318: *dist = 16; break;
            case 319: *dist = 16; break;
            case 320: *dist = 16; break;
            case 321: *dist = 16; break;
            case 322: *dist = 16; break;
            case 323: *dist = 16; break;
            case 324: *dist = 16; break;
            case 325: *dist = 15; break;
            case 326: *dist = 15; break;
            case 327: *dist = 15; break;
            case 328: *dist = 15; break;
            case 329: *dist = 15; break;
            case 330: *dist = 15; break;
            case 331: *dist = 15; break;
            case 332: *dist = 15; break;
            case 333: *dist = 15; break;
            case 334: *dist = 15; break;
            case 335: *dist = 15; break;
            case 336: *dist = 14; break;
            case 337: *dist = 14; break;
            case 338: *dist = 14; break;
            case 339: *dist = 14; break;
            case 340: *dist = 14; break;
            case 341: *dist = 14; break;
            case 342: *dist = 14; break;
            case 343: *dist = 14; break;
            case 344: *dist = 14; break;
            case 345: *dist = 14; break;
            case 346: *dist = 14; break;
            case 347: *dist = 13; break;
            case 348: *dist = 13; break;
            case 349: *dist = 13; break;
            case 350: *dist = 13; break;
            case 351: *dist = 13; break;
            case 352: *dist = 13; break;
            case 353: *dist = 13; break;
            case 354: *dist = 13; break;
            case 355: *dist = 13; break;
            case 356: *dist = 13; break;
            case 357: *dist = 13; break;
            case 358: *dist = 13; break;
            case 359: *dist = 12; break;
            case 360: *dist = 12; break;
            case 361: *dist = 12; break;
            case 362: *dist = 12; break;
            case 363: *dist = 12; break;
            case 364: *dist = 12; break;
            case 365: *dist = 12; break;
            case 366: *dist = 12; break;
            case 367: *dist = 12; break;
            case 368: *dist = 12; break;
            case 369: *dist = 12; break;
            case 370: *dist = 12; break;
            case 371: *dist = 12; break;
            case 372: *dist = 12; break;
            case 373: *dist = 12; break;
            case 374: *dist = 12; break;
            case 375: *dist = 12; break;
            case 376: *dist = 12; break;
            case 377: *dist = 11; break;
            case 378: *dist = 11; break;
            case 379: *dist = 11; break;
            case 380: *dist = 11; break;
            case 381: *dist = 11; break;
            case 382: *dist = 11; break;
            case 383: *dist = 11; break;
            case 384: *dist = 11; break;
            case 385: *dist = 11; break;
            case 386: *dist = 11; break;
            case 387: *dist = 11; break;
            case 388: *dist = 11; break;
            case 389: *dist = 11; break;
            case 390: *dist = 11; break;
            case 391: *dist = 11; break;
            case 392: *dist = 11; break;
            case 393: *dist = 11; break;
            case 394: *dist = 11; break;
            case 395: *dist = 11; break;
            case 396: *dist = 11; break;
            case 397: *dist = 11; break;
            case 398: *dist = 11; break;
            case 399: *dist = 11; break;
            case 400: *dist = 11; break;
            case 401: *dist = 11; break;
            case 402: *dist = 11; break;
            case 403: *dist = 11; break;
            case 404: *dist = 11; break;
            case 405: *dist = 11; break;
            case 406: *dist = 11; break;
            case 407: *dist = 11; break;
            case 408: *dist = 11; break;
            case 409: *dist = 11; break;
            case 410: *dist = 11; break;
            case 411: *dist = 11; break;
            case 412: *dist = 11; break;
            case 413: *dist = 11; break;
            case 414: *dist = 11; break;
            case 415: *dist = 11; break;
            case 416: *dist = 11; break;
            case 417: *dist = 11; break;
            case 418: *dist = 11; break;
            case 419: *dist = 11; break;
            case 420: *dist = 11; break;
            case 421: *dist = 11; break;
            case 422: *dist = 11; break;
            case 423: *dist = 11; break;
            case 424: *dist = 11; break;
            case 425: *dist = 11; break;
            case 426: *dist = 11; break;
            case 427: *dist = 11; break;
            case 428: *dist = 11; break;
            case 429: *dist = 11; break;
            case 430: *dist = 11; break;
            case 431: *dist = 11; break;
            case 432: *dist = 11; break;
            case 433: *dist = 11; break;
            case 434: *dist = 11; break;
            case 435: *dist = 11; break;
            case 436: *dist = 10; break;
            case 437: *dist = 10; break;
            case 438: *dist = 10; break;
            case 439: *dist = 10; break;
            case 440: *dist = 10; break;
            case 441: *dist = 10; break;
            case 442: *dist = 10; break;
            case 443: *dist = 10; break;
            case 444: *dist = 10; break;
            case 445: *dist = 10; break;
            case 446: *dist = 10; break;
            case 447: *dist = 10; break;
            case 448: *dist = 10; break;
            case 449: *dist = 9; break;
            case 450: *dist = 9; break;
            case 451: *dist = 9; break;
            case 452: *dist = 9; break;
            case 453: *dist = 9; break;
            case 454: *dist = 9; break;
            case 455: *dist = 9; break;
            case 456: *dist = 9; break;
            case 457: *dist = 9; break;
            case 458: *dist = 9; break;
            case 459: *dist = 8; break;
            case 460: *dist = 8; break;
            case 461: *dist = 8; break;
            case 462: *dist = 8; break;
            case 463: *dist = 8; break;
            case 464: *dist = 8; break;
            case 465: *dist = 8; break;
            case 466: *dist = 8; break;
            case 467: *dist = 8; break;
            case 468: *dist = 8; break;
            case 469: *dist = 7; break;
            case 470: *dist = 7; break;
            case 471: *dist = 7; break;
            case 472: *dist = 7; break;
            case 473: *dist = 7; break;
            case 474: *dist = 7; break;
            case 475: *dist = 7; break;
            case 476: *dist = 7; break;
            case 477: *dist = 7; break;
            case 478: *dist = 7; break;
            case 479: *dist = 7; break;
            case 480: *dist = 7; break;
        }
    }

    return isValide;
}

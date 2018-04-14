/**
 * \file time.cpp
 * \brief implementation de la classe Timer
 * \author 
 */

#include "time.h"


Time::Time()
	: dix_(0)
	  sec_(0)
	  min_(0)
{
}

Time::Time(uint8_t dix, uint8_t sec, uint8_t min)
	: dix_(dix)
	  sec_(sec)
	  min_(min)
{
}

Time::~Time()
{
}



void Time::tick()
{
	// incremente millisecondes
	relTime_.tm_dix++;
	// verifie overflow millisecondes
	if (relTime_.tm_dix >= TIME_NB_MS)
	{
		// reset millisecondes
		relTime_.tm_dix = 0;
		// incremente secondes
		relTime_.tm_sec++;
		// verifie overflow secondes
		if (relTime_.tm_sec >= TIME_NB_SEC)
		{
			// reset secondes
			relTime_.tm_sec = 0;
			// incremente minutes
			relTime_.tm_min++;
			// verifie overflow minutes
			if (relTime_.tm_min >= TIME_NB_MIN)
			{
				// reset minutes
				relTime_.tm_min = 0;
				// incremente heures
				relTime_.tm_heure++;
				// verifie overflow heures
				if (relTime_.tm_heure >= TIME_NB_HEU)
				{
					// reset heures
					relTime_.tm_heure = 0;
					// fin : pas de compteur pour jours
				}
			}
		}
	}
}

bool Time::operator>(Time d)
{
	/// \todo modifier

	// aditionne initTime et deltaTime
	tm_t addTime = add(initTime, deltaTime);

	// compare
	bool ecoule = false;
	if (refTime.tm_heure > addTime.tm_heure)
	{
		ecoule = true;
	}
	else
	{
		if (refTime.tm_min > addTime.tm_min)
		{
			ecoule = true;
		}
		else
		{
			if (refTime.tm_sec > addTime.tm_sec)
			{
				ecoule = true;
			}
			else
			{
				if (refTime.tm_dix > addTime.tm_dix)
				{
					ecoule = true;
				}
			}
		}
	}
	
	return ecoule;
}

Time& Time::operator+(Time d)
{
	/// \todo modifier

	tm_t res = tm(0, 0, 0, 0);

	/// \todo verifier

	// add millisecondes
	res.tm_dix = t1.tm_dix + t2.tm_dix;
	// verifie overflow ms
	if (res.tm_dix >= TIME_NB_MS)
	{
		res.tm_sec = res.tm_dix / TIME_NB_MS;
		res.tm_dix %= TIME_NB_MS;
	}

	// add secondes
	res.tm_sec += t1.tm_sec + t2.tm_sec;
	// verifie overflow sec
	if (res.tm_sec >= TIME_NB_SEC)
	{
		res.tm_min = res.tm_sec / TIME_NB_SEC;
		res.tm_sec %= TIME_NB_SEC;
	}

	// add minutes
	res.tm_min += t1.tm_min + t2.tm_min;
	// verifie overflow min
	if (res.tm_min >= TIME_NB_MIN)
	{
		res.tm_heure = res.tm_min / TIME_NB_MIN;
		res.tm_min %= TIME_NB_MIN;
	}

	// add heures
	res.tm_heure += t1.tm_heure + t2.tm_heure;
	// verifie overflow min
	if (res.tm_heure >= TIME_NB_HEU)
	{
		res.tm_heure = 0;
	}
}


tm_t Time::tm(uint8_t dix, uint8_t sec, uint8_t min, uint8_t heu)
{
	tm_t t;
	t.tm_dix = dix;
	t.tm_sec = sec;
	t.tm_min = min;
	t.tm_heure = heu;
	return t;
}

void Time::debug()
{
	Debug::out(t.tm_heure);
	Debug::out(":");
	Debug::out(t.tm_min);
	Debug::out(":");
	Debug::out(t.tm_sec);
	Debug::out(":");
	Debug::out(t.tm_dix);
	Debug::out("\n");
}

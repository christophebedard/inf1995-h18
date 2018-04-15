/**
 * \file time.cpp
 * \brief implementation de la classe Timer
 * \author 
 */

#include "time.h"


Time::Time()
{
	nDix_ = 0;
	nSec_ = 0;
	nMin_ = 0;
}

Time::Time(uint8_t dix, uint8_t sec, uint8_t min)
{
	nDix_ = dix;
	nSec_ = sec;
	nMin_ = min;
}

Time::Time(const Time& t)
{
	operator=(t);
}

Time::~Time()
{
}

void Time::tick()
{
	// incremente millisecondes
	nDix_++;

	// verifie overflow millisecondes
	if (nDix_ >= TIME_NB_DIX)
	{
		// reset millisecondes
		nDix_ = 0;
		// incremente secondes
		nSec_++;
		// verifie overflow secondes
		if (nSec_ >= TIME_NB_SEC)
		{
			// reset secondes
			nSec_ = 0;
			// incremente minutes
			nMin_++;
			// verifie overflow minutes
			if (nMin_ >= TIME_NB_MIN)
			{
				// reset minutes
				nMin_ = 0;
				// fin : pas de compteur pour heures
			}
		}
	}
}

Time& Time::operator=(const Time& t)
{
	if (&t != this)
	{
		nDix_ = t.nDix_;
		nSec_ = t.nSec_;
		nMin_ = t.nMin_;
	}

	return *this;
}

bool operator<(const Time& g, const Time& d)
{
	/// \todo modifier/valider
	Time cmp;

	bool resultat = false;
	if (g.nMin_ > d.nMin_)
	{
		resultat = true;
	}
	else
	{
		cmp.nSec_ += g.nSec_ + (d.nMin_ * TIME_NB_SEC);

		if (g.nSec_ > d.nSec_)
		{
			resultat = true;
		}
		else
		{
			cmp.nDix_ += g.nDix_ + (d.nSec_ * TIME_NB_DIX);

			if (g.nDix_ > d.nDix_)
			{
				resultat = true;
			}
		}
	}

	return resultat;
}

bool operator>(const Time& g, const Time& d) { return d < g; }
bool operator<=(const Time& g, const Time& d) { return !(g > d); }
bool operator>=(const Time& g, const Time& d) { return !(g < d); }

Time operator+(const Time& g, const Time& d)
{
	/// \todo modifier/verifier

	// creer un objet pour l'adition
	Time add;

	// add dixiemes de secondes
	add.nDix_ = g.nDix_ + d.nDix_;
	// verifie overflow dixiemes de secondes
	if (add.nDix_ >= TIME_NB_DIX)
	{
		add.nSec_ = add.nDix_ / TIME_NB_DIX;
		add.nDix_ %= TIME_NB_DIX;
	}

	// add secondes
	add.nSec_ += g.nSec_ + d.nSec_;
	// verifie overflow sec
	if (add.nSec_ >= TIME_NB_SEC)
	{
		add.nMin_ = add.nSec_ / TIME_NB_SEC;
		add.nSec_ %= TIME_NB_SEC;
	}

	// add minutes
	add.nMin_ += g.nMin_ + d.nMin_;
	// verifie overflow min
	if (add.nMin_ >= TIME_NB_MIN)
	{
		add.nMin_ %= TIME_NB_MIN;
	}

	return add;
}

Time& Time::operator++(int)
{
	tick();

	return *this;
}

uint8_t Time::getDix() const
{
	return nDix_;
}

uint8_t Time::getSec() const
{
	return nSec_;
}

uint8_t Time::getMin() const
{
	return nMin_;
}

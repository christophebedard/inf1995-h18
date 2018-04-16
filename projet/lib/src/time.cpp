/**
 * \file time.cpp
 * \brief implementation de la classe Time
 * \author 
 */

#include "time.h"

Time::Time()
{
	nDix_ = 0;
}

Time::Time(uint8_t dix, uint8_t sec, uint8_t min)
{
	// nombre total dixiemes
	// = nb dixiemes
	//   + (nb dixiemes/seconde * (nb secondes + (nb secondes/minutes * nb minutes)))
	nDix_ = (uint16_t)(dix + (TIME_NB_DIX * (sec + (TIME_NB_SEC * min))));
}

Time::Time(uint16_t dix)
{
	nDix_ = dix;
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
	// incremente dixiemes de seconde
	nDix_++;
}

Time& Time::operator=(const Time& t)
{
	if (&t != this)
	{
		nDix_ = t.nDix_;
	}

	return *this;
}

bool operator<(const Time& g, const Time& d) { return (g.nDix_ < d.nDix_); }
bool operator>(const Time& g, const Time& d) { return (g.nDix_ > d.nDix_); }
bool operator<=(const Time& g, const Time& d) { return (g.nDix_ <= d.nDix_); }
bool operator>=(const Time& g, const Time& d) { return (g.nDix_ >= d.nDix_); }

Time operator+(const Time& g, const Time& d)
{
	// add dixiemes de secondes
	return Time(g.nDix_ + d.nDix_);
}

Time& Time::operator++(int)
{
	tick();

	return *this;
}

uint16_t Time::getDixTotal() const
{
	return nDix_;
}

uint8_t Time::getDix() const
{
	// nb dixiemes = 
	//		nb dixiemes % (nb dixiemes / seconde)
	return (nDix_ % TIME_NB_DIX);
}

uint8_t Time::getSec() const
{
	// nb secondes = 
	//		(nb dixiemes % (nb dixiemes / minute)) / (nb dixiemes / seconde)
	return ((nDix_ % (TIME_NB_DIX * TIME_NB_SEC)) / TIME_NB_DIX);
}

uint8_t Time::getMin() const
{
	// nb minutes =
	//		nb dixiemes total / (nb dixiemes / minute)
	return (nDix_ / (TIME_NB_DIX * TIME_NB_SEC));
}

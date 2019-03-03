#ifndef HOUR_HPP
#define HOUR_HPP

#include <set>
#include "plane.hpp"

class Hour
{
	private:
	
	int hourTime;
	unsigned long long int uniqueHourTime;
	
	public:
	std::set<Plane*> planesPtrSet;
	
	Hour(){}
	
	Hour(unsigned long long int uniqueTime, int iHourTime)
	:uniqueHourTime(uniqueTime),
	hourTime(iHourTime)
	{
	}
	//Gets the unique hour time, in the format YYYYMMDDHH00
	unsigned long long int getUniqueHourTime() const
	{
		return uniqueHourTime;
	}
	//Compares two hours, and sees which one is earlier. Required for
	//sorting. Returns true if this is earlier, else false.
	//	h - the other hour
	bool operator<(const Hour& h) const
	{
		return uniqueHourTime<h.getUniqueHourTime();
	}
};

#endif

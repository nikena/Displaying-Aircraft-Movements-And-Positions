#ifndef PLANE_TIME_STAMP_HPP
#define PLANE_TIME_STAMP_HPP

#include "plane.hpp"
#include "earthAirportPrototype.hpp"
#include "hour.hpp"

class Hour;
class Plane;
const float altitudescale = 1.0/1000.0;
class PlaneTimeStamp {
	float latitude, longitude;
	float altitude;// altitude is measured in feet (imperial system)
	int time;
	unsigned long long int hourUnique;
public:
	float x,y,z;//The precalculated xyz values for rendering.
	void preCalculateXYZ()
	{
		const float earthRadius=earth.radius;
		const float curLat = latitude;
		const float curLong = longitude;
		const float cosDegLat = cosDeg(curLat);
		const float cosDegLong = cosDeg(curLong);
		const float sinDegLat = sinDeg(curLat);
		const float sinDegLong = sinDeg(curLong);
		const float h = earthRadius + altitudescale*altitude;
		x=(getXFromLatLongPreTrig(h, cosDegLat, cosDegLong, sinDegLat, sinDegLong));
		y=(getYFromLatLongPreTrig(h, cosDegLat, cosDegLong, sinDegLat, sinDegLong));
		z=(getZFromLatLongPreTrig(h, cosDegLat, cosDegLong, sinDegLat, sinDegLong));
	}
	void setLatLong(float la, float lo)
	{
		latitude = la;
		longitude = la;
		preCalculateXYZ();
	}

	float getLat() const{
		return latitude;
	}
	float getLong() const{
		return longitude;
	}
	float getAlt() const{
		return altitude;
	}
	void setTime(int t) {
		time = t;
	}
	int getTime() const{
		return time;
	}
	//Gets the unique hour time, in the format YYYYMMDDHH00
	unsigned long long int getUniqueHourTime() const
	{
		return hourUnique;
	}
	Hour* getCurHour(std::vector<Hour>& hourVector, std::map<unsigned long long int ,int>& posTimeHourIndexMap) const
	{
		return &(hourVector[posTimeHourIndexMap[hourUnique]]);
	}
	PlaneTimeStamp(float latnew,float longnew,float altnew,int timenew, unsigned long long int hUnique)
	:latitude(latnew),
	longitude(longnew),
	altitude(altnew),
	time(timenew),
	hourUnique(hUnique)
	{
		preCalculateXYZ();				
	}
	PlaneTimeStamp() {
		time = -1;
	}
};

#endif

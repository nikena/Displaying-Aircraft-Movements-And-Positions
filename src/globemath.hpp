#ifndef GLOBE_MATH_HPP
#define GLOBE_MATH_HPP

#ifdef __APPLE__
#include <cmath>
#endif

#define PI 3.14159265
#define toRads PI/180
#define cosDeg(num) cos(num*toRads)
#define sinDeg(num) sin(num*toRads)

float getXFromLatLong(double r, double latitude, double longitude)
{
	return r*cosDeg(latitude)*cosDeg(longitude);
};
float getYFromLatLong(double r, double latitude, double longitude)
{
	return r*cosDeg(latitude)*sinDeg(longitude);
};
float getZFromLatLong(double r, double latitude, double longitude)
{
	return r*sinDeg(latitude);
};
//The same methods, but with trigometry precalculated for efficiency
//Inline as well for optimisation
inline float getXFromLatLongPreTrig(float r, float cosDegLat, float cosDegLong, float sinDegLat, float sinDegLong)
{
	return r*cosDegLat*cosDegLong;
};
inline float getYFromLatLongPreTrig(float r, float cosDegLat, float cosDegLong, float sinDegLat, float sinDegLong)
{
	return r*cosDegLat*sinDegLong;
};
inline float getZFromLatLongPreTrig(float r, float cosDegLat, float cosDegLong, float sinDegLat, float sinDegLong)
{
	return r*sinDegLat;
};
#endif

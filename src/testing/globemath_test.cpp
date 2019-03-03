#include "testUtils.hpp"
#include "../globemath.hpp"


bool test_GlobeMath_getXFromLatLong()
{
	PRINT_TEST_START;
	if((int)getXFromLatLong(100,0,0)!=100)
	{
		std::cout<<"[1/3]";
		return false;
	}
	if((int)getXFromLatLong(100,30,30)!=75)
	{
		std::cout<<"[2/3]";
		return false;
	}
	if((int)getXFromLatLong(100,30,-90)!=0)
	{
		std::cout<<"[3/3]";
		return false;
	}
	return true;
}
bool test_GlobeMath_getYFromLatLong()
{	
	PRINT_TEST_START;
	if((int)getYFromLatLong(100,0,0)!=0)
	{
		std::cout<<"[1/3]";
		return false;
	}
	if((int)getYFromLatLong(100,30,30)!=43)
	{
		std::cout<<"[2/3]";
		return false;
	}
	if((int)getYFromLatLong(100,30,-90)!=-86)
	{
		std::cout<<"[3/3]";
		return false;
	}
	return true;
}
bool test_GlobeMath_getZFromLatLong()
{
	PRINT_TEST_START;
	if((int)getZFromLatLong(100,0,0)!=0)
	{
		std::cout<<"[1/3]";
		return false;
	}
	if((int)getZFromLatLong(100,30,30)!=50)
	{
		std::cout<<"[2/3]";
		return false;
	}
	if((int)getZFromLatLong(100,30,-90)!=50)
	{
		std::cout<<"[3/3]";
		return false;
	}
	return true;
}
bool test_GlobeMath_getXFromLatLong_PreTrig()
{
	PRINT_TEST_START;
	float cosDegLat=cosDeg(0);
	float sinDegLat=sinDeg(0);
	float cosDegLong=cosDeg(0);
	float sinDegLong=sinDeg(0);
	if((int)getXFromLatLongPreTrig(100,cosDegLat,cosDegLong,sinDegLat,sinDegLong)!=100)
	{
		std::cout<<"[1/3]";
		return false;
	}
	cosDegLat=cosDeg(30);
	sinDegLat=sinDeg(30);
	cosDegLong=cosDeg(30);
	sinDegLong=sinDeg(30);
	if((int)getXFromLatLongPreTrig(100,cosDegLat,cosDegLong,sinDegLat,sinDegLong)!=75)
	{
		std::cout<<"[2/3]";
		return false;
	}
	cosDegLat=cosDeg(30);
	sinDegLat=sinDeg(30);
	cosDegLong=cosDeg(-90);
	sinDegLong=sinDeg(-90);
	if((int)getXFromLatLongPreTrig(100,cosDegLat,cosDegLong,sinDegLat,sinDegLong)!=0)
	{
		std::cout<<"[3/3]";
		return false;
	}
	return true;
}
bool test_GlobeMath_getYFromLatLong_PreTrig()
{
	PRINT_TEST_START;
	float cosDegLat=cosDeg(0);
	float sinDegLat=sinDeg(0);
	float cosDegLong=cosDeg(0);
	float sinDegLong=sinDeg(0);
	if((int)getYFromLatLongPreTrig(100,cosDegLat,cosDegLong,sinDegLat,sinDegLong)!=0)
	{
		std::cout<<"[1/3]";
		return false;
	}
	cosDegLat=cosDeg(30);
	sinDegLat=sinDeg(30);
	cosDegLong=cosDeg(30);
	sinDegLong=sinDeg(30);
	if((int)getYFromLatLongPreTrig(100,cosDegLat,cosDegLong,sinDegLat,sinDegLong)!=43)
	{
		std::cout<<"[2/3]";
		return false;
	}
	cosDegLat=cosDeg(30);
	sinDegLat=sinDeg(30);
	cosDegLong=cosDeg(-90);
	sinDegLong=sinDeg(-90);
	if((int)getYFromLatLongPreTrig(100,cosDegLat,cosDegLong,sinDegLat,sinDegLong)!=-86)
	{
		std::cout<<"[3/3]";
		return false;
	}
	return true;
}
bool test_GlobeMath_getZFromLatLong_PreTrig()
{
		PRINT_TEST_START;
	float cosDegLat=cosDeg(0);
	float sinDegLat=sinDeg(0);
	float cosDegLong=cosDeg(0);
	float sinDegLong=sinDeg(0);
	if((int)getZFromLatLongPreTrig(100,cosDegLat,cosDegLong,sinDegLat,sinDegLong)!=0)
	{
		std::cout<<"[1/3]";
		return false;
	}
	cosDegLat=cosDeg(30);
	sinDegLat=sinDeg(30);
	cosDegLong=cosDeg(30);
	sinDegLong=sinDeg(30);
	if((int)getZFromLatLongPreTrig(100,cosDegLat,cosDegLong,sinDegLat,sinDegLong)!=50)
	{
		std::cout<<"[2/3]";
		return false;
	}
	cosDegLat=cosDeg(30);
	sinDegLat=sinDeg(30);
	cosDegLong=cosDeg(-90);
	sinDegLong=sinDeg(-90);
	if((int)getZFromLatLongPreTrig(100,cosDegLat,cosDegLong,sinDegLat,sinDegLong)!=50)
	{
		std::cout<<"[3/3]";
		return false;
	}
	return true;
}
void test_GlobeMath()
{
	std::cout<<__FILE__<<":\n";numFilesTested++;
	printIfOK(test_GlobeMath_getXFromLatLong());
	printIfOK(test_GlobeMath_getYFromLatLong());
	printIfOK(test_GlobeMath_getZFromLatLong());
	printIfOK(test_GlobeMath_getXFromLatLong_PreTrig());
	printIfOK(test_GlobeMath_getYFromLatLong_PreTrig());
	printIfOK(test_GlobeMath_getZFromLatLong_PreTrig());
}

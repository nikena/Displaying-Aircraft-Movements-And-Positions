#ifndef PLANE_HPP
#define PLANE_HPP

#include "planeTimeStamp.hpp"
class PlaneTimeStamp;
class Plane {
	std::string id;
	public:
	std::vector<PlaneTimeStamp> timeStamps;
	float redColor=(20.0+rand()%80)/100.0;
	float greenColor=(20.0+rand()%80)/100.0;
	float blueColor=(20.0+rand()%80)/100.0;
	
	//Returns the string ID of this plane.
	std::string getID() const{
		return id;
	}
	//Sets the string ID of this plane.
	//	newid - the new ID to be set.
	void setID(std::string newid){
		id = newid;
	}
	
	Plane(std::string newid)
	:id(newid)
	{
	}
	Plane()
	:id("")
	{
	}
};
#endif

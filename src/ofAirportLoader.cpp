#include "earth.hpp"
#include "ofAirportLoader.hpp"
#ifdef __APPLE__
#include <iostream>
#endif
//Calls getline for values that are surrounded by quotes that may contain the delimiter.
//Will NOT work if the delimiter is a quote.
void getQuotedStrLine(std::ifstream& file,std::string& varStr,char delimiter)
{
	std::getline(file,varStr,delimiter);
	std::string quoteChar("\"");
	while(varStr.compare(varStr.length()-1,1,quoteChar)!=0)
	{
		std::string tempstr;				
		std::getline(file,tempstr,delimiter);
		varStr = varStr + tempstr;
	}
}
void getAirportVerticesAsPoints(float output[MAX_AIRPORT_COORDS_BUFFER*3/2], double radius)
{
	double r=radius;
	int a = 0;
	int o = 0;
	for(a=0;a<numAirportCoords;a+=2)
	{
		output[o++]=getXFromLatLong(r,airportCoords[a],airportCoords[a+1]);
		output[o++]=getYFromLatLong(r,airportCoords[a],airportCoords[a+1]);
		output[o++]=getZFromLatLong(r,airportCoords[a],airportCoords[a+1]);
	}
}
//A parser for the open flights data loading in airport locations into airportCoords[],
//And storing the number of airport lat/long coordinates in numAirportCoords
//As such, numAirportCoords should be numAirportCoords*2
void airportParser(std::string filelocation)
{
	std::ifstream airports(filelocation);
	std::string strLine;
    if(!airports)
    {
		std::cout << "Could not open "<<filelocation<<"\n";
		std::cout << "Have you tried passing in the location from /Data Files/openflights/airports.dat as an argument?\n";
		std::cout << "It can be retrieved from From https://openflights.org/data.html\n";
	}else
	{
		int numEntries=0;
		int currEntry=0;
		while(std::getline(airports,strLine))
		{
			numEntries++;
		}
		airports.clear();
		airports.seekg(0);//restart from top.
		float coords[MAX_AIRPORT_COORDS_BUFFER];
		while(!airports.eof())
		{
			std::string airportId;
			std::string name;
			std::string city;
			std::string country;
			std::string iata;
			std::string icao;
			std::string latitude;
			std::string longitude;
			std::string altitude;
			std::string timezone;
			std::string dst;
			std::string tz;
			std::string type;
			std::string source;					
			
			std::getline(airports,airportId,',');
			if(airportId.length()==0)
				break;
			
			getQuotedStrLine(airports,name,',');
			getQuotedStrLine(airports,city,',');
			getQuotedStrLine(airports,country,',');
			std::getline(airports,iata,',');
			std::getline(airports,icao,',');
			std::getline(airports,latitude,',');
			std::getline(airports,longitude,',');
			std::getline(airports,altitude,',');
			std::getline(airports,timezone,',');
			std::getline(airports,dst,',');
			std::getline(airports,tz,',');
			std::getline(airports,type,',');
			std::getline(airports,source,'\n');

			double lav = std::stod(latitude);
			double lov = std::stod(longitude);
			coords[currEntry++]=lav;
			coords[currEntry++]=lov;
		}
		airports.close();

		int a;
		numAirportCoords=numEntries*2;

		for(a=0;a<numAirportCoords;a+=1)
		{
			if(a%1000==0)
			std::cout << "Copying[" << a << "]/[" << numAirportCoords << "]\n";
			airportCoords[a]=coords[a];
		}
		std::cout << "Done copying...\n";
	}
}

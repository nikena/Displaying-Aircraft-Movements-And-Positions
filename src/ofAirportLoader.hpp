#ifndef OF_AIRPORT_LOADER_HPP
#define OF_AIRPORT_LOADER_HPP

#define MAX_AIRPORT_COORDS_BUFFER 20000
int numAirportCoords=MAX_AIRPORT_COORDS_BUFFER;
float airportCoords[MAX_AIRPORT_COORDS_BUFFER];
//Calls getline for values that are surrounded by quotes that may contain the delimiter.
//Will NOT work if the delimiter is a quote.
void getQuotedStrLine(std::ifstream& file,std::string& varStr,char delimiter);
void getAirportVerticesAsPoints(float output[MAX_AIRPORT_COORDS_BUFFER*3/2], double radius);
//A parser for the open flights data loading in airport locations into airportCoords[],
//And storing the number of airport lat/long coordinates in numAirportCoords
//As such, numAirportCoords should be numAirportCoords*2
void airportParser(std::string filelocation);

#endif

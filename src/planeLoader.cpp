#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#include "planeTimeStamp.hpp"
#include "planeLoader.hpp"
#include "stringUtils.hpp"
#include "earthAirportPrototype.hpp"

void getPlaneVerticesAsPoints(std::vector<float>& airplaneCoordVec, Earth& earth, int curPlaneTimeSegment,int curHourTimeSegment)
{
	int indexCount = 0;
	airplaneCoordVec.clear();//Doesn't free memory, but removes items - so don't need to reserve in subsequent calls.
	indicesPlaneVector.clear();
	int a = 0;
	int o = 0;
	Hour curHour;
	
	//for(int hourTimeSegment=curHourTimeSegment-1;hourTimeSegment<=curHourTimeSegment;hourTimeSegment++)
	for(int hourTimeSegment=curHourTimeSegment;hourTimeSegment<=curHourTimeSegment;hourTimeSegment++)
	{
		try
		{
			curHour = hourVector.at(hourTimeSegment);
		}catch (const std::out_of_range& exception)
		{
			continue;
		}
		int planeTimeSegment = curPlaneTimeSegment+hourTimeSegment*100;
		bool searchIsBlank=textInput=="";
		//for (a = 0; a < curHour.planesPtrSet.size(); a ++)
		for (const Plane* curPlanePtr : curHour.planesPtrSet)
		{
			const Plane curPlane = *(curPlanePtr);
			if( (searchIsBlank) | (doesStrContainsStr(curPlane.getID(),textInput)) )
			{
				const float red=curPlane.redColor;
				const float grn=curPlane.greenColor;
				const float blu=curPlane.blueColor;
				if(airplaneRenderer.bRenderTrails)
				{
					int trailPoints=0;
					const float red=curPlane.redColor;
					const float grn=curPlane.greenColor;
					const float blu=curPlane.blueColor;
					//for(int t = 0; t<curPlane.timeStamps.size();t++)
					//std::cout<<"P("<<curPlanePtr->timeStamps.size()<<"):\n";
					for(const PlaneTimeStamp curTimeStamp : curPlanePtr->timeStamps)
					{
						//std::cout<<"\tT"<<curTimeStamp.getTime()<<"\n";	
						if( (curTimeStamp.getAlt()<=maxAltFt) & (curTimeStamp.getAlt()>=0) )
						{
							const int curTime = curTimeStamp.getTime();
							if ( ( curTime <= planeTimeSegment ) & (curTimeStamp.getCurHour(hourVector,posTimeHourIndexMap)->getUniqueHourTime() <= curHour.getUniqueHourTime())) 
							{
								if(trailPoints>1)
								{
									//After the first line, count from the previous point
									//This prevents the dashed-line bug.
									indicesPlaneVector.push_back(indexCount-1);
								}
								airplaneCoordVec.push_back(curTimeStamp.x);
								airplaneCoordVec.push_back(curTimeStamp.y);
								airplaneCoordVec.push_back(curTimeStamp.z);
								
								airplaneCoordVec.push_back(red);
								airplaneCoordVec.push_back(grn);
								airplaneCoordVec.push_back(blu);
								
								indicesPlaneVector.push_back(indexCount++);
								
								trailPoints++;
							}
						}
					}
					if(trailPoints==1)
					{
						//Prevents single points from bleeding trails
						//Across other lines
						indicesPlaneVector.push_back(indexCount-1);
					}
				}else
				{
					try
					{
						const int t = planeTimeSegment;
						const PlaneTimeStamp curTimeStamp = curPlane.timeStamps.at(t);
						if( (curTimeStamp.getAlt()<=maxAltFt) & (curTimeStamp.getAlt()>=0) )
						{
							airplaneCoordVec.push_back(curTimeStamp.x);
							airplaneCoordVec.push_back(curTimeStamp.y);
							airplaneCoordVec.push_back(curTimeStamp.z);
							airplaneCoordVec.push_back(red);
							airplaneCoordVec.push_back(grn);
							airplaneCoordVec.push_back(blu);
							indicesPlaneVector.push_back(indexCount++);
						}
					}catch(std::out_of_range& exception)
					{
						
					}
				}
			}
		}
	}
}
int getNumPlaneIndices(){
	return indicesPlaneVector.size();
}

void setIndices(unsigned int *indices, int sizeOfIndices,GLuint elementBufferObject)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices, indices, GL_STATIC_DRAW);

};
void planeParser(std::string& filelocation)
{
	float loadTimer = glfwGetTime();//sets up timer

	hourVector.clear();
	hourVector.shrink_to_fit();
	
	std::ifstream planesFile(filelocation);

	int currentEntry = 0;
	int numEntries = 0;
	int currRow = 0;

	std::map<int,std::string> fieldMap; // Maps an field index to an field name
	std::map<std::string,int> revFieldMap; // Maps an field name to an field index
	std::string lineEntry;
	std::vector<std::string> stringsVecResult;
	std::getline(planesFile, lineEntry);currRow++;//Gets the first line of the file
	splitStr(lineEntry, ',', stringsVecResult);//Seperates the entires of the first line

	for(int i = 0; i < stringsVecResult.size();i++)
	{
		removeFirstSpaceOnStr(stringsVecResult[i]);
		fieldMap[i]=stringsVecResult[i];
		revFieldMap[stringsVecResult[i]]=i;
	}//Maps the field names to the positions
	const int indexDateA = revFieldMap["DateA"];
	const int indexTimeB = revFieldMap["TimeB"];
	const int indexPosTime = revFieldMap["Postime"];
	const int indexIcao0 = revFieldMap["Icao0"];
	const int indexLat3 = revFieldMap["Lat3"];
	const int indexLong4 = revFieldMap["Long4"];
	const int indexAlt1 = revFieldMap["Alt1"];
	const int indexGAlt2 = revFieldMap["GAlt2"];
	const int indexCall5 = revFieldMap["Call5"];
	int latestTimeB=0;
	while (!planesFile.eof())
	{
		std::string planeID;
		std::getline(planesFile, lineEntry);++currRow;
		splitStr(lineEntry, ',', stringsVecResult);
		try
		{
			if(currRow%10000==0)
				std::cout<<"Current row:"<<currRow<<"\t|\tCurrent entry:"<<currentEntry<<" \n";
			int valDateA=-1;
			int valTimeB=-1;
			float valLat=-10000;
			float valLong=-10000;
			float valAlt=-10000;
			std::string valIcao="";
			std::string valCall="";
			for(int i = 0; i < stringsVecResult.size();++i)
			{
				const std::string curStr = stringsVecResult[i];
				if(i==indexDateA)
				{
					valDateA=std::stoi(curStr);
				}
				else if(i==indexTimeB)						
				{
					valTimeB=std::stoi(curStr);
				}
				else if(i==indexIcao0)
				{
					valIcao=(curStr);
				}
				else if(i==indexLat3)
				{
					valLat= std::stod(curStr);
				}
				else if(i==indexLong4)
				{
					valLong=std::stod(curStr);
				}
				else if(i==indexGAlt2)
				{
					valAlt=std::stod(curStr);
				}
				else if(i==indexCall5)
				{
					valCall=(curStr);
				}
			}
			if((valDateA!=-1)&(valTimeB!=-1)&(valLat!=-10000)&(valLong!=-10000)&(valAlt!=-10000))
			{
				planeID=valIcao+valCall;
				
				unsigned long long int dateShifted = valDateA;dateShifted*=10000;
				
				unsigned long long int hourUnique = dateShifted+(valTimeB-(valTimeB%100));
				
				const int hourTimeSegment=(valTimeB - (valTimeB%100))/100;
				try
				{
					hourVector.at(posTimeHourIndexMap.at(hourUnique));
				}catch (const std::out_of_range& exception)
				{
					Hour curHour(hourUnique,hourTimeSegment);
					posTimeHourIndexMap[hourUnique]=hourVector.size();
					hourVector.push_back(curHour);
				}
				int hourIndex=posTimeHourIndexMap[hourUnique];
				
				if (planesMap.find(planeID) == planesMap.end())
				{
					Plane plane(planeID);
					planesMap[planeID]=plane;
				}
				hourVector[hourIndex].planesPtrSet.insert(&planesMap[planeID]);
				PlaneTimeStamp timeStamp(valLat,valLong,valAlt,valTimeB,hourUnique);
				if(valTimeB>latestTimeB)
				{
					latestTimeB=valTimeB;
				}
				planesMap[planeID].timeStamps.push_back(timeStamp);
				
				++currentEntry;
				++numEntries;
			}else
			{
				std::cout<< "Missing fields!\n";
				std::cout<<"Ignoring row["<<currRow+1<<"]\n";
			}
		}
		catch (const std::invalid_argument& exception)
		{
			std::cout<< "Invalid argument exception: " << exception.what() << '\n';
			std::cout<<"Ignoring row["<<currRow+1<<"]\n";
		}
		catch (const std::out_of_range& exception)
		{
			std::cout<< "Out of Range exception: " << exception.what() << '\n';
			std::cout<<"Ignoring row["<<currRow+1<<"]\n";
		}
		catch(const std::bad_alloc& exception)
		{
			std::cout<< "Bad Alloc exception: " << exception.what() << '\n';
			std::cout<<"No more memory to allocate planes, only " <<currentEntry<<" planes loaded!\n" ;
			break;
		}
	}
	planesFile.close();
	std::cout<<"Current row:"<<currRow<<"\t|\tCurrent entry:"<<currentEntry<<" \n";
	int hIndex=0;
	for(hIndex=0;hIndex<hourVector.size();hIndex++)
	{
		std::cout<<"Hour "<<hIndex<<": "<<hourVector[hIndex].planesPtrSet.size()<<" planes\n";
	}
	std::sort(hourVector.begin(),hourVector.end());
	for(hIndex=0;hIndex<hourVector.size();hIndex++)
	{
		posTimeHourIndexMap[hourVector[hIndex].getUniqueHourTime()]=hIndex;
	}
	std::cout<<"Loaded until "<<latestTimeB<<"\n";
	loadTimer = glfwGetTime()-loadTimer;
	std::cout<<"Loading '"<<filelocation<<"' took "<<loadTimer<<" seconds.\n";
	return;
}

#ifndef PLANE_LOADER_HPP
#define PLANE_LOADER_HPP

#include <vector>
#include "hour.hpp"
#include "plane.hpp"


std::vector<Hour> hourVector;
std::map<std::string,Plane> planesMap;
std::map<unsigned long long int ,int> posTimeHourIndexMap;

std::vector<int> indicesPlaneVector;
int indicesVectorCount = 0;

void getPlaneVerticesAsPoints(std::vector<float>& airplaneCoordVec, Earth& earth, int planeTimeSegment,int hourTimeSegment);
int getNumPlaneIndices();
void setIndices(unsigned int *indices, int sizeOfIndices,GLuint elementBufferObject);
#endif

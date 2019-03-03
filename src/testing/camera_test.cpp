#include "testUtils.hpp"
#include "../camera.hpp"


bool test_Camera_identity()
{
	PRINT_TEST_START;
	Matrix4 identityMat;
	identityMat.identity();
	camera.identity();
	if(!camera.getModelMat().compare(identityMat.values))
	{
		std::cout<<"[1/3]";
		return false;
	}
	if(!camera.getProjMat().compare(identityMat.values))
	{
		std::cout<<"[2/3]";
		return false;
	}
	if(!camera.getCombinedMat().compare(identityMat.values))
	{
		std::cout<<"[3/3]";
		return false;
	}
	return true;
}
bool test_Camera_scale()
{
	PRINT_TEST_START;
	camera.identity();
	camera.scale(0.5f);
	float coords[4] = {10,10,99,1};
	float coordsResult[4] = {5,5,99,1};
	camera.getCombinedMat().postMultiplyVec4(coords,coords);
	int i;
	for(i=0;i<4;i++)
	{
		if(coords[i]!=coordsResult[i])
		{
			return false;
		}
	}
	
	return true;
}
bool test_Camera_scale_3()
{
	PRINT_TEST_START;
	camera.identity();
	camera.scale(3.0,6.0,95.0);
	float coords[4] = {10,10,99,1};
	float coordsResult[4] = {10.0*3.0,10.0*6.0,99.0*95.0,1};
	camera.getCombinedMat().postMultiplyVec4(coords,coords);
	int i;
	for(i=0;i<4;i++)
	{
		if(coords[i]!=coordsResult[i])
		{
			return false;
		}
	}
	return true;
}
bool test_Camera_zoom()
{
	PRINT_TEST_START;
	camera.identity();
	camera.zoom(2);
	float coords[4] = {10,10,99,1};
	float coordsResult[4] = {10,10,99*2,1};
	camera.getCombinedMat().postMultiplyVec4(coords,coords);
	int i;
	for(i=0;i<4;i++)
	{
		if(coords[i]!=coordsResult[i])
		{
			return false;
		}
	}
	return true;
}
bool test_Camera_rotate()
{
	PRINT_TEST_START;
	camera.identity();
	camera.rotate(90,1,1,1);
	float coords[4] = {10,10,99,1};
	float coordsResult[4] = {99,-10,10,1};
	camera.getCombinedMat().postMultiplyVec4(coords,coords);
	int i;
	for(i=0;i<4;i++)
	{
		if(coords[i]!=coordsResult[i])
		{
			return false;
		}
	}
	return true;
}
bool test_Camera_pan()
{
	PRINT_TEST_START;
	camera.identity();
	camera.pan(3,6,9);
	float coords[4] = {10,10,99,1};
	float coordsResult[4] = {13,16,108,1};
	camera.getCombinedMat().postMultiplyVec4(coords,coords);
	int i;
	for(i=0;i<4;i++)
	{
		if(coords[i]!=coordsResult[i])
		{
			return false;
		}
	}
	return true;
}
void test_Camera()
{
	std::cout<<__FILE__<<":\n";numFilesTested++;
	printIfOK(test_Camera_identity());
	printIfOK(test_Camera_scale());
	printIfOK(test_Camera_scale_3());
	printIfOK(test_Camera_zoom());
	printIfOK(test_Camera_rotate());
	printIfOK(test_Camera_pan());
}

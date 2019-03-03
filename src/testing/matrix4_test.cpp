#include "testUtils.hpp"
#include "../matrix4.hpp"


bool test_Matrix4_identity()
{
	PRINT_TEST_START;
	float identityValues[16] = 
	{1,0,0,0,
	 0,1,0,0,
	 0,0,1,0,
	 0,0,0,1};
	Matrix4 mat;
	mat.identity();
	return mat.compare(identityValues);
}
bool test_Matrix4_set()
{
	PRINT_TEST_START;
	//Creates a completely random matrix to set to.
	float values[16];
	int i;
	for(i=0;i<16;i++)
	{
		values[i]=((float)rand())/RAND_MAX;
	}
	Matrix4 mat;
	mat.set(values);
	return mat.compare(values);
}
bool test_Matrix4_preMultiply()
{
	PRINT_TEST_START;
	Matrix4 mat,oldmat,matIdentity,matIdentity2;
	float valuesRand[16];
	int i;
	for(i=0;i<16;i++)
	{
		valuesRand[i]=((float)rand())/RAND_MAX;
	}
	matIdentity.identity();
	matIdentity2.identity();
	mat.set(valuesRand);
	oldmat.set(mat.values);
	mat.preMultiply(matIdentity.values);
	if(!mat.compare(oldmat.values))
	{
		std::cout<<"[1/3]:";
		return false;
	}
	mat.set(oldmat.values);
	matIdentity.preMultiply(mat.values);
	if(!matIdentity.compare(mat.values))
	{
		std::cout<<"[2/3]:";
		return false;
	}
	float values1[16] = 
	{2,3,5,9,
	 3,8,9,7,
	 5,2,1,4,
	 7,1,1,1};
	float values2[16] = 
	{4,6,6,4,
	 7,3,3,5,
	 8,5,3,0,
	 9,7,2,1};
	float valuesResult[16] = 
	{150,109,54,32,
	 203,136,83,59,
	 78,69,47,34,
	 52,57,50,34};
	mat.set(values2);
	mat.preMultiply(values1);
	if(!mat.compare(valuesResult))
	{
		std::cout<<"[3/3]:";
		return false;
	}
	return true;
}
bool test_Matrix4_postMultiplyVec4()
{
	PRINT_TEST_START;
	float matValues[16] = 
	{3,   0,0,0,
	 0.5,-1,0,0,
	 0,  -1,1,0,
	 0,   0,0,1};
	Matrix4 mat;
	mat.set(matValues);
	float vec4Values[4] = {2,4,6,1};
	float vec4Result[4] = {6,-3,2,1};
	mat.postMultiplyVec4(vec4Values,vec4Values);
	int i;
	for(i=0;i<4;i++)
	{
		if(vec4Values[i]!=vec4Result[i])
		{
			return false;
		}
	}
	return true;
}
bool test_Matrix4_rotateX()
{
	PRINT_TEST_START;
	float vecValues[4] = {2,3,4,1};
	float vecResult[4] = {2,4,-3,1};
	Matrix4 mat;
	mat.identity();
	mat.rotateX(90.0f);
	int i;
	for(i=0;i<16;i++)
	{
		mat.values[i]=(int)mat.values[i];//Gets rid of rounding errors for this test.
	}
	mat.postMultiplyVec4(vecValues,vecValues);
	for(i=0;i<4;i++)
	{
		if(vecValues[i]!=vecResult[i])
			return false;
	}
	return true;
}
bool test_Matrix4_rotateY()
{
	PRINT_TEST_START;
	float vecValues[4] = {2,3,4,1};
	float vecResult[4] = {-4,3,2,1};
	Matrix4 mat;
	mat.identity();
	mat.rotateY(90.0f);
	int i;
	for(i=0;i<16;i++)
	{
		mat.values[i]=(int)mat.values[i];//Gets rid of rounding errors for this test.
	}
	mat.postMultiplyVec4(vecValues,vecValues);
	for(i=0;i<4;i++)
	{
		if(vecValues[i]!=vecResult[i])
			return false;
	}
	return true;
}
bool test_Matrix4_rotateZ()
{
	PRINT_TEST_START;
	float vecValues[4] = {2,3,4,1};
	float vecResult[4] = {3,-2,4,1};
	Matrix4 mat;
	mat.identity();
	mat.rotateZ(90.0f);
	int i;
	for(i=0;i<16;i++)
	{
		mat.values[i]=(int)mat.values[i];//Gets rid of rounding errors for this test.
	}
	mat.postMultiplyVec4(vecValues,vecValues);
	for(i=0;i<4;i++)
	{
		if(vecValues[i]!=vecResult[i])
			return false;
	}
	return true;
}
bool test_Matrix4_rotate()
{	
	PRINT_TEST_START;
	float vecValues[4] = {2,3,4,1};
	float vecResult[4] = {4,-3,2,1};
	Matrix4 mat;
	mat.identity();
	mat.rotate(90.0f,1.0f,1.0f,1.0f);
	int i;
	for(i=0;i<16;i++)
	{
		mat.values[i]=(int)mat.values[i];//Gets rid of rounding errors for this test.
	}
	mat.postMultiplyVec4(vecValues,vecValues);
	for(i=0;i<4;i++)
	{
		if(vecValues[i]!=vecResult[i])
			return false;
	}
	return true;
}
bool test_Matrix4_compare()
{
	PRINT_TEST_START;
	float valuesRand[16];
	float valuesRand2[16];
	int i;
	for(i=0;i<16;i++)
	{
		valuesRand[i]=((float)rand())/RAND_MAX;
		valuesRand2[i]=((float)rand())/RAND_MAX;
	}
	Matrix4 mat;
	mat.set(valuesRand);
	if(!mat.compare(valuesRand))
	{
		std::cout<<"[1/2]:";
		return false;
	}
	if(mat.compare(valuesRand2))
	{
		std::cout<<"[2/2]:";
		return false;
	}
	return true;
}
void test_Matrix4()
{
	std::cout<<__FILE__<<":\n";numFilesTested++;
	printIfOK(test_Matrix4_identity());
	printIfOK(test_Matrix4_set());
	printIfOK(test_Matrix4_preMultiply());
	printIfOK(test_Matrix4_postMultiplyVec4());
	printIfOK(test_Matrix4_rotateX());
	printIfOK(test_Matrix4_rotateY());
	printIfOK(test_Matrix4_rotateZ());
	printIfOK(test_Matrix4_rotate());
	printIfOK(test_Matrix4_compare());
}

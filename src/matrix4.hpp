#ifndef MATRIX4_HPP
#define MATRIX4_HPP

#include "globemath.hpp"
class Matrix4
{
	public:
	//the values of the 4 dimensional matrix,
	//such that a matrix is represented as an array:
	//[abcd]
	//[efgh]
	//[ijkl]	->	{a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p}
	//[mnop]
	float values[16];
	Matrix4()
	{
		identity();
	}
	//Sets the matrix to the identity matrix, which is a matrix of zeros
	//with ones in the diagonal
	void identity();
	
	//Sets this matrix to the values of the float array passed in.
	//		matB - the matrix values to set this matrix to.
	void set(float matB[16]);
	
	//Multiplies matB * values. Matrix multiplication is order dependent.
	//http://www.mathsisfun.com/algebra/matrix-multiplying.html
	//		matB - the other matrix, such that 'matB * values'
	void preMultiply(float matB[16]);
	
	//Multiplies values * vec4. Order dependent. Premultiplication shouldn't be possible here.
	//Result ends up in vecResult parameter.
	//		vec4 - the 4D vector array to have values multiplied
	//		vecResult - the 4D vector to store the resulting values in
	void postMultiplyVec4(float vec4[4], float vecResult[4]);
	
	//https://stackoverflow.com/questions/3982418/how-to-represent-a-4x4-matrix-rotation
	//Rotate the matrix by the X, Y, or Z coordinates
	//		angle - the angle to rotate the matrix by, in degrees
	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);
	void rotate(float angle, float axisX, float axisY, float axisZ);
	
	
	//https://en.wikipedia.org/wiki/Translation_(geometry)#Matrix_representation
	//Translate the matrix by certain distance
	//		dx - the x component to move by
	//		dy - the y component to move by
	//		dz - the z component to move by
	void translateX(float dx);
	void translateY(float dy);
	void translateZ(float dz);
	void translate(float dx, float dy, float dz);
	
	//Scales the axis, pass in 1.0 as the axis that you DON'T want scaled.
	//		scalarX - the factor to stretch the x-axis
	//		scalarY - the factor to stretch the y-axis
	//		scalarZ - the factor to stretch the z-axis
	void scale(float scalarX, float scalarY, float scalarZ);
	//Compares two matrices together and returns whether they are the same
	//		matB - the other matrix to compare against
	bool compare(float matB[16]);
};
#endif

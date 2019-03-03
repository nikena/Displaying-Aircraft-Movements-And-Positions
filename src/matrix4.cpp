#include "matrix4.hpp"
void Matrix4::identity()
{
	values[0]=1;		values[1]=0;		values[2]=0;		values[3]=0;
	values[4]=0;		values[5]=1;		values[6]=0;		values[7]=0;
	values[8]=0;		values[9]=0;		values[10]=1;		values[11]=0;
	values[12]=0;		values[13]=0;		values[14]=0;		values[15]=1;
}
void Matrix4::set(float matB[16])
{
	int i;
	for(i=0;i<16;i++)
	{
		values[i]=matB[i];
	}
}
//Multiplies matB * values. Matrix multiplication is order dependent.
//http://www.mathsisfun.com/algebra/matrix-multiplying.html
void Matrix4::preMultiply(float matB[16])
{
	float matResult[16];
	matResult[0]=matB[0]*values[0] + matB[1]*values[4] + matB[2]*values[8] + matB[3]*values[12];
	matResult[1]=matB[0]*values[1] + matB[1]*values[5] + matB[2]*values[9] + matB[3]*values[13];
	matResult[2]=matB[0]*values[2] + matB[1]*values[6] + matB[2]*values[10] + matB[3]*values[14];
	matResult[3]=matB[0]*values[3] + matB[1]*values[7] + matB[2]*values[11] + matB[3]*values[15];

	matResult[4]=matB[4]*values[0] + matB[5]*values[4] + matB[6]*values[8] + matB[7]*values[12];
	matResult[5]=matB[4]*values[1] + matB[5]*values[5] + matB[6]*values[9] + matB[7]*values[13];
	matResult[6]=matB[4]*values[2] + matB[5]*values[6] + matB[6]*values[10] + matB[7]*values[14];
	matResult[7]=matB[4]*values[3] + matB[5]*values[7] + matB[6]*values[11] + matB[7]*values[15];

	matResult[8]=matB[8]*values[0] + matB[9]*values[4] + matB[10]*values[8] + matB[11]*values[12];
	matResult[9]=matB[8]*values[1] + matB[9]*values[5] + matB[10]*values[9] + matB[11]*values[13];
	matResult[10]=matB[8]*values[2] + matB[9]*values[6] + matB[10]*values[10] + matB[11]*values[14];
	matResult[11]=matB[8]*values[3] + matB[9]*values[7] + matB[10]*values[11] + matB[11]*values[15];

	matResult[12]=matB[12]*values[0] + matB[13]*values[4] + matB[14]*values[8] + matB[15]*values[12];
	matResult[13]=matB[12]*values[1] + matB[13]*values[5] + matB[14]*values[9] + matB[15]*values[13];
	matResult[14]=matB[12]*values[2] + matB[13]*values[6] + matB[14]*values[10] + matB[15]*values[14];
	matResult[15]=matB[12]*values[3] + matB[13]*values[7] + matB[14]*values[11] + matB[15]*values[15];

	set(matResult);//Sets -after- the multiplication since we don't want to contaminate results prior.
}
//Multiplies values * vec4. Order dependent. Premultiplication shouldn't be possible here.
//Result ends up in vecResult parameter.
void Matrix4::postMultiplyVec4(float vec4[4], float vecResult[4])
{
	float x,y,z,w;
	x=values[0]*vec4[0] + values[1]*vec4[1] + values[2]*vec4[2] + values[3]*vec4[3];
	y=values[4]*vec4[0] + values[5]*vec4[1] + values[6]*vec4[2] + values[7]*vec4[3];
	z=values[8]*vec4[0] + values[9]*vec4[1] + values[10]*vec4[2] + values[11]*vec4[3];
	w=values[12]*vec4[0] + values[13]*vec4[1] + values[14]*vec4[2] + values[15]*vec4[3];

	vecResult[0]=x;
	vecResult[1]=y;
	vecResult[2]=z;
	vecResult[3]=w;
}
//https://stackoverflow.com/questions/3982418/how-to-represent-a-4x4-matrix-rotation
void Matrix4::rotateX(float angle)
{
	Matrix4 rotMat;
	rotMat.values[5]=cosDeg(-angle);
	rotMat.values[6]=-sinDeg(-angle);

	rotMat.values[9]=sinDeg(-angle);
	rotMat.values[10]=cosDeg(-angle);
	preMultiply(rotMat.values);
}
void Matrix4::rotateY(float angle)
{
	Matrix4 rotMat;
	rotMat.values[0]=cosDeg(-angle);
	rotMat.values[2]=sinDeg(-angle);

	rotMat.values[8]=-sinDeg(-angle);
	rotMat.values[10]=cosDeg(-angle);
	preMultiply(rotMat.values);
}
void Matrix4::rotateZ(float angle)
{
	Matrix4 rotMat;
	rotMat.values[0]=cosDeg(-angle);
	rotMat.values[1]=-sinDeg(-angle);

	rotMat.values[4]=sinDeg(-angle);
	rotMat.values[5]=cosDeg(-angle);
	preMultiply(rotMat.values);
}
void Matrix4::rotate(float angle, float axisX, float axisY, float axisZ)
{
	if(axisX!=0)
		rotateX(angle*axisX);
	if(axisY!=0)
		rotateY(angle*axisY);
	if(axisZ!=0)
		rotateZ(angle*axisZ);
}
void Matrix4::translateX(float dx)
{
	Matrix4 transMat;
	transMat.values[3]+=dx;
	preMultiply(transMat.values);
}
void Matrix4::translateY(float dy)
{
	Matrix4 transMat;
	transMat.values[7]+=dy;
	preMultiply(transMat.values);
}
void Matrix4::translateZ(float dz)
{
	Matrix4 transMat;
	transMat.values[11]+=dz;
	preMultiply(transMat.values);
}
void Matrix4::translate(float dx, float dy, float dz)
{
	if(dx!=0)
		translateX(dx);
	if(dy!=0)
		translateY(dy);
	if(dz!=0)
		translateZ(dz);
}
void Matrix4::scale(float scalarX, float scalarY, float scalarZ)
{
	Matrix4 scaleMat;
	scaleMat.values[0]=scalarX;
	scaleMat.values[5]=scalarY;
	scaleMat.values[10]=scalarZ;
	preMultiply(scaleMat.values);
}
bool Matrix4::compare(float matB[16])
{
	int i;
	for(i=0;i<16;i++)
	{
		if(values[i]!=matB[i])
		{
			return false;
		}
	}
	return true;
}

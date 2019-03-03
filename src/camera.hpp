#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "matrix4.hpp"
class Camera
{
	private:
	Matrix4 mat4model;//The model-view matrix- transforming model coords to world coords
	Matrix4 mat4proj;//The projection matrix- transforming world coords to screen coords
	Matrix4 mat4combined;//The combined matrix of both model and projection, such that combined=proj*model
	
	public:
	//Resets the camera's transformations back to default
	void identity()
	{	
		mat4model.identity();//Resets the matrices to transform again.
		mat4proj.identity();
	};
	//Gets the model matrix of the camera
	Matrix4& getModelMat()
	{
		return mat4model;
	};
	//Gets the projection matrix of the camera
	Matrix4& getProjMat()
	{
		return mat4proj;
	};
	//Gets the combined matrix of the camera, that is:
	// proj * model
	Matrix4 getCombinedMat()
	{
		mat4combined.set(mat4model.values);
		mat4combined.preMultiply(mat4proj.values);
		return mat4combined;
	};

	//Changes the screen size to display things larger
	//		zoom - the amount to stretch the X and Y axis
	void scale(float zoom)
	{
		mat4proj.scale(zoom,zoom,1);
	};
	//Changes the screen size to display things larger, with independent dimension zoom coefficients
	//		zoomX - the amount to stretch the X-axis
	//		zoomY - the amount to stretch the Y-axis
	//		zoomZ - the amount to stretch the Z-axis
	void scale(float zoomX, float zoomY, float zoomZ)
	{
		mat4proj.scale(zoomX,zoomY,zoomZ);
	};

	//Moves in distance, not changing the screen size
	//		zoom - the distance-ratio to move in by
	void zoom(float zoom)
	{
		mat4model.scale(1,1,zoom);
	};
	//Rotates camera around its current focus point
	//		angle - the angle to rotate by
	//		axisX - the coefficient of rotation by the X axis
	//		axisY - the coefficient of rotation by the Y axis
	//		axisZ - the coefficient of rotation by the Z axis
	void rotate(float angle, float axisX, float axisY, float axisZ)
	{
		mat4model.rotate(angle,axisX,axisY,axisZ);
	};
	//Moves around the camera.
	//		dX - the amount to move in the X axis
	//		dY - the amount to move in the Y axis
	//		dZ - the amount to move in the Z axis
	void pan(float dX, float dY, float dZ)
	{
		mat4model.translate(dX,dY,dZ);
	};
};
#endif

#include <iostream>
#include "uiControls.hpp"
#include "inputHandler.hpp"
#include "airplaneRenderer.hpp"


void setTimeBackward()
{
    if(airplaneRenderer.bBackwards)
    {
        if(airplaneRenderer.planeRenderSpeed < 2)
        {
            airplaneRenderer.planeRenderSpeed = airplaneRenderer.planeRenderSpeed *2;
        }
    }
    else
    {
        if(airplaneRenderer.planeRenderSpeed <= 0.25)
        {
            airplaneRenderer.bBackwards = true;
        }
        else 
        {
            airplaneRenderer.planeRenderSpeed = airplaneRenderer.planeRenderSpeed /2;
        }
    }
	if(airplaneRenderer.planeRenderSpeed == 0)
    {
		airplaneRenderer.planeRenderSpeed = 1;
	}
}

void setTimeForward()
{
    if(!airplaneRenderer.bBackwards)
    {
        if(airplaneRenderer.planeRenderSpeed < 2)
        {
            airplaneRenderer.planeRenderSpeed = airplaneRenderer.planeRenderSpeed *2;
        }
    }
    else 
    {
        if(airplaneRenderer.planeRenderSpeed <= 0.25)
        {
            airplaneRenderer.bBackwards = false;
        }
        else 
        {
			airplaneRenderer.planeRenderSpeed = airplaneRenderer.planeRenderSpeed /2;
        }
    }
    if(airplaneRenderer.planeRenderSpeed == 0)
    {
		airplaneRenderer.planeRenderSpeed = 1;
	}
}

void toggleTrails(){
    if(!airplaneRenderer.bRenderTrails) {airplaneRenderer.bRenderTrails = true;}
    else airplaneRenderer.bRenderTrails = false;
}

void pause(){
    if(airplaneRenderer.planeRenderSpeed == 0)
    {
		airplaneRenderer.planeRenderSpeed = 1;
	}else
	{
		airplaneRenderer.planeRenderSpeed = 0;
	}
}

void zoomIn(){
	inputHandler.setTargetZoom(inputHandler.getTargetZoom()-1.0/10.0);
}

void zoomOut(){
	inputHandler.setTargetZoom(inputHandler.getTargetZoom()+1.0/10.0);
}

void recenterCamera()
{
	inputHandler.setCameraRotHoriz(0);
	inputHandler.setCameraRotVert(0);
}
void altUp()
{
	oldMaxAltFt=maxAltFt;
	maxAltFt+=1000;
}
void altDown()
{
	oldMaxAltFt=maxAltFt;
	maxAltFt-=1000;
	if(maxAltFt<=0)
		maxAltFt=0;
}

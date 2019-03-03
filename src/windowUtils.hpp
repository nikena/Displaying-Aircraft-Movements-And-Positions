#ifndef WINDOW_UTILS_HPP
#define WINDOW_UTILS_HPP

const int windowWidth = 800;
const int windowHeight = 600;
float aspectRatio=4.0/3.0;

int curScreenX=0;
int curScreenY=0;
int curScreenWidth=windowWidth;
int curScreenHeight=windowHeight;

float avgDeltaTime = -1.0;
//Returns the moving average deltaTime over multiple frames
float getAverageDeltaTime()
{
	return avgDeltaTime;
}
//Updates the variables within windowUtils.hpp
//At the moment only the average delta time is modified.
//	deltaTime - the current time(seconds) between this and last frame.
void updateWindowUtils(float deltaTime)
{
	if(avgDeltaTime==-1.0)
	{
		avgDeltaTime=deltaTime;//Initialize the average delta time
		return;
	}else
	{
		//Lerp between the new deltaTime and the old average
		avgDeltaTime=deltaTime*0.1f+avgDeltaTime*0.9f;
	}
}
#endif

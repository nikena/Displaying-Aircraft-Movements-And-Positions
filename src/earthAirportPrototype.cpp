#define NOMINMAX

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include "deps/glew.c"

#ifdef __APPLE__
#include <GLFW/glfw3.h>
#else
#include "deps/GLFW/glfw3.h"
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "deps/stb_image.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "earth.hpp"
#include "matrix4.hpp"
#include "camera.hpp"
#include "windowUtils.hpp"
#include "earthAirportPrototype.hpp"

#include "earth.cpp"
#include "matrix4.cpp"
#include "ofAirportLoader.cpp"
#include "spriteRenderer.cpp"
#include "directoryHandler.cpp"
#include "airplaneRenderer.cpp"
#include "inputHandler.cpp"
#include "planeLoader.cpp"
#include "glfwErrorHandler.cpp"
#include "fontRenderer.cpp"
#include "uiControls.cpp"
#include "uiRenderer.cpp"
#include "shaders.cpp"



void character_callback( GLFWwindow *window, unsigned int codepoint )
{
	textInputOld=textInput;
	char tempChar = codepoint;

	switch(ui.inputFlag)
	{
		case inputFlagListen:
			if(textInput.length() < 10)
			{
				textInput = textInput + tempChar;
			}
			break;
		case inputFlagSearchButtonClicked:
			break;
		case inputFlagClear:
			textInput = "";
			break;
	}
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(ui.inputFlag == inputFlagListen)
	{
		switch(key)
		{
			case GLFW_KEY_BACKSPACE:
			case GLFW_KEY_DELETE:
			if(textInput.size()>0)
			{
				textInputOld=textInput;
				textInput.pop_back();//Removes last character
			}
			break;
			default: break;
		}
	}
}

void initialize()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_PROGRAM_POINT_SIZE);


	std::cout << "Loading...\n";

	std::string openflightsFileLoc = findFileAbsLocFromRoot("Data Files/openflights/airports.dat");
	airportParser(openflightsFileLoc);

	std::string adsbplanesFileLoc = "trimmed1.csv";
	chooseFile(&adsbplanesFileLoc,"csv,txt");
	std::cout<<adsbplanesFileLoc<<"\n";
	if(fileExists(adsbplanesFileLoc))
	{
		planeParser(adsbplanesFileLoc);
	}

	std::cout << "Loaded!\n";

	initializeSpriteRenderer();
	ui.initialize();
	fontRenderer.initialize();
	earth.initialize();
	airplaneRenderer.initializeAirplaneRenderer(earth);
}
void updateViewport()
{
	int windowWidth,windowHeight;
	glfwGetWindowSize(window,&windowWidth,&windowHeight);
	
	float largest = windowWidth;
	float shortest = windowWidth;
	
	if(windowHeight>largest)
		largest=windowHeight;
	if(windowHeight<shortest)
		shortest=windowHeight;
		
	float screenWidth=shortest*aspectRatio;
	float screenHeight=shortest;
	if(screenWidth>windowWidth)
	{
		screenWidth=windowWidth;
		screenHeight=windowWidth/aspectRatio;
	}
	
	float sx=(windowWidth-screenWidth)/2.0;
	float sy=(windowHeight-screenHeight)/2.0;
	

	curScreenX=sx;
	curScreenY=sy;
	curScreenWidth=screenWidth;
	curScreenHeight=screenHeight;


	#ifdef __APPLE__
	screenWidth = screenWidth*2;
	screenHeight = screenHeight*2;
	sx=(windowWidth-(screenWidth /2.0));
	sy=(windowHeight-(screenHeight/ 2.0));

	#endif	

	glViewport(sx,sy,screenWidth,screenHeight);
}
void update(float deltaTime)
{
	updateWindowUtils(deltaTime);
	
	//Finds the closest aspect ratio to use.
	//From either 16:9 or 4:3, since both look good.
	int cwindowWidth,cwindowHeight;
	glfwGetWindowSize(window,&cwindowWidth,&cwindowHeight);
	float windowAspectRatio=(float)cwindowWidth / (float)cwindowHeight;
	if( std::abs(windowAspectRatio-(16.0/9.0)) < std::abs(windowAspectRatio - (4.0/3.0)) )
	{
		aspectRatio=16.0/9.0;
	}else
	{
		aspectRatio=4.0/3.0;
	}
	
	inputHandler.updateInput(deltaTime, window);

	camera.identity();
	camera.rotate(90,1,0,0);
	camera.rotate(90,0,1,0);//Rotates earth to a preferable angle.
	
	camera.rotate(-inputHandler.getEarthRotHoriz(),0,1,0);
	camera.rotate(-inputHandler.getEarthRotVert(),1,0,0);//Rotates to earth rotation set by mouse
	
	updateViewport();
	camera.scale(1/(aspectRatio*300.0),1/(300.0),-(1/300.0f)/2.0f);//Projection matrix set to window dimensions.
	
	camera.scale(1/inputHandler.getZoom());//Zooms in to the earth
	
	camera.pan(0,0,-300);
	camera.rotate(-inputHandler.cameraRotHoriz,0,1,0);
	camera.rotate(-inputHandler.cameraRotVert,1,0,0);//Rotates to camera viewing rotation set by mouse
	camera.pan(0,0,300);
	
	camera.pan(0,0,-600);//Moves earth away from camera, as to render properly
	
	spriteRendererUpdateCamera(camera);
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//Clears the colour and depth buffers of the screen 

	earth.render(camera);
	airplaneRenderer.renderAirplanes(camera,earth);
	
	ui.render(fontRenderer, textInput);
	fontRenderer.render(deltaTime);
}

void mouseCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT) 
	{
		float nX = windowWidth*(inputHandler.getcurCursorPosX()-curScreenX)/curScreenWidth;
		float nY = windowHeight*(inputHandler.getcurCursorPosY()-curScreenY)/curScreenHeight;
		//nX is between 0 and windowWidth
		//nY is between 0 and windowHeight
		//As such mouse input is faithful to viewport
		ui.isClicked(nX, nY, action);
	}
}

int main(int argc, char** argv)
{
	glfwSetErrorCallback(glfwErrorCallback);
	double lastTime = 0;
	double nowTime = 0;
	if(!glfwInit())
    {
		std::cout << "Could not init glfw.\n";
        return 1;
    }
    glfwWindowHint(GLFW_RESIZABLE,GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);

    window = glfwCreateWindow(windowWidth,windowHeight,"Aircraft",NULL,NULL);
    glfwSetCharCallback( window, character_callback );
    glfwSetKeyCallback( window, key_callback );
    
    if(window==NULL)
    {
		std::cout << "Could not create window.\n";
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_FASTEST);

	glewExperimental = GL_TRUE;
	if(glewInit()!=GLEW_OK)
	{
		std::cout << "Could not init GLEW.\n";
		glfwTerminate();
		return 1;
	}
	float deltaTime = 1.0;
	glfwSetScrollCallback(window, scrollZoomCallback);
	glfwSetMouseButtonCallback(window, mouseCallback);

	initialize();
    while(!glfwWindowShouldClose(window))
    {
		lastTime = glfwGetTime();
		(update)(deltaTime);
		glfwSwapBuffers(window);
		glfwPollEvents();

		inputHandler.lastUpdate(window);
		nowTime=glfwGetTime();
		deltaTime = (float)(nowTime - lastTime);
    }

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}

#define NOMINMAX

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include "../deps/glew.c"

#ifdef __APPLE__
#include <GLFW/glfw3.h>
#else
#include "../deps/GLFW/glfw3.h"
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "../deps/stb_image.h"

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

#include "../earth.hpp"
#include "../matrix4.hpp"
#include "../camera.hpp"
#include "../shaders.hpp"
#include "../windowUtils.hpp"
#include "../earthAirportPrototype.hpp"
#include "../glfwErrorHandler.hpp"

#include "../earth.cpp"
#include "../matrix4.cpp"
#include "../ofAirportLoader.cpp"
#include "../spriteRenderer.cpp"
#include "../directoryHandler.cpp"
#include "../airplaneRenderer.cpp"
#include "../inputHandler.cpp"
#include "../planeLoader.cpp"
#include "../fontRenderer.cpp"
#include "../shaders.cpp"
#include "../uiControls.cpp"
#include "../uiRenderer.cpp"

#include "testUtils.hpp"

#include "camera_test.cpp"
#include "directoryHandler_test.cpp"
#include "earth_test.cpp"
#include "fontRenderer_test.cpp"
#include "glfwErrorHandler_test.cpp"
#include "globemath_test.cpp"
#include "inputHandler_test.cpp"
#include "matrix4_test.cpp"
#include "plane_test.cpp"
#include "shaders_test.cpp"
#include "spriteRenderer_test.cpp"
#include "uiRenderer_test.cpp"

void initialize()
{
	initializeSpriteRenderer();
	ui.initialize();
	fontRenderer.initialize();
	earth.initialize();
	airplaneRenderer.initializeAirplaneRenderer(earth);
	
	test_Camera();
	test_DirectoryHandler();
	test_Earth();
	test_FontRenderer();
	test_GlfwErrorHandler();
	test_GlobeMath();
	test_InputHandler();
	test_Matrix4();
	test_Plane();
	test_Shaders();
	test_SpriteRenderer();
	test_UIRenderer();
	
	std::cout<<"============\n";
	std::cout<<"Number of test files   \t   :"<<numFilesTested<<"\n";
	std::cout<<"Number of tests		   :"<<numSuccess+numFail<<"\n";
	std::cout<<"Successful tests	   :"<<numSuccess<<"\n";
	std::cout<<"\\-Require manual check\t   :"<<requireManualCheck<<"\n";
	std::cout<<"Failed tests    	   :"<<numFail<<"\n";
	std::cout<<"\\-Unimplemented tests \t   :"<<numUnimplemented<<"\n";
	if(numFail>0)
	{
		std::cout<<"\tBuild failed.\n";
	}else
	{
		std::cout<<"\tBuild passed.\n";
		glfwSetWindowShouldClose(window,GLFW_TRUE);
	}
	assert(numFail==0);
}
void update(float deltaTime)
{
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
    glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);

    window = glfwCreateWindow(800,600,"Aircraft",NULL,NULL);
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

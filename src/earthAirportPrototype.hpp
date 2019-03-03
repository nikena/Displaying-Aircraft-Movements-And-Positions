#ifndef EARTH_AIRPORT_PROTOTYPE_HPP
#define EARTH_AIRPORT_PROTOTYPE_HPP

#include "airplaneRenderer.hpp"
#include "earth.hpp"
#include "camera.hpp"
#include "fontRenderer.hpp"
#include "uiRenderer.hpp"

GLFWwindow* window;
Earth earth;
Camera camera;
UI ui;
FontRenderer fontRenderer;
AirplaneRenderer airplaneRenderer;

//The text input on search looks through planes for Icao and Call signs.
std::string textInput,textInputOld;

//The maximum altitude to render planes at, measured in ft.
double maxAltFt = 50000;
double oldMaxAltFt = maxAltFt;

//Calls other initializers and sets necessary variables if needed.
void initialize();


//Updates the viewport such that the program can be resized properly.
//Called on every update loop.
//Use if manually changing resolution, ie going fullscreen.
void updateViewport();


//The main update loop. If anything needs to be called from here, it is
//recommended it calls a function from a seperate class instead.
//For instance, all UI drawing should be done in uiHandler's render method,
//Rather than here.
void update(float deltaTime);


//The main method. Used for setting up opengl context and window.
//It also calls the update method on every loop.
int main(int argc, char** argv);


#endif

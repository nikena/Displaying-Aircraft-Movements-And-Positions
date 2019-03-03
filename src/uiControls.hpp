#ifndef UICONTROLS_HPP
#define UICONTROLS_HPP

#include <iostream>
#include "earthAirportPrototype.hpp"

//Slows down or reverses plane rendering, depending on the current
//rendering speed.
void setTimeBackward();
//Speeds up plane rendering, depending on the current rendering speed.
void setTimeForward();
//(Un-)Pauses plane rendering.
void pause();

//Zooms in to the earth
void zoomIn();
//Zooms out from the earth
void zoomOut();

//Resets the camera such that it is no longer tilted at an angle
//away from the earth.
void recenterCamera();

//Modifies the maximum rendering height of planes.
//Planes above the maximum height are ignored.
void altUp();
void altDown();

#endif

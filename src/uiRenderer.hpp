#ifndef UIRenderer
#define UIRenderer

class UI;

#include <cstdio>
#include <iostream>
#include <list>
#include <vector>
#include "fontRenderer.hpp"
#include "uiControls.hpp"
#include "sprite2D.cpp"
#include "button.hpp"
#include <GLFW/glfw3.h>

const int inputFlagListen = 1;
const int inputFlagSearchButtonClicked = 2;
const int inputFlagClear = 3;
    
class UI
{
    public:
    Sprite2D searchFlightSprite;
    Sprite2D searchAirportSprite2D, loadFileButton, uploadButton;
    Sprite2D menuBar;
    Sprite2D filterPane, playBackPane;
    Sprite2D expandButton, searchBar, searchButton1, filterButton, playbackButton, zoomInButton, zoomOutButton;
    Sprite2D inputBox, showButton, showButtonClicked, hideButton, hideButtonClicked, showTrackOption;
    Sprite2D forwardButton, backwardButton, pauseButton;
    Sprite2D recenterCameraButton;
    Sprite2D altUpButton,altDownButton;
  
    std::list<Sprite2D*> spriteList;
    std::list<Sprite2D*> buttonList;
    std::list<Sprite2D*> menuBarList;
    std::list<Sprite2D*> filterPaneList;
    std::list<Sprite2D*> playbackPaneList;
    std::vector<Button*> buttonPtrVector;

    int expandFlag = 0;
    int displayFlag = 0;
    int displayFlag1 = 0;
    
    int inputFlag = inputFlagClear; //0 - not start; 1 - listen to input; 2 - searchButtonclicked, stop listen; 3 - searchBarclicked, clear all input

	SearchButton bSearchButton;
	ExpandButton bExpandButton;
	SearchBar bSearchBar;
	AltitudeUpButton bAltUpButton;
	AltitudeDownButton bAltDownButton;
	FilterButton bFilterButton;
	PlaybackButton bPlaybackButton;
	ZoomInButton bZoomInButton;
	ZoomOutButton bZoomOutButton;
	RecenterCamButton bRecenterCameraButton;
	MinusSpeedButton bMinusSpeedButton;
	PlusSpeedButton bPlusSpeedButton;
	PauseButton bPauseButton;
	ToggleTrailsButton bToggleTrailsButton;

    UI();

	//The action the ui takes after a click was committed.
	//	x - the x cursor coordinate
	//	y - the y cursor coordinate#
	//	action - whether the mouse button is held(1) or released(0)
    void isClicked(float x, float y, int action);

	//Renders the UI, to be called after every render loop.
	//	fontRenderer - A reference to a FontRenderer, to display text
	//	textInput - the search string for the search bar
    void render(FontRenderer& fontRenderer,std::string textInput);
    
    //Initializes this renderer.
    void initialize();
};


#endif

#include "uiRenderer.hpp"
#include "button.cpp"

UI::UI() 
{
	bSearchButton = SearchButton(&searchButton1, this);
	buttonPtrVector.push_back(&bSearchButton);

	bExpandButton = ExpandButton(&expandButton, this);
	buttonPtrVector.push_back(&bExpandButton);

	bSearchBar = SearchBar(&searchBar, this);
	buttonPtrVector.push_back(&bSearchBar);

	bAltUpButton = AltitudeUpButton(&altUpButton, this);
	buttonPtrVector.push_back(&bAltUpButton);

	bAltDownButton = AltitudeDownButton(&altDownButton, this);
	buttonPtrVector.push_back(&bAltDownButton);

	bFilterButton = FilterButton(&filterButton, this);
	buttonPtrVector.push_back(&bFilterButton);

	bPlaybackButton = PlaybackButton(&playbackButton, this);
	buttonPtrVector.push_back(&bPlaybackButton);

	bZoomInButton = ZoomInButton(&zoomInButton, this);
	buttonPtrVector.push_back(&bZoomInButton);

	bZoomOutButton = ZoomOutButton(&zoomOutButton, this);
	buttonPtrVector.push_back(&bZoomOutButton);

	bRecenterCameraButton = RecenterCamButton(&recenterCameraButton, this);
	buttonPtrVector.push_back(&bRecenterCameraButton);

	bMinusSpeedButton = MinusSpeedButton(&backwardButton, this);
	buttonPtrVector.push_back(&bMinusSpeedButton);

	bPlusSpeedButton = PlusSpeedButton(&forwardButton, this);
	buttonPtrVector.push_back(&bPlusSpeedButton);

	bPauseButton = PauseButton(&pauseButton, this);
	buttonPtrVector.push_back(&bPauseButton);

	bToggleTrailsButton = ToggleTrailsButton(&showTrackOption, this);
	buttonPtrVector.push_back(&bToggleTrailsButton);
}

void UI::isClicked(float x, float y, int action)
{
	float relX = x / (windowWidth / 2) - 1;
	float relY = 1 - y / (windowHeight / 2);

	static Button* pressedButton = NULL;
	if (action == 1)
	{
		pressedButton = NULL;
		for (Button* btnPtr : buttonPtrVector) //checks if any of the buttons are clicked
		{
			if (btnPtr->isClicked(x, y, action))
			{
				pressedButton = btnPtr; // stores the button that was pressed
				break;
			}
		}
	}
	else
	{
		if (pressedButton != NULL)
		{
			pressedButton->isClicked(x, y, action); // checks if mouse is still on the pressed button
		}
	}
}




void UI::render(FontRenderer& fontRenderer,std::string textInput)
{
	if(fontRenderer.indexNum > 0){
		fontRenderer.flush();
	}
	//glEnable(GL_SCISSOR_TEST);
	//glScissor(150, 1100, 230, 58);
	//glScissor(150, 1100, 230, 58);
	//get input
	std::string searchBoxInput = textInput;
	fontRenderer.drawText(searchBoxInput, 0.6, searchBar.getX()+0.12, searchBar.getY()+0.1);
	
	if(fontRenderer.indexNum > 0){
		fontRenderer.flush();
	}
	//glDisable(GL_SCISSOR_TEST);

	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

	for (Sprite2D* sprite : spriteList) {
		if(sprite->isDisplay()){
			sprite->drawSprite();
		}
	}

	for (Sprite2D* button : buttonList) {
		if(button->isDisplay()){
			button->drawSprite();
		}
	}

	for (Sprite2D* button : menuBarList) {
		if(button->isDisplay()){
			button->drawSprite();
		}
	}

	for (Sprite2D* button : filterPaneList) {
		if(button->isDisplay()){
			button->drawSprite();
		}
	}

	for (Sprite2D* button : playbackPaneList) {
		if(button->isDisplay()){
			button->drawSprite();
		}
	}
	
}

void UI::initialize()
{
	//Create necessary sprites 

	// SearchBar elements:
	searchBar.loadNoInitShape("assets/filter/pane.png", shaderProgramTex);
	searchBar.setTo2DDimensions(-0.93f, 0.825f, 0.53f, 0.11f);
	searchBar.setToDisplay();
	buttonList.push_back(&searchBar);

	expandButton.loadNoInitShape("assets/button/expandButton.png", shaderProgramTex);
	expandButton.setTo2DDimensions(-0.92f, 0.832f, 0.09f, 0.09f);
	expandButton.setToDisplay();
	buttonList.push_back(&expandButton);

	searchButton1.loadNoInitShape("assets/button/searchButton.png", shaderProgramTex);
	searchButton1.setTo2DDimensions(-0.5f, 0.83f, 0.09f, 0.09f);
	searchButton1.setToDisplay();
	buttonList.push_back(&searchButton1);
	
	// MenuBar elements:
	altUpButton.loadNoInitShape("assets/button/altitudeUpButton.png", shaderProgramTex);
	altUpButton.setTo2DDimensions(-0.916f, 0.70f, 0.073f, 0.1f);
	menuBarList.push_back(&altUpButton);
	altDownButton.loadNoInitShape("assets/button/altitudeDownButton.png", shaderProgramTex);
	altDownButton.setTo2DDimensions(-0.916f, 0.59f, 0.073f, 0.1f);
	menuBarList.push_back(&altDownButton);
	
	filterButton.loadNoInitShape("assets/button/filterButton.png", shaderProgramTex);
	filterButton.setTo2DDimensions(-0.916f, 0.47f, 0.073f, 0.1f);
	menuBarList.push_back(&filterButton);

	playbackButton.loadNoInitShape("assets/button/playbackButton.png", shaderProgramTex);
	playbackButton.setTo2DDimensions(-0.916f, 0.33f, 0.073f, 0.1f);
	menuBarList.push_back(&playbackButton);

	zoomInButton.loadNoInitShape("assets/button/zoomInButton.png", shaderProgramTex);
	zoomInButton.setTo2DDimensions(-0.916f, 0.21f, 0.073f, 0.1f);
	menuBarList.push_back(&zoomInButton);

	zoomOutButton.loadNoInitShape("assets/button/zoomOutButton.png", shaderProgramTex);
	zoomOutButton.setTo2DDimensions(-0.916f, 0.09f, 0.073f, 0.1f);
	menuBarList.push_back(&zoomOutButton);
	
	recenterCameraButton.loadNoInitShape("assets/button/recenterCameraButton.png",shaderProgramTex);
	recenterCameraButton.setTo2DDimensions(-0.916f, -0.01f, 0.073f, 0.1f);
	menuBarList.push_back(&recenterCameraButton);

	menuBar.loadNoInitShape("assets/menu/menuBar1.png", shaderProgramTex);
	menuBar.setTo2DDimensions(-0.935f, -0.03f, 0.11f, 0.85f);
	spriteList.push_back(&menuBar);

	// Filter elements:

	inputBox.loadNoInitShape("assets/filter/pane.png", shaderProgramTex);
	inputBox.setTo2DDimensions(-0.8f, 0.65f, 0.3f, 0.095f);
	filterPaneList.push_back(&inputBox);

	showButton.loadNoInitShape("assets/filter/showButton.png", shaderProgramTex);
	showButton.setTo2DDimensions(-0.625f, 0.5f, 0.1f, 0.087f);
	filterPaneList.push_back(&showButton);

	showButtonClicked.loadNoInitShape("assets/filter/showButtonClicked.png", shaderProgramTex);
	showButtonClicked.setTo2DDimensions(-0.625f, 0.5f, 0.1f, 0.087f);
	filterPaneList.push_back(&showButtonClicked);

	hideButton.loadNoInitShape("assets/filter/hideButton.png", shaderProgramTex);
	hideButton.setTo2DDimensions(-0.525f, 0.5f, 0.1f, 0.087f);
	filterPaneList.push_back(&hideButton);

	hideButtonClicked.loadNoInitShape("assets/filter/hideButtonClicked.png", shaderProgramTex);
	hideButtonClicked.setTo2DDimensions(-0.525f, 0.5f, 0.1f, 0.087f);
	filterPaneList.push_back(&hideButtonClicked);
	
	showTrackOption.loadNoInitShape("assets/filter/showTrackOption.png", shaderProgramTex);
	showTrackOption.setTo2DDimensions(-0.82f, 0.6f, 0.4f, 0.1f);
	filterPaneList.push_back(&showTrackOption);

	filterPane.loadNoInitShape("assets/filter/pane.png", shaderProgramTex);
	filterPane.setTo2DDimensions(-0.83f, 0.07f, 0.43f, 0.75f);
	spriteList.push_back(&filterPane);

	// Playback elements:
	backwardButton.loadNoInitShape("assets/button/backwardButton.png", shaderProgramTex);
	backwardButton.setTo2DDimensions(-0.8f, 0.3f, 0.07f, 0.08f);
	playbackPaneList.push_back(&backwardButton);

	forwardButton.loadNoInitShape("assets/button/forwardButton.png", shaderProgramTex);
	forwardButton.setTo2DDimensions(-0.5f, 0.3f, 0.07f, 0.08f);
	playbackPaneList.push_back(&forwardButton);

	pauseButton.loadNoInitShape("assets/button/pauseButton.png", shaderProgramTex);
	pauseButton.setTo2DDimensions(-0.65f, 0.3f, 0.07f, 0.08f);
	playbackPaneList.push_back(&pauseButton);

	playBackPane.loadNoInitShape("assets/filter/pane.png", shaderProgramTex);
	playBackPane.setTo2DDimensions(-0.83f, 0.07f, 0.43f, 0.75f);
	spriteList.push_back(&playBackPane);
}





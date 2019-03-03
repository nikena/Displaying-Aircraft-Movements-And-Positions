#include <iostream>

#include "button.hpp"
#include "windowUtils.hpp"
#include "sprite2D.hpp"
//#include "uiRenderer.hpp"

Button::Button(Sprite2D* spr, UI* uiPtr)
	:spritePtr(spr)
	,uiPtr(uiPtr)
{}

Button::Button()
{
	spritePtr = NULL;
}
void Button::close()
{
}

bool Button::isClicked(float x, float y, int action)
{
	bool isclicked = false;
	if (isOnSprite(x, y))
	{
		isclicked = true;
		if (action == 1)
		{}

		else if (action == 0)
		{
			act();
		}
	}
	return isclicked;
}

bool Button::isOnSprite(float x, float y)//check if cursor is on the sprite
{
	float relX = x / (windowWidth / 2) - 1;
	float relY = 1 - y / (windowHeight / 2);
	if (spritePtr -> isDisplay() && spritePtr -> contains(relX, relY)) 
	{
		return true;
	}
	return false;
}

void Button::act()
{}



SearchBar::SearchBar(Sprite2D* spr, UI* uiPtr)
	:Button(spr, uiPtr)
{}

SearchBar::SearchBar()
	:Button()
{}

void SearchBar::act()
{
	if (uiPtr->inputFlag == inputFlagSearchButtonClicked) {
		uiPtr->inputFlag = inputFlagClear; //clear input
	}
	else {
		uiPtr->inputFlag = inputFlagListen; //listen to input
	}

}



SearchButton::SearchButton(Sprite2D* spr, UI* uiPtr)
	:Button(spr, uiPtr)
{}

SearchButton::SearchButton()
	:Button()
{}

void SearchButton::act()
{
	uiPtr->inputFlag = inputFlagSearchButtonClicked;//stop listening for input
}



ExpandButton::ExpandButton(Sprite2D* spr, UI* uiPtr)
	:Button(spr, uiPtr)
{}

ExpandButton::ExpandButton()
	:Button()
{}

void ExpandButton::act()
{
	if (uiPtr->expandFlag == 0) {
		for (Sprite2D* button : (uiPtr->menuBarList)) {
			button->setToDisplay();
		}
		uiPtr->menuBar.setToDisplay();
		uiPtr->expandFlag = 1;
	}
	else {
		for (Sprite2D* button : (uiPtr->menuBarList)) {
			button->setToHide();
		}
		uiPtr->bFilterButton.close();
		uiPtr->bPlaybackButton.close();
		
		uiPtr->menuBar.setToHide();
		uiPtr->expandFlag = 0;
	}
}



AltitudeUpButton::AltitudeUpButton(Sprite2D* spr, UI* uiPtr)
	:Button(spr, uiPtr)
{}

AltitudeUpButton::AltitudeUpButton()
	:Button()
{}

void AltitudeUpButton::act()
{
	altUp();
}




AltitudeDownButton::AltitudeDownButton(Sprite2D* spr, UI* uiPtr)
	:Button(spr, uiPtr)
{}

AltitudeDownButton::AltitudeDownButton()
	:Button()
{}

void AltitudeDownButton::act()
{
	altDown();
}



FilterButton::FilterButton(Sprite2D* spr, UI* uiPtr)
	:Button(spr, uiPtr)
{}

FilterButton::FilterButton()
	:Button()
{}

void FilterButton::act()
{
	if (uiPtr->displayFlag == 0) {
		if (uiPtr->displayFlag1 == 1) {
			uiPtr->bPlaybackButton.close();
		}
		uiPtr->filterPane.setToDisplay();
		uiPtr->showTrackOption.setToDisplay();
		uiPtr->displayFlag = 1;
	}
	else {
		close();
	}
	for (Sprite2D* button : (uiPtr->playbackPaneList)) {
		button->setToHide();
	}
	uiPtr->playBackPane.setToHide();
}
void FilterButton::close()
{
	uiPtr->filterPane.setToHide();
	uiPtr->showTrackOption.setToHide();
	uiPtr->displayFlag = 0;
}




PlaybackButton::PlaybackButton(Sprite2D* spr, UI* uiPtr)
	:Button(spr, uiPtr)
{}

PlaybackButton::PlaybackButton()
	:Button()
{}

void PlaybackButton::act()
{
	if (uiPtr->displayFlag1 == 0) {
		if (uiPtr->displayFlag == 1) {
			uiPtr->bFilterButton.close();
		}
		for (Sprite2D* button : (uiPtr->playbackPaneList)) {
			button->setToDisplay();
		}
		uiPtr->playBackPane.setToDisplay();
		uiPtr->displayFlag1 = 1;
	}
	else {
		close();
	}
	for (Sprite2D* button : (uiPtr->filterPaneList)) {
		button->setToHide();
	}
	uiPtr->filterPane.setToHide();
}

void PlaybackButton::close()
{
	for (Sprite2D* button : (uiPtr->playbackPaneList)) 
	{
		button->setToHide();
	}
	uiPtr->playBackPane.setToHide();
	uiPtr->displayFlag1 = 0;
}



ZoomInButton::ZoomInButton(Sprite2D* spr, UI* uiPtr)
	:Button(spr, uiPtr)
{}

ZoomInButton::ZoomInButton()
	:Button()
{}

void ZoomInButton::act()
{
	zoomIn();
}




ZoomOutButton::ZoomOutButton(Sprite2D* spr, UI* uiPtr)
	:Button(spr, uiPtr)
{}

ZoomOutButton::ZoomOutButton()
	:Button()
{}

void ZoomOutButton::act()
{
	zoomOut();
}




RecenterCamButton::RecenterCamButton(Sprite2D* spr, UI* uiPtr)
	:Button(spr, uiPtr)
{}

RecenterCamButton::RecenterCamButton()
	:Button()
{}

void RecenterCamButton::act()
{
	recenterCamera();
}




ShowButton::ShowButton(Sprite2D* spr, UI* uiPtr)
	:Button(spr, uiPtr)
{}

ShowButton::ShowButton()
	:Button()
{}

void ShowButton::act()
{
	uiPtr->hideButtonClicked.setToHide();
	uiPtr->showButton.setToHide();
	uiPtr->hideButton.setToDisplay();
	uiPtr->showButtonClicked.setToDisplay();
	uiPtr->filterPane.setToDisplay();
}




ShowButton_clicked::ShowButton_clicked(Sprite2D* spr, UI* uiPtr)
	:Button(spr, uiPtr)
{}

ShowButton_clicked::ShowButton_clicked()
	:Button()
{}

void ShowButton_clicked::act()
{
	uiPtr->showButtonClicked.setToHide();
	uiPtr->hideButton.setToHide();
	uiPtr->showButton.setToDisplay();
	uiPtr->hideButtonClicked.setToDisplay();
	uiPtr->filterPane.setToDisplay();
}




HideButton::HideButton(Sprite2D* spr, UI* uiPtr)
	:Button(spr, uiPtr)
{}

HideButton::HideButton()
	:Button()
{}

void HideButton::act()
{
	uiPtr->showButtonClicked.setToHide();
	uiPtr->hideButton.setToHide();
	uiPtr->showButton.setToDisplay();
	uiPtr->hideButtonClicked.setToDisplay();
	uiPtr->filterPane.setToDisplay();
}




HideButton_clicked::HideButton_clicked(Sprite2D* spr, UI* uiPtr)
	:Button(spr, uiPtr)
{}

HideButton_clicked::HideButton_clicked()
	:Button()
{}

void HideButton_clicked::act()
{
	uiPtr->hideButtonClicked.setToHide();
	uiPtr->showButton.setToHide();
	uiPtr->hideButton.setToDisplay();
	uiPtr->showButtonClicked.setToDisplay();
	uiPtr->filterPane.setToDisplay();
}




MinusSpeedButton::MinusSpeedButton(Sprite2D* spr, UI* uiPtr)
	:Button(spr, uiPtr)
{}

MinusSpeedButton::MinusSpeedButton()
	:Button()
{}

void MinusSpeedButton::act()
{
	setTimeBackward();
}




PlusSpeedButton::PlusSpeedButton(Sprite2D* spr, UI* uiPtr)
	:Button(spr, uiPtr)
{}

PlusSpeedButton::PlusSpeedButton()
	:Button()
{}

void PlusSpeedButton::act()
{
	setTimeForward();
}




PauseButton::PauseButton(Sprite2D* spr, UI* uiPtr)
	:Button(spr, uiPtr)
{}

PauseButton::PauseButton()
	:Button()
{}

void PauseButton::act()
{
	pause();
}




ToggleTrailsButton::ToggleTrailsButton(Sprite2D* spr, UI* uiPtr)
	:Button(spr, uiPtr)
{}

ToggleTrailsButton::ToggleTrailsButton()
	:Button()
{}

void ToggleTrailsButton::act()
{
	toggleTrails();
}

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "sprite2D.hpp"



class Button
{
	Sprite2D* spritePtr;
	//Whether the image of the button contains coordinates
	//	x - the x cursor coordinate
	//	y - the y cursor coordinate
	bool isOnSprite(float x, float y);
protected:
	UI* uiPtr;
	//The action which this button will take after being closed.
	virtual void close();
public:

	Button(Sprite2D* spr, UI* uiPtr);

	Button();

	//Whether the button is clicked
	//	x - the x screen coordinate
	//	y - the y screen coordinate
	//	action - whether the mouse button is held(1) or released(0)
	bool isClicked(float x, float y, int action);

	//The action which this button will take after being clicked.
	virtual void act();

};

class SearchBar : public Button
{
public:
	SearchBar(Sprite2D* spr, UI* uiPtr);

	SearchBar();

	void act() override;
};

class SearchButton : public Button
{
public:
	SearchButton(Sprite2D* spr, UI* uiPtr);

	SearchButton();

	void act() override;
};

class ExpandButton : public Button
{
public:
	ExpandButton(Sprite2D* spr, UI* uiPtr);

	ExpandButton();

	void act() override;
};

class AltitudeUpButton : public Button
{
public:
	AltitudeUpButton(Sprite2D* spr, UI* uiPtr);

	AltitudeUpButton();

	void act() override;
};

class AltitudeDownButton : public Button
{
public:
	AltitudeDownButton(Sprite2D* spr, UI* uiPtr);

	AltitudeDownButton();

	void act() override;
};

class FilterButton : public Button
{
public:
	FilterButton(Sprite2D* spr, UI* uiPtr);

	FilterButton();

	void act() override;
	void close() override;
};

class PlaybackButton : public Button
{
public:
	PlaybackButton(Sprite2D* spr, UI* uiPtr);

	PlaybackButton();

	void act() override;
	void close() override;
};

class ZoomInButton : public Button
{
public:
	ZoomInButton(Sprite2D* spr, UI* uiPtr);

	ZoomInButton();

	void act() override;
};

class ZoomOutButton : public Button
{
public:
	ZoomOutButton(Sprite2D* spr, UI* uiPtr);

	ZoomOutButton();

	void act() override;
};

class RecenterCamButton : public Button
{
public:
	RecenterCamButton(Sprite2D* spr, UI* uiPtr);

	RecenterCamButton();

	void act() override;
};

class ShowButton : public Button
{
public:
	ShowButton(Sprite2D* spr, UI* uiPtr);

	ShowButton();

	void act() override;
};

class ShowButton_clicked : public Button
{
public:
	ShowButton_clicked(Sprite2D* spr, UI* uiPtr);

	ShowButton_clicked();

	void act() override;
};

class HideButton : public Button
{
public:
	HideButton(Sprite2D* spr, UI* uiPtr);

	HideButton();

	void act() override;
};

class HideButton_clicked : public Button
{
public:
	HideButton_clicked(Sprite2D* spr, UI* uiPtr);

	HideButton_clicked();

	void act() override;
};

class MinusSpeedButton : public Button
{
public:
	MinusSpeedButton(Sprite2D* spr, UI* uiPtr);

	MinusSpeedButton();

	void act() override;
};

class PlusSpeedButton : public Button
{
public:
	PlusSpeedButton(Sprite2D* spr, UI* uiPtr);

	PlusSpeedButton();

	void act() override;
};

class PauseButton : public Button
{
public:
	PauseButton(Sprite2D* spr, UI* uiPtr);

	PauseButton();

	void act() override;
};

class ToggleTrailsButton : public Button
{
public:
	ToggleTrailsButton(Sprite2D* spr, UI* uiPtr);

	ToggleTrailsButton();

	void act() override;
};
#endif

#include "testUtils.hpp"
#include "../inputHandler.hpp"


bool test_InputHandler_updateInput()
{
	PRINT_REQ_MANUAL_CHECK;
}
bool test_InputHandler_lastUpdate()
{
	PRINT_TEST_START;
	float oldCurPosX = inputHandler.getcurCursorPosX();
	float oldCurPosY = inputHandler.getcurCursorPosY();
	inputHandler.lastUpdate(window);
	if(oldCurPosX!=inputHandler.getlastCursorPosX())
		return false;
	if(oldCurPosY!=inputHandler.getlastCursorPosY())
		return false;
	return true;
}
bool test_InputHandler_setTargetZoom()
{
	PRINT_TEST_START;
	inputHandler.setTargetZoom(0.9f);
	return inputHandler.getTargetZoom()==0.9f;
}
bool test_InputHandler_scrollZoomCallback()
{
	PRINT_TEST_START;
	float tz = inputHandler.getTargetZoom();
	scrollZoomCallback(window, 0,10);
	bool pass = tz > inputHandler.getTargetZoom();
	inputHandler.setTargetZoom(1.0f);//Resets the target zoom for future tests
	return pass;
}
void test_InputHandler()
{
	std::cout<<__FILE__<<":\n";numFilesTested++;
	printIfOK(test_InputHandler_updateInput());
	printIfOK(test_InputHandler_lastUpdate());
	printIfOK(test_InputHandler_setTargetZoom());
	printIfOK(test_InputHandler_scrollZoomCallback());
}

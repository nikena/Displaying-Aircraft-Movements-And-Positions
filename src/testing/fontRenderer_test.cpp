#include "testUtils.hpp"
#include "../fontRenderer.hpp"


bool test_FontRenderer_drawText()
{
	PRINT_REQ_MANUAL_CHECK;
}
bool test_FontRenderer_getRenderLengthOfText()
{
	//Although this would be testable since it returns a number,
	//if the font were to change this test would fail,
	//and there's no way to predict the length
	//of a character independent of the font, so must leave it to manual
	//checking.
	PRINT_REQ_MANUAL_CHECK;
}
bool test_FontRenderer_render()
{
	PRINT_REQ_MANUAL_CHECK;
}
bool test_FontRenderer_flush()
{
	PRINT_REQ_MANUAL_CHECK;
}
void test_FontRenderer()
{
	std::cout<<__FILE__<<":\n";numFilesTested++;
	printIfOK(test_FontRenderer_drawText());
	printIfOK(test_FontRenderer_getRenderLengthOfText());
	printIfOK(test_FontRenderer_render());
	printIfOK(test_FontRenderer_flush());
}

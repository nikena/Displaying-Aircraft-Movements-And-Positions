#include "testUtils.hpp"
#include "../uiRenderer.hpp"


bool test_UIRenderer_render()
{
	PRINT_REQ_MANUAL_CHECK_NO_RETURN;
	glGetError();//Clears any glError from any prior test.
	ui.render(fontRenderer, textInput);
	if(glGetError()!=GL_NO_ERROR)
	{
		return false;
	}
	return true;
}
void test_UIRenderer()
{
	std::cout<<__FILE__<<":\n";numFilesTested++;
	printIfOK(test_UIRenderer_render());
}

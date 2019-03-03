#include "testUtils.hpp"
#include "../glfwErrorHandler.hpp"


bool test_GlfwErrorHandler_glfwErrorCallback()
{
	PRINT_REQ_MANUAL_CHECK;
}
void test_GlfwErrorHandler()
{
	std::cout<<__FILE__<<":\n";numFilesTested++;
	printIfOK(test_GlfwErrorHandler_glfwErrorCallback());
}

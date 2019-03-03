#include "testUtils.hpp"
#include "../earth.hpp"


bool test_Earth_render()
{
	PRINT_REQ_MANUAL_CHECK;
}
void test_Earth()
{
	std::cout<<__FILE__<<":\n";numFilesTested++;
	printIfOK(test_Earth_render());
}

#include "testUtils.hpp"
#include "../plane.hpp"


bool test_Plane_setID()
{
	PRINT_TEST_START;
	Plane plane("testID");
	plane.setID("NEWtestID");
	return plane.getID()=="NEWtestID";
}
void test_Plane()
{
	std::cout<<__FILE__<<":\n";numFilesTested++;
	printIfOK(test_Plane_setID());
}

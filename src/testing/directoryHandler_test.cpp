#include "testUtils.hpp"
#include "../directoryHandler.hpp"


bool test_DirectoryHandler_fileExists()
{
	PRINT_TEST_START;
	if(!fileExists("testing/directoryHandler_test.cpp"))
	{
		std::cout<<"[1/2]:";
		return false;
	}
	if(fileExists("nonExistentFileWhichWillNeverEverExist.imaginary"))
	{
		std::cout<<"[2/2]:";
		return false;
	}
	return true;
}
bool test_DirectoryHandler_findFileAbsLocFromRoot()
{
	PRINT_TEST_START;
	if(!fileExists(findFileAbsLocFromRoot("Data Files/openflights/airports.dat",false)))
	{
		std::cout<<"[1/2]:";
		return false;
	}
	if(fileExists(findFileAbsLocFromRoot("BAD_FOLDER/airports.dat",false)))
	{
		std::cout<<"[2/2]:";
		return false;
	}
	return true;
}
bool test_DirectoryHandler_chooseFile()
{
	PRINT_REQ_MANUAL_CHECK;
}
bool test_DirectoryHandler_chooseFile_filters()
{
	PRINT_REQ_MANUAL_CHECK;
}
void test_DirectoryHandler()
{
	std::cout<<__FILE__<<":\n";numFilesTested++;
	printIfOK(test_DirectoryHandler_fileExists());
	printIfOK(test_DirectoryHandler_findFileAbsLocFromRoot());
	printIfOK(test_DirectoryHandler_chooseFile());
	printIfOK(test_DirectoryHandler_chooseFile_filters());
}

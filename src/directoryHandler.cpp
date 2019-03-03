#include "directoryHandler.hpp"
#include <nfd.h>
bool fileExists(std::string fileName)
{
	std::ifstream file(fileName);
	bool exists= (bool)file;
	file.close();
	return exists;
}
std::string findFileAbsLocFromRoot(std::string fileLocation, bool printDebug)
{
	int attempts=16;
	if(printDebug)std::cout<<"Trying to open: " << fileLocation << "\n";
	if(fileExists(fileLocation))
	{
		return fileLocation;
	}else
	{
		attempts--;
		if(*fileLocation.begin()=='/')
			fileLocation = ".." + fileLocation;
		else
			fileLocation = "../" + fileLocation;
	}
	for(;attempts>0;attempts--)
	{
		if(printDebug)std::cout<<"\tTrying: " << fileLocation << "\n";
		if(fileExists(fileLocation))
		{
			return fileLocation;
		}else
		{
			fileLocation = "../" + fileLocation;
		}
	}
	if(printDebug)std::cout<<"\tCould not find file!\n";
	return "";
}
std::string chooseFile(std::string *outPath, const char* filters)
{
	nfdchar_t *tempOutPath = NULL;
	nfdresult_t result = NFD_OpenDialog( filters, NULL, &tempOutPath );
	switch(result)
	{
		case NFD_OKAY:
			std::cout <<"Opening '"<< tempOutPath << "'\n";
			(*outPath).assign(tempOutPath);
			break;
		case NFD_CANCEL:
			std::cout <<"Cancelled opening file.\n";
			(*outPath).assign("");
			break;
		default:
			std::cout<<"Error opening file: " << NFD_GetError() << "\n";
			(*outPath).assign("");
			break;
	}
	return *outPath;
}
std::string chooseFile(std::string *outPath)
{
	return chooseFile(outPath,NULL);
}

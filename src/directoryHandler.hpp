#ifndef DIRECTORY_HANDLER_HPP
#define DIRECTORY_HANDLER_HPP

//Queries whether the file exists
//		fileName- the name of the file to be checked
bool fileExists(std::string fileName);

//Finds a file from the root directory, if it can be found.
//		fileLocation- the name of the file, inside the folders from
//						the perspective of the project root.
std::string findFileAbsLocFromRoot(std::string fileLocation, bool printDebug=true);

//Asks the OS to choose a file from a GUI.
//Any file type can be chosen.
//		*outPath- the string to which to return a file location string
std::string chooseFile(std::string *outPath);


//Asks the OS to choose a file from a GUI.
//Filters to only get certain file types.
//		*outPath- the string to which to return a file location string
//		filters- The string of filters to be used.
//				 For example, the string "csv,txt" would allow the user
//				 To choose either CSV or TXT files.
//				 See for reference:
//				 https://github.com/mlabbe/nativefiledialog#file-filter-syntax
std::string chooseFile(std::string *outPath, const char* filters);
#endif

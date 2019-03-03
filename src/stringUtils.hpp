#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP
//Splits a string using a delimiter character
//Example - splitStr("ab,cd,efg",',',result)
//			Would modify result to have a vector containing {"ab","cd","efg"}
inline void splitStr(std::string& str, char delimiter, std::vector<std::string>& stringsVecResult)
{
	stringsVecResult.clear();
	std::stringstream strstream(str);
	std::string strpart;
	while(std::getline(strstream,strpart,delimiter))
	{
		stringsVecResult.push_back(strpart);
	}
};

//passing in a string" test" modifies it to become "test"
inline void removeFirstSpaceOnStr(std::string& str)
{
	if(str[0]==' ')
	{
		str.erase(str.begin());
	}
};
//Returns whether one string contains another
//	str1 - the first string which may contain the second.
//	str2 - the second string
inline bool doesStrContainsStr(std::string str1, std::string& str2)
{
	return str1.find(str2) != std::string::npos;
}

#endif

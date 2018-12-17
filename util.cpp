/*
//OOP345 - milestone3
//Bokyung Moon(136103165)
//util.cpp
*/

#include "util.h"
std::string& trim(std::string& s, char trimChar)
{
	while (!s.empty() && s[0] == trimChar)
		s.erase(0, 1);

	while (!s.empty() && s[s.size() - 1] == trimChar)
		s.erase(s.size() - 1, 1);

	return s;
}

/*
 * Utilities.h
 *
 *  Created on: Nov 20, 2014
 *      Author: Rafael De Smet
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <sstream>
#include <stdexcept>
#include <iostream>

class Utilities	{
public:
	Utilities();
	~Utilities();
	
	static std::string intToString(int theNumber);
	static int stringToInt(std::string theString);
	static int constCharToInt(const char* theString);
	static std::string charToString(char theChar);
	static std::string charPtrToString(char* theCharPtr);
	static const char* stringToCharPtr(std::string theString);
};

#endif /* UTILITIES_H_ */
/*
 * Utilities.cpp
 *
 *  Created on: Nov 20, 2014
 *      Author: Rafael De Smet
 */

#include "Utilities.h"

using namespace std;

Utilities::Utilities()
{
}

Utilities::~Utilities()
{
}

string Utilities::intToString(int theNumber)
{
	ostringstream localStringStream;
	try
	{
		localStringStream << theNumber;
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
	return localStringStream.str();
}

int Utilities::stringToInt(string theString)
{
	istringstream ss(theString);
	int localInt;

	try
	{
		ss >> localInt;
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
	return localInt;
}

int Utilities::constCharToInt(const char* theString)
{
	stringstream stringValue;
	int intValue;

	try
	{
		stringValue << theString;
		stringValue >> intValue;
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}

	return intValue;
}

std::string Utilities::charToString(char theChar)
{
	stringstream ss;
	string returnString;

	try
	{
		ss << theChar;
		ss >> returnString;
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}

	return returnString;
}

std::string Utilities::charPtrToString(char* theCharPtr)
{
	std::string returnString(theCharPtr);
	return returnString;
}

const char* Utilities::stringToCharPtr(std::string theString)
{
	return theString.c_str();
}

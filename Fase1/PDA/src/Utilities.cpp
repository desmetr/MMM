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
	localStringStream << theNumber;

	return localStringStream.str();
}

int Utilities::stringToInt(string theString)	
{
	istringstream ss(theString);
	int localInt;
	
	try	{
		ss >> localInt;
		return localInt;
	}
	catch (exception& e)	{
		cout << e.what() << endl;
	}
}

int Utilities::constCharToInt(const char* theString)
{
	stringstream stringValue;
	stringValue << theString;
	
	int intValue;
	stringValue >> intValue;
	
	return intValue;
}

std::string Utilities::charToString(char theChar)	{
	stringstream ss;
	string returnString;
	
	ss << theChar;
	ss >> returnString;
	
	return returnString;
}

std::string Utilities::charPtrToString(char* theCharPtr)	{
	std::string returnString(theCharPtr);
	return returnString;	
}

const char* Utilities::stringToCharPtr(std::string theString)	{
	return theString.c_str();
}
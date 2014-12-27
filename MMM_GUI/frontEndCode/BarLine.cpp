/*
 * BarLine.cpp
 *
 *  Created on: Dec 16, 2014
 *      Author: Rafael De Smet
 */

#include "BarLine.h"

using namespace std;

BarLine::BarLine() {
}

BarLine::~BarLine() {
}

const string& BarLine::getLocation() const 	{	return location;	}
const string& BarLine::getTagName() const	{	return tagName;		}

void BarLine::setLocation(const string& location) 	{	this->location = location;	}

void BarLine::print() {
	if (location != "")	{
		cout << "\t\tBarLine:" << endl;
		cout << "\t\t\tlocation: " << location << endl;
		barStyle.print();
	}
}

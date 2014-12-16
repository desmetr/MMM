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

const string& BarLine::getBarStyle() const 	{	return barStyle;	}
const string& BarLine::getLocation() const 	{	return location;	}
const string& BarLine::getTagName() const	{	return tagName;		}

void BarLine::setBarStyle(const string& barStyle) 	{	this->barStyle = barStyle;	}
void BarLine::setLocation(const string& location) 	{	this->location = location;	}

void BarLine::print() {
	cout << "BarLine:" << endl;
	cout << "\tlocation: " << location << endl;
	cout << "\tbarStyle: " << barStyle << endl;
}

/*
 * BarStyle.cpp
 *
 *  Created on: Dec 17, 2014
 *      Author: Rafael De Smet
 */

#include "BarStyle.h"

using namespace std;

BarStyle::BarStyle() {
}

BarStyle::~BarStyle() {
}

const string& BarStyle::getBarStyle() const 	{	return barStyle;	}
const string& BarStyle::getTagName() const 		{	return tagName;		}

void BarStyle::setBarStyle(const string& barStyle) 		{	this->barStyle = barStyle;	}

void BarStyle::print() {
	cout << "\t\t\tBarStyle:" << endl;
	cout << "\t\t\t\tbarStyle: " << barStyle << endl;
}

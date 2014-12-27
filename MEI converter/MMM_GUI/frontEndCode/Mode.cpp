/*
 * Mode.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: Rafael De Smet
 */

#include "Mode.h"

using namespace std;

Mode::Mode() {
}

Mode::~Mode() {
}

const string& Mode::getMode() const 	{	return mode;	}
const string& Mode::getTagName() const 	{	return tagName;	}

void Mode::setMode(const string& mode) 	{	this->mode = mode;	}

void Mode::print() {
	cout << "\t\t\t\tMode:" << endl;
	cout << "\t\t\t\t\tmode: " << mode << endl;
}

/*
 * Key.cpp
 *
 *  Created on: Dec 16, 2014
 *      Author: Rafael De Smet
 */

#include "Key.h"

using namespace std;

Key::Key() {
}

Key::~Key() {
}

const string& Key::getFifths() const 	{	return fifths;	}
const string& Key::getMode() const 		{	return mode;	}
const string& Key::getTagName() const 	{	return tagName;	}

void Key::setFifths(const string& fifths)	{	this->fifths = fifths;	}
void Key::setMode(const string& mode)		{	this->mode = mode;		}

void Key::print() {
	cout << "\t\t\tKey:" << endl;
	cout << "\t\t\t\tfifths: " << fifths << endl;
	cout << "\t\t\t\tmode: " << mode << endl;
}

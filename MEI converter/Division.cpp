/*
 * Division.cpp
 *
 *  Created on: Dec 17, 2014
 *      Author: Rafael De Smet
 */

#include "Division.h"

using namespace std;

Division::Division() {
}

Division::~Division() {
}

const string& Division::getDivisions() const 	{	return divisions;	}
const string& Division::getTagName() const 		{	return tagName;		}

void Division::setDivisions(const string& divisions) 	{	this->divisions = divisions;	}

void Division::print() {
	cout << "\t\t\tDivision" << endl;
	cout << "\t\t\t\tdivisions: " << divisions << endl;
}

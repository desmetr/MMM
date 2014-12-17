/*
 * Attribute.cpp
 *
 *  Created on: Dec 16, 2014
 *      Author: Rafael De Smet
 */

#include "Attribute.h"

using namespace std;

Attribute::Attribute() {
}

Attribute::~Attribute() {
}

const string& Attribute::getDivisions() const	{	return divisions;	}
const string& Attribute::getTagName() const		{	return tagName;		}

void Attribute::setDivisions(const string& divisions) {	this->divisions = divisions;	}

void Attribute::print() {
	cout << "Attribute:" << endl;
	cout << "\tdivisions: " << divisions << endl;
	key.print();
	time.print();
	clef.print();
}

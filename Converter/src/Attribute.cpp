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

const string& Attribute::getTagName() const		{	return tagName;		}

void Attribute::print() {
	if (division.getDivisions() != "")	{
		cout << "\t\tAttribute:" << endl;
		division.print();
		key.print();
		time.print();
		clef.print();
	}
}

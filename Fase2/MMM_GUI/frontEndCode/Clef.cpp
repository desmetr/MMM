/*
 * Clef.cpp
 *
 *  Created on: Dec 16, 2014
 *      Author: Rafael De Smet
 */

#include "Clef.h"

using namespace std;

Clef::Clef() {
}

Clef::~Clef() {
}

const string& Clef::getTagName() const 	{	return tagName;	}

void Clef::print() {
	cout << "\t\t\tClef:" << endl;
	sign.print();
	line.print();
}

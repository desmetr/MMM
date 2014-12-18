/*
 * Fifths.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: Rafael De Smet
 */

#include "Fifths.h"

using namespace std;

Fifths::Fifths() {
}

Fifths::~Fifths() {
}

const string& Fifths::getFifths() const 	{	return fifths;	}
const string& Fifths::getTagName() const 	{	return tagName;	}

void Fifths::setFifths(const string& fifths) {	this->fifths = fifths;	}

void Fifths::print() {
	cout << "\t\t\t\tFifths:" << endl;
	cout << "\t\t\t\t\tfifths: " << fifths << endl;
}

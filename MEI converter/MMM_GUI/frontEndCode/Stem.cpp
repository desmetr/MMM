/*
 * Stem.cpp
 *
 *  Created on: Dec 17, 2014
 *      Author: Rafael De Smet
 */

#include "Stem.h"

using namespace std;

Stem::Stem() {
}

Stem::~Stem() {
}

const string& Stem::getStem() const 		{	return stem;		}
const string& Stem::getTagName() const		{	return tagName;		}

void Stem::setStem(const string& stem) 		{	this->stem = stem;	}

void Stem::print() {
	cout << "\t\t\tStem:" << endl;
	cout << "\t\t\t\tstem: " << stem << endl;
}

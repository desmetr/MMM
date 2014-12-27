/*
 * Pitch.cpp
 *
 *  Created on: Dec 16, 2014
 *      Author: Rafael De Smet
 */

#include "Pitch.h"

using namespace std;

Pitch::Pitch() {
}

Pitch::~Pitch() {
}

const string& Pitch::getTagName() const 	{	return tagName;	}

void Pitch::print() {
	cout << "\t\t\tPitch:" << endl;
	step.print();
	octave.print();
}

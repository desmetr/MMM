/*
 * Octave.cpp
 *
 *  Created on: Dec 17, 2014
 *      Author: Rafael De Smet
 */

#include "Octave.h"

using namespace std;

Octave::Octave() {
}

Octave::~Octave() {
}

const string& Octave::getOctave() const		{	return octave;	}
const string& Octave::getTagName() const 	{	return tagName; }

void Octave::setOctave(const string& octave) 	{	this->octave = octave;	}

void Octave::print() {
	cout << "\t\t\t\tOctave:" << endl;
	cout << "\t\t\t\t\toctave: " << octave << endl;
}

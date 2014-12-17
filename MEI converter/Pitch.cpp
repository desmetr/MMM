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

const string& Pitch::getOctave() const 		{	return octave;	}
const string& Pitch::getStep() const 		{	return step;	}
const string& Pitch::getTagName() const 	{	return tagName;	}

void Pitch::setOctave(const string& octave) {	this->octave = octave;	}
void Pitch::setStep(const string& step) 	{	this->step = step;		}

void Pitch::print() {
	cout << "Pitch:" << endl;
	cout << "\tstep: " << step << endl;
	cout << "\toctave: " << octave << endl;
}

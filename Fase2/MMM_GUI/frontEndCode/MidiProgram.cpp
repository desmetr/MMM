/*
 * MidiProgram.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: Rafael De Smet
 */

#include "MidiProgram.h"

using namespace std;

MidiProgram::MidiProgram() {
}

MidiProgram::~MidiProgram() {
}

const string& MidiProgram::getMidiProgram() const 		{	return midiProgram;		}
const string& MidiProgram::getTagName() const 			{	return tagName;			}

void MidiProgram::setMidiProgram(const string& midiProgram) {	this->midiProgram = midiProgram;	}

void MidiProgram::print() {
	cout << "\t\t\tMidiProgram: " << endl;
	cout << "\t\t\t\tmidi program: " << midiProgram << endl;
}

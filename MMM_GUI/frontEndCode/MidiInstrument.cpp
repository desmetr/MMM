/*
 * MidiInstrument.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: Rafael De Smet
 */

#include "MidiInstrument.h"

using namespace std;

MidiInstrument::MidiInstrument() {
}

MidiInstrument::~MidiInstrument() {
}

const string& MidiInstrument::getId() const 			{	return id;			}
const string& MidiInstrument::getTagName() const 		{	return tagName;		}

void MidiInstrument::setId(const string& id) 			{	this->id = id;		}

void MidiInstrument::print() {
	cout << "\t\tMidiInstrument:" << endl;
	cout << "\t\t\tID: " << id << endl;
	midiChannel.print();
	midiProgram.print();
	volume.print();
	pan.print();
}

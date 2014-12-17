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
const string& MidiInstrument::getMidiChannel() const 	{	return midiChannel;	}
const string& MidiInstrument::getMidiProgram() const 	{	return midiProgram;	}
const string& MidiInstrument::getPan() const 			{	return pan;			}
const string& MidiInstrument::getTagName() const 		{	return tagName;		}
const string& MidiInstrument::getVolume() const 		{	return volume;		}

void MidiInstrument::setId(const string& id) 					{	this->id = id;						}
void MidiInstrument::setMidiChannel(const string& midiChannel) 	{	this->midiChannel = midiChannel;	}
void MidiInstrument::setMidiProgram(const string& midiProgram) 	{	this->midiProgram = midiProgram;	}
void MidiInstrument::setPan(const string& pan) 					{	this->pan = pan;					}
void MidiInstrument::setVolume(const string& volume) 			{	this->volume = volume;				}

void MidiInstrument::print() {
	cout << "MidiInstrument:" << endl;
	cout << "\tID: " << id << endl;
	cout << "\tmidiChannel: " << midiChannel << endl;
	cout << "\tmidiProgram: " << midiProgram << endl;
	cout << "\tvolume: " << volume << endl;
	cout << "\tpan: " << pan << endl;
}

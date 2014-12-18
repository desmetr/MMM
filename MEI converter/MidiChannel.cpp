/*
 * MidiChannel.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: Rafael De Smet
 */

#include "MidiChannel.h"

using namespace std;

MidiChannel::MidiChannel() {
}

MidiChannel::~MidiChannel() {
}

const string& MidiChannel::getMidiChannel() const 	{	return midiChannel;	}
const string& MidiChannel::getTagName() const 		{	return tagName;		}

void MidiChannel::setMidiChannel(const string& midiChannel) 	{	this->midiChannel = midiChannel;	}

void MidiChannel::print() {
	cout << "\t\t\tMidiChannel:" << endl;
	cout << "\t\t\t\tmidi-channel: " << midiChannel << endl;
}

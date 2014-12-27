/*
 * InputOutputManager.cpp
 *
 *  Created on: Dec 22, 2014
 *      Author: Rafael De Smet
 */

#include "InputOutputManager.h"

using namespace std;

InputOutputManager::InputOutputManager() {
	readInstruments();
	readNotes();
}

InputOutputManager::~InputOutputManager() {
}

void InputOutputManager::readInstruments() {
	ifstream infile("midiInstruments.txt");
	unsigned int index = 1;
	string instrument;

	while (getline(infile, instrument))	{
		midiInstruments.insert(make_pair(index - 1, instrument));
		index++;
	}
}

void InputOutputManager::readNotes() {
	ifstream infile("midiNotes.txt");
	unsigned int index = 1;
	string note;

	while (getline(infile, note))	{
		midiNotes.insert(make_pair(index - 1, note));
		index++;
	}
}

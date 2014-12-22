/*
 * CSVGenerator.cpp
 *
 *  Created on: Dec 22, 2014
 *      Author: Rafael De Smet
 */

#include "CSVGenerator.h"

using namespace std;

CSVGenerator::CSVGenerator() {
	midiInstruments = ioManager.midiInstruments;
	midiNotes = ioManager.midiNotes;
}

CSVGenerator::CSVGenerator(PartList partList, Part part) {
	this->sourcePartList = partList;
	this->sourcePart = part;

	midiInstruments = ioManager.midiInstruments;
	midiNotes = ioManager.midiNotes;
}

CSVGenerator::~CSVGenerator() {
}

string CSVGenerator::getHeader() {
	string returnString = "Timing Resolution (pulses per quarter note)\n";
	returnString += "4\n\n";

	return returnString;
}

string CSVGenerator::getInstrument() {
	string returnString = "Instrument,";
	string name = sourcePartList.scorePart.partName.getName();
	if (name == "Piano")	{
		name = "Acoustic Grand Piano";
	}

	for (const auto& midiInstrument : midiInstruments)	{
		if (name == midiInstrument.second)	{
			returnString += Utilities::intToString(midiInstrument.first);
		}
	}

	returnString += ",";
	returnString += name;

	returnString += "\n\n";
	return returnString;
}

string CSVGenerator::getDataSpecification() {
	return "Tick,Note (0-127),Velocity (0-127)\n";
}

string CSVGenerator::getTick(Note note, int& tick) {
	string returnString = "";

	if (!note.isRest())		{
		if (note.type.getType() == "quarter")	{
			returnString = Utilities::intToString(++tick);
		}
		else if (note.type.getType() == "half")	{
			returnString = Utilities::intToString(++tick);
			tick++;
		}
	}
	return returnString;
}

string CSVGenerator::getNote(Note note) {
	string returnString = "";
	if (!note.isRest())		{
		string completeNote = note.pitch.step.getStep() + note.pitch.octave.getOctave();

		for (const auto& midiNote : midiNotes)	{
			if (completeNote == midiNote.second)	{
				returnString += Utilities::intToString(midiNote.first);
			}
		}
	}

	return returnString;
}

string CSVGenerator::getVelocity(Note note) {
	string volume = "";
	if (!note.isRest())		{
		volume = sourcePartList.scorePart.midiInstrument.volume.getVolume();
		int index = volume.find(".");
		int numberOfSymbolsToRemove = volume.size() - index;

		volume.erase(index, numberOfSymbolsToRemove);
	}

	return volume;
}

void CSVGenerator::generateCSV() {
	ofstream midiAsCSV;
	midiAsCSV.open("midiAsCSV.csv");

	int tick = -1;

	midiAsCSV << getHeader();
	midiAsCSV << getInstrument();
	midiAsCSV << getDataSpecification();

	for (const auto& measure : sourcePart.measures)		{
		for (const auto& note : measure.notes)			{
			midiAsCSV << getTick(note, tick);
			midiAsCSV << ",";
			midiAsCSV << getNote(note);
			midiAsCSV << ",";
			midiAsCSV << getVelocity(note);
			midiAsCSV << endl;
		}
	}

	midiAsCSV.close();
}

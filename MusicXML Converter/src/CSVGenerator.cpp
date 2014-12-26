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
	returnString += Utilities::intToString(PPQ) + "\n\n";

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

	returnString += "\n";
	return returnString;
}

int CSVGenerator::getTick(Note note) {
	if (note.type.getType() == "quarter")	{
		return 3;
	}
	else if (note.type.getType() == "half")	{
		return 7;
	}
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
	else	{
		returnString = "0";
	}

	return returnString;
}

string CSVGenerator::getVelocityOff() {
	return "0";
}

string CSVGenerator::getVelocityOn(Note note) {
	string volume = "";
	if (!note.isRest())		{
		volume = sourcePartList.scorePart.midiInstrument.volume.getVolume();
		int index = volume.find(".");
		int numberOfSymbolsToRemove = volume.size() - index;

		volume.erase(index, numberOfSymbolsToRemove);
	}
	else	{
		volume = "0";
	}

	return volume;
}

void CSVGenerator::generateCSV(string fileName) {
	ofstream midiToCSV;

	int position = fileName.find(".xml");
	fileName.erase(position, fileName.size() - position);
	fileName += ".csv";
	midiToCSV.open(Utilities::stringToCharPtr(fileName));

	int tick = 0;

	midiToCSV << getHeader();
	midiToCSV << getInstrument();

	for (const auto& measure : sourcePart.measures)		{
		for (unsigned int i = 0; i < measure.notes.size(); i++)			{
			if (!measure.notes[i].isRest())	{
				midiToCSV << Utilities::intToString(tick);
				midiToCSV << ",";
				midiToCSV << getNote(measure.notes[i]);
				midiToCSV << ",";
				midiToCSV << getVelocityOn(measure.notes[i]);
				midiToCSV << "\n";

				tick += getTick(measure.notes[i]);
				midiToCSV << Utilities::intToString(tick);
				midiToCSV << ",";
				midiToCSV << getNote(measure.notes[i]);
				midiToCSV << ",";
				midiToCSV << getVelocityOff();
				midiToCSV << "\n";

				tick++;
			}
			// TODO rest in middle of measure, ticks += duration
		}
	}
	midiToCSV.close();
}

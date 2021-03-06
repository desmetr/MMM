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
	string name = sourcePartList.scorePart.scoreInstrument.instrumentName.getInstrumentName();

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

int CSVGenerator::getTicks(Note note) {
	if (note.type.getType() == "quarter")	{
		return 3;
	}
	else if (note.type.getType() == "half")	{
		return 6;
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

        if (index >= 0) {
            volume.erase(index, numberOfSymbolsToRemove);
        }
	}
	else	{
		volume = "0";
	}

	return volume;
}

void CSVGenerator::generateCSV(string fileName) {
    ofstream musicXmlToCSV;

    musicXmlToCSV.open(Utilities::stringToCharPtr(fileName));

	int tick = 0;

    musicXmlToCSV << getHeader();
    musicXmlToCSV << getInstrument();

	for (const auto& measure : sourcePart.measures)		{
		for (unsigned int i = 0; i < measure.notes.size(); i++)			{
			if (!measure.notes[i].isRest())	{
                musicXmlToCSV << Utilities::intToString(tick);
                musicXmlToCSV << ",";
                musicXmlToCSV << getNote(measure.notes[i]);
                musicXmlToCSV << ",";
                musicXmlToCSV << getVelocityOn(measure.notes[i]);
                musicXmlToCSV << "\n";

				tick += getTicks(measure.notes[i]);
                musicXmlToCSV << Utilities::intToString(tick);
                musicXmlToCSV << ",";
                musicXmlToCSV << getNote(measure.notes[i]);
                musicXmlToCSV << ",";
                musicXmlToCSV << getVelocityOff();
                musicXmlToCSV << "\n";

				tick++;
			}
			else	{
				tick++;
				tick += getTicks(measure.notes[i]);
			}
			// TODO rest in middle of measure, ticks += duration
		}
	}
    musicXmlToCSV.close();
}

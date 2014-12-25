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

	ticks = 60000 / (BPM * PPQ);
}

CSVGenerator::CSVGenerator(PartList partList, Part part) {
	this->sourcePartList = partList;
	this->sourcePart = part;

	midiInstruments = ioManager.midiInstruments;
	midiNotes = ioManager.midiNotes;

	ticks = 60000 / (BPM * PPQ);
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

	returnString += "\n\n";
	return returnString;
}

string CSVGenerator::getTrack() {
	// Pretty useless method temporary. It is possible that the track is different.
	// For now we decide that there is only one track.
	return "1";
}

string CSVGenerator::getTick(Note note, int& tick) {
	string returnString = "";

//	if (!note.isRest())		{
		if (note.type.getType() == "quarter")	{
			tick++;
//			returnString = Utilities::intToString(tick);
			returnString = Utilities::intToString(tick * ticks);
		}
		else if (note.type.getType() == "half")	{
			tick++;
//			returnString = Utilities::intToString(tick);
			returnString = Utilities::intToString(tick * ticks);
			tick++;
		}
//	}
	return returnString;
}

string CSVGenerator::getChannel() {
	// Pretty useless method temporary. It is possible that the channel is different.
	// For now we decide that there is only one channel.
	return "0";
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

string CSVGenerator::getVelocityOff(Note note) {
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
	ofstream midiAsCSV;
	int position = fileName.find(".xml");
	fileName.erase(position, fileName.size() - position);
	fileName += ".csv";
	midiAsCSV.open(Utilities::stringToCharPtr(fileName));

	int tick = -1;
	int currentNote = 0;
	unsigned int i = 0;

	midiAsCSV << getHeader();
	midiAsCSV << getInstrument();

	for (const auto& measure : sourcePart.measures)		{
		for (i = 0; i < measure.notes.size(); i++)			{
			for (unsigned int j = 0; j < 2; j++)	{
				midiAsCSV << getTrack();
				midiAsCSV << ",";
				midiAsCSV << getTick(measure.notes[i], tick);
				midiAsCSV << ",";
				midiAsCSV << "Note_on_c";
				midiAsCSV << ",";
				midiAsCSV << Utilities::intToString(PPQ * currentNote);
				midiAsCSV << ",";
				midiAsCSV << getNote(measure.notes[i]);
				midiAsCSV << ",";
				if (j == 0)	{
					midiAsCSV << getVelocityOn(measure.notes[i]);
				}
				else 	{
					midiAsCSV << getVelocityOff(measure.notes[i]);
				}
				midiAsCSV << endl;
			}
			currentNote++;
		}
		currentNote = i;
	}
	midiAsCSV.close();
}

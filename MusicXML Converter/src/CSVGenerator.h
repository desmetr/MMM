/*
 * CSVGenerator.h
 *
 *  Created on: Dec 22, 2014
 *      Author: Rafael De Smet
 */

#ifndef CSVGENERATOR_H_
#define CSVGENERATOR_H_

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "Utilities.h"
#include "Part.h"
#include "PartList.h"
#include "Note.h"
#include "InputOutputManager.h"

class CSVGenerator {
public:
	CSVGenerator();
	CSVGenerator(PartList partList, Part part);
	virtual ~CSVGenerator();

	void generateCSV(std::string fileName);

private:
	InputOutputManager ioManager;

	Part sourcePart;
	PartList sourcePartList;

	std::map<unsigned int, std::string> midiInstruments;
	std::map<unsigned int, std::string> midiNotes;

	const int BPM = 120;		// BPM = Beats Per Minute.
	const int PPQ = 4;		// PPQ = Pulses Per Quarter note
	float ticks;

	std::string getHeader();
	std::string getInstrument();

	/// Documentation: http://www.penguinpeepshow.com/programs/csv-to-midi-converter/
	/// Documentation: http://www.fourmilab.ch/webtools/midicsv/

	std::string getTrack();

	// The tick number determines where in the song the note will be placed.
	// For example, if the timing resolution is 4 pulses per quarter note, a tick number of 20 will put the note 5 quarter notes after the start of the song.
	// Tick numbers start at 0.
	// TODO tick aanpassen
	std::string getTick(Note note, int& tick);

	std::string getChannel();

	// The note number is the note to play. This number can range from 0 to 127. Where 0 is C-1 and 127 is G9.
	std::string getNote(Note note);

	// The velocity number is like the volume of the note. The higher the velocity the higher the volume.
	// This number can range from 0 to 127.
	// By velocity off I mean what happens when the note stops playing; the velocity (volume) is 0.
	std::string getVelocityOff(Note note);

	// Same as velocityOff, but now we get what happens when the note is played.
	std::string getVelocityOn(Note note);
};

#endif /* CSVGENERATOR_H_ */

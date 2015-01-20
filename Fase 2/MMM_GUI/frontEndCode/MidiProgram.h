/*
 * MidiProgram.h
 *
 *  Created on: Dec 18, 2014
 *      Author: Rafael De Smet
 */

#ifndef MIDIPROGRAM_H_
#define MIDIPROGRAM_H_

#include <string>
#include <iostream>

class MidiProgram {
public:
	MidiProgram();
	virtual ~MidiProgram();

	const std::string& getMidiProgram() const;
	const std::string& getTagName() const;

	void setMidiProgram(const std::string& midiProgram);

	void print();

private:
	std::string midiProgram;

	std::string tagName = "midi-program";
//	const std::string tagName = "midi-program";
};

#endif /* MIDIPROGRAM_H_ */

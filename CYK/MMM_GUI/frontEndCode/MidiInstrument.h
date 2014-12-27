/*
 * MidiInstrument.h
 *
 *  Created on: Dec 15, 2014
 *      Author: Rafael De Smet
 */

#ifndef MIDIINSTRUMENT_H_
#define MIDIINSTRUMENT_H_

#include <string>
#include <iostream>
#include "MidiChannel.h"
#include "MidiProgram.h"
#include "Volume.h"
#include "Pan.h"

class MidiInstrument {
public:
	MidiInstrument();
	virtual ~MidiInstrument();

	MidiChannel midiChannel;
	MidiProgram midiProgram;
	Volume volume;
	Pan pan;

	const std::string& getId() const;
	const std::string& getTagName() const;

	void setId(const std::string& id);

	void print();

private:
	std::string id;

	std::string tagName = "midi-instrument";
//	const std::string tagName = "midi-instrument";
};

#endif /* MIDIINSTRUMENT_H_ */

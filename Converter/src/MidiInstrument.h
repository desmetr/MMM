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

class MidiInstrument {
public:
	MidiInstrument();
	virtual ~MidiInstrument();

	const std::string& getId() const;
	const std::string& getMidiChannel() const;
	const std::string& getMidiProgram() const;
	const std::string& getPan() const;
	const std::string& getTagName() const;
	const std::string& getVolume() const;

	void setId(const std::string& id);
	void setMidiChannel(const std::string& midiChannel);
	void setMidiProgram(const std::string& midiProgram);
	void setPan(const std::string& pan);
	void setVolume(const std::string& volume);

	void print();

private:
	std::string id;
	std::string midiChannel;
	std::string midiProgram;
	std::string volume;
	std::string pan;

	const std::string tagName;
};

#endif /* MIDIINSTRUMENT_H_ */

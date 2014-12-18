/*
 * MidiChannel.h
 *
 *  Created on: Dec 18, 2014
 *      Author: Rafael De Smet
 */

#ifndef MIDICHANNEL_H_
#define MIDICHANNEL_H_

#include <string>
#include <iostream>

class MidiChannel {
public:
	MidiChannel();
	virtual ~MidiChannel();

	const std::string& getMidiChannel() const;
	const std::string& getTagName() const;

	void setMidiChannel(const std::string& midiChannel);

	void print();

private:
	std::string midiChannel;

	std::string tagName = "midi-channel";
//	const std::string tagName = "midi-channel";
};

#endif /* MIDICHANNEL_H_ */

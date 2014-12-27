/*
 * InputOutputManager.h
 *
 *  Created on: Dec 22, 2014
 *      Author: Rafael De Smet
 */

#ifndef INPUTOUTPUTMANAGER_H_
#define INPUTOUTPUTMANAGER_H_

#include <iostream>
#include <map>
#include <string>
#include <fstream>

class InputOutputManager {
public:
	InputOutputManager();
	virtual ~InputOutputManager();

	std::map<unsigned int, std::string> midiInstruments;
	std::map<unsigned int, std::string> midiNotes;

private:
	void readInstruments();
	void readNotes();
};

#endif /* INPUTOUTPUTMANAGER_H_ */

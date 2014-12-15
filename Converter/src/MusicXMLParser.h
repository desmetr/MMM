/*
 * MusicXMLParser.h
 *
 *  Created on: Dec 15, 2014
 *      Author: Rafael De Smet
 */

#ifndef MUSICXMLPARSER_H_
#define MUSICXMLPARSER_H_

#include <iostream>
#include <stdexcept>
#include <string>
#include "tinyxml2.h"
#include "ScorePart.h"
#include "PartList.h"
#include "ScoreInstrument.h"
#include "MidiInstrument.h"

enum SuccessEnum {FAILURE, SUCCESS};

class MusicXMLParser {
public:
	MusicXMLParser();
	virtual ~MusicXMLParser();

	SuccessEnum parse(std::string fileName);

private:
	PartList partList;
	ScorePart scorePart;
	ScoreInstrument scoreInstrument;
	MidiInstrument midiInstrument;
};

#endif /* MUSICXMLPARSER_H_ */

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
#include "Part.h"

/*
 * This class parses a MusicXML file and stores the info accordingly in a class structure.
 * This class structure is needed for the conversion from MusicXML to MEI.
 *
 * TODO file with rests only show one measure
 */

enum SuccessEnum {FAILURE, SUCCESS};

class MusicXMLParser {
public:
	MusicXMLParser();
	virtual ~MusicXMLParser();

	SuccessEnum parse(std::string fileName);

	void print();

private:
	PartList partList;
	Part part;
};

#endif /* MUSICXMLPARSER_H_ */

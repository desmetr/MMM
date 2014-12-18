/*
 * MusicXMLGenerator.h
 *
 *  Created on: Dec 18, 2014
 *      Author: Rafael De Smet
 */

#ifndef MUSICXMLGENERATOR_H_
#define MUSICXMLGENERATOR_H_

#include <string>
#include <iostream>
#include "tinyxml2.h"
#include "MusicXMLParser.h"
#include "Part.h"
#include "PartList.h"
#include "Utilities.h"

class MusicXMLGenerator {
public:
	MusicXMLGenerator();
	MusicXMLGenerator(PartList partList, Part part);
	virtual ~MusicXMLGenerator();

	void generateMusicXML();
//	void generateMusicXML(MEI meiDocument);

private:
	Part part;
	PartList partList;

	tinyxml2::XMLDocument xmlDoc;

	void generateChildrenOfPartList(tinyxml2::XMLElement xmlElement);
	void generateChildrenOfPart(tinyxml2::XMLElement& xmlElement);
};

#endif /* MUSICXMLGENERATOR_H_ */

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

	void generateMusicXML(std::string fileName);

private:
	Part sourcePart;
	PartList sourcePartList;

	tinyxml2::XMLDocument xmlDoc;

	tinyxml2::XMLDeclaration* getDeclaration();
//	tinyxml2::XMLUnknown* getDocType();

	tinyxml2::XMLElement* getPartList();
	tinyxml2::XMLElement* getScorePart();
	tinyxml2::XMLElement* getPartName();
	tinyxml2::XMLElement* getScoreInstrument();
	tinyxml2::XMLElement* getInstrumentName();
	tinyxml2::XMLElement* getMidiInstrument();
	tinyxml2::XMLElement* getMidiChannel();
	tinyxml2::XMLElement* getMidiProgram();
	tinyxml2::XMLElement* getVolume();
	tinyxml2::XMLElement* getPan();

	tinyxml2::XMLElement* getPart();
	tinyxml2::XMLElement* getMeasureElement(Measure currentMeasure);

	tinyxml2::XMLElement* getAttribute(Measure currentMeasure);
	tinyxml2::XMLElement* getDivisions(Measure currentMeasure);
	tinyxml2::XMLElement* getKey(Measure currentMeasure);
	tinyxml2::XMLElement* getFifths(Measure currentMeasure);
	tinyxml2::XMLElement* getMode(Measure currentMeasure);
	tinyxml2::XMLElement* getTime(Measure currentMeasure);
	tinyxml2::XMLElement* getBeats(Measure currentMeasure);
	tinyxml2::XMLElement* getBeatType(Measure currentMeasure);
	tinyxml2::XMLElement* getClef(Measure currentMeasure);
	tinyxml2::XMLElement* getSign(Measure currentMeasure);
	tinyxml2::XMLElement* getLine(Measure currentMeasure);

	tinyxml2::XMLElement* getNote(Note currentNote);
	tinyxml2::XMLElement* getPitch(Note currentNote);
	tinyxml2::XMLElement* getStep(Note currentNote);
	tinyxml2::XMLElement* getOctave(Note currentNote);
	tinyxml2::XMLElement* getDuration(Note currentNote);
	tinyxml2::XMLElement* getVoice(Note currentNote);
	tinyxml2::XMLElement* getType(Note currentNote);
	tinyxml2::XMLElement* getStem(Note currentNote);
	tinyxml2::XMLElement* getRest(Note currentNote);

	tinyxml2::XMLElement* getBarLine(Measure currentMeasure);
	tinyxml2::XMLElement* getBarStyle(Measure currentMeasure);
};

#endif /* MUSICXMLGENERATOR_H_ */

/*
 * TODO declaration and doctype
 * 	XMLNode* previousElement;
	previousElement = xmlDoc.InsertFirstChild(xmlDoc.NewDeclaration());
	cout << previousElement->Value() << endl;
 */

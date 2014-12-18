/*
 * MusicXMLGenerator.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: Rafael De Smet
 */

#include "MusicXMLGenerator.h"

using namespace std;
using namespace tinyxml2;

MusicXMLGenerator::MusicXMLGenerator() {
}

MusicXMLGenerator::MusicXMLGenerator(PartList partList, Part part) {
	this->partList = partList;
	this->part = part;
}

MusicXMLGenerator::~MusicXMLGenerator() {
}

void MusicXMLGenerator::generateMusicXML() {
	// The root of a MusicXML file is always "score-partwise". So this is mandatory for every file we want to generate.
	XMLNode* root = xmlDoc.NewElement("score-partwise");
	xmlDoc.InsertFirstChild(root);

	// The first child of the root, tag = part-list.
	XMLElement* partListElement = xmlDoc.NewElement(Utilities::stringToCharPtr(partList.getTagName()));
	root->InsertFirstChild(partListElement);

	generateChildrenOfPartList(*partListElement);

	// The second and last child of the root, tag = part.
	XMLElement* partElement = xmlDoc.NewElement(Utilities::stringToCharPtr(part.getTagName()));
	root->InsertAfterChild(partListElement, partElement);

	generateChildrenOfPart(*partElement);

	xmlDoc.SaveFile("MusicXMLFile.xml");
}

void MusicXMLGenerator::generateChildrenOfPartList(XMLElement& xmlElement) {
	// Use all members of partList and generate the correct xml tags and text.
	XMLElement* scorePartElement = xmlDoc.NewElement(Utilities::stringToCharPtr(partList.scorePart.getTagName()));
	scorePartElement->SetAttribute("id", Utilities::stringToCharPtr(partList.scorePart.getId()));
	xmlElement.InsertFirstChild(scorePartElement);

	// Generate the children of scorePart.
	// tag = part-name
	XMLElement* partNameElement = xmlDoc.NewElement(Utilities::stringToCharPtr(partList.scorePart.partName.getTagName()));
	partNameElement->SetText(Utilities::stringToCharPtr(partList.scorePart.partName.getName()));
	scorePartElement->InsertFirstChild(partNameElement);

	// tag = score-instrument
	XMLElement* scoreInstrumentElement = xmlDoc.NewElement(Utilities::stringToCharPtr(partList.scorePart.scoreInstrument.getTagName()));
	scoreInstrumentElement->SetAttribute("id", Utilities::stringToCharPtr(partList.scorePart.scoreInstrument.getId()));
	scorePartElement->InsertAfterChild(partNameElement, scoreInstrumentElement);

	// Generate the children of scoreInstrument.
	// tag = instrument-name
	XMLElement* instrumentNameElement = xmlDoc.NewElement(Utilities::stringToCharPtr(partList.scorePart.scoreInstrument.instrumentName.getTagName()));
	instrumentNameElement->SetText(Utilities::stringToCharPtr(partList.scorePart.scoreInstrument.instrumentName.getInstrumentName()));
	scoreInstrumentElement->InsertFirstChild(instrumentNameElement);

	// Generate the rest of the children of scorePart.
	// tag = midi-instrument
	XMLElement* midiInstrumentElement = xmlDoc.NewElement(Utilities::stringToCharPtr(partList.scorePart.midiInstrument.getTagName()));
	midiInstrumentElement->SetAttribute("id", Utilities::stringToCharPtr((partList.scorePart.midiInstrument.getId())));
	scorePartElement->InsertAfterChild(scoreInstrumentElement, midiInstrumentElement);

	// Generate the children of midiInstrument.
	// tag = midi-channel
	XMLElement* midiChannelElement = xmlDoc.NewElement(Utilities::stringToCharPtr(partList.scorePart.midiInstrument.midiChannel.getTagName()));
	midiChannelElement->SetText(Utilities::stringToCharPtr(partList.scorePart.midiInstrument.midiChannel.getMidiChannel()));
	midiInstrumentElement->InsertFirstChild(midiChannelElement);

	// tag = midi-program
	XMLElement* midiPogramElement = xmlDoc.NewElement(Utilities::stringToCharPtr(partList.scorePart.midiInstrument.midiProgram.getTagName()));
	midiPogramElement->SetText(Utilities::stringToCharPtr(partList.scorePart.midiInstrument.midiProgram.getMidiProgram()));
	midiInstrumentElement->InsertAfterChild(midiChannelElement, midiPogramElement);

	// tag = volume
	XMLElement* volumeElement = xmlDoc.NewElement(Utilities::stringToCharPtr(partList.scorePart.midiInstrument.volume.getTagName()));
	volumeElement->SetText(Utilities::stringToCharPtr(partList.scorePart.midiInstrument.volume.getVolume()));
	midiInstrumentElement->InsertAfterChild(midiPogramElement, volumeElement);

	// tag = pan
	XMLElement* panElement = xmlDoc.NewElement(Utilities::stringToCharPtr(partList.scorePart.midiInstrument.pan.getTagName()));
	panElement->SetText(Utilities::stringToCharPtr(partList.scorePart.midiInstrument.pan.getPan()));
	midiInstrumentElement->InsertAfterChild(volumeElement, panElement);
}

void MusicXMLGenerator::generateChildrenOfPart(XMLElement& xmlElement) {
}

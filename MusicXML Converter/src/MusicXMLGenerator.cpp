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
	this->sourcePartList = partList;
	this->sourcePart = part;
}

MusicXMLGenerator::~MusicXMLGenerator() {
}

XMLDeclaration* MusicXMLGenerator::getDeclaration() {
	return xmlDoc.NewDeclaration();
}

// Doens't work, maybe not neccessary anymore.
//XMLUnknown* MusicXMLGenerator::getDocType() {
//	XMLUnknown* docType = xmlDoc.NewUnknown("DOCTYPE");
//	docType->("score-partwise PUBLIC \"-//Recordare//DTD MusicXML 2.0 Partwise//EN\" \"http://www.musicxml.org/dtds/partwise.dtd\">");
//	return docType;
//}

XMLElement* MusicXMLGenerator::getPartName() {
	XMLElement* partNameElement = xmlDoc.NewElement(Utilities::stringToCharPtr(sourcePartList.scorePart.partName.getTagName()));

	partNameElement->SetText(Utilities::stringToCharPtr(sourcePartList.scorePart.partName.getName()));

	return partNameElement;
}

XMLElement* MusicXMLGenerator::getPartList() {
	XMLElement* partListElement = xmlDoc.NewElement(Utilities::stringToCharPtr(sourcePartList.getTagName()));

	partListElement->InsertFirstChild(getScorePart());

	return partListElement;
}

XMLElement* MusicXMLGenerator::getScorePart() {
	XMLElement* scorePartElement = xmlDoc.NewElement(Utilities::stringToCharPtr(sourcePartList.scorePart.getTagName()));
	XMLNode* previousElement;

	scorePartElement->SetAttribute("id", Utilities::stringToCharPtr(sourcePartList.scorePart.getId()));
	previousElement = scorePartElement->InsertFirstChild(getPartName());
	previousElement = scorePartElement->InsertAfterChild(previousElement, getScoreInstrument());
	previousElement = scorePartElement->InsertAfterChild(previousElement, getMidiInstrument());

	return scorePartElement;
}

XMLElement* MusicXMLGenerator::getScoreInstrument() {
	XMLElement* scoreInstrumentElement = xmlDoc.NewElement(Utilities::stringToCharPtr(sourcePartList.scorePart.scoreInstrument.getTagName()));

	scoreInstrumentElement->SetAttribute("id", Utilities::stringToCharPtr(sourcePartList.scorePart.scoreInstrument.getId()));
	scoreInstrumentElement->InsertFirstChild(getInstrumentName());

	return scoreInstrumentElement;
}

XMLElement* MusicXMLGenerator::getInstrumentName() {
	XMLElement* instrumentNameElement = xmlDoc.NewElement(Utilities::stringToCharPtr(sourcePartList.scorePart.scoreInstrument.instrumentName.getTagName()));

	instrumentNameElement->SetText(Utilities::stringToCharPtr(sourcePartList.scorePart.scoreInstrument.instrumentName.getInstrumentName()));

	return instrumentNameElement;
}

XMLElement* MusicXMLGenerator::getMidiInstrument() {
	XMLElement* midiInstrumentElement = xmlDoc.NewElement(Utilities::stringToCharPtr(sourcePartList.scorePart.midiInstrument.getTagName()));
	XMLNode* previousElement;

	midiInstrumentElement->SetAttribute("id", Utilities::stringToCharPtr((sourcePartList.scorePart.midiInstrument.getId())));
	previousElement = midiInstrumentElement->InsertFirstChild(getMidiChannel());
	previousElement = midiInstrumentElement->InsertAfterChild(previousElement, getMidiProgram());
	previousElement = midiInstrumentElement->InsertAfterChild(previousElement, getVolume());
	midiInstrumentElement->InsertEndChild(getPan());

	return midiInstrumentElement;
}

XMLElement* MusicXMLGenerator::getMidiChannel() {
	XMLElement* midiChannelElement = xmlDoc.NewElement(Utilities::stringToCharPtr(sourcePartList.scorePart.midiInstrument.midiChannel.getTagName()));

	midiChannelElement->SetText(Utilities::stringToCharPtr(sourcePartList.scorePart.midiInstrument.midiChannel.getMidiChannel()));

	return midiChannelElement;
}

XMLElement* MusicXMLGenerator::getMidiProgram() {
	XMLElement* midiPogramElement = xmlDoc.NewElement(Utilities::stringToCharPtr(sourcePartList.scorePart.midiInstrument.midiProgram.getTagName()));

	midiPogramElement->SetText(Utilities::stringToCharPtr(sourcePartList.scorePart.midiInstrument.midiProgram.getMidiProgram()));

	return midiPogramElement;
}

XMLElement* MusicXMLGenerator::getVolume() {
	XMLElement* volumeElement = xmlDoc.NewElement(Utilities::stringToCharPtr(sourcePartList.scorePart.midiInstrument.volume.getTagName()));

	volumeElement->SetText(Utilities::stringToCharPtr(sourcePartList.scorePart.midiInstrument.volume.getVolume()));

	return volumeElement;
}

tinyxml2::XMLElement* MusicXMLGenerator::getPan() {
	XMLElement* panElement = xmlDoc.NewElement(Utilities::stringToCharPtr(sourcePartList.scorePart.midiInstrument.pan.getTagName()));

	panElement->SetText(Utilities::stringToCharPtr(sourcePartList.scorePart.midiInstrument.pan.getPan()));

	return panElement;
}

XMLElement* MusicXMLGenerator::getPart() {
	XMLElement* partElement = xmlDoc.NewElement(Utilities::stringToCharPtr(sourcePart.getTagName()));

	partElement->SetAttribute("id", Utilities::stringToCharPtr(sourcePart.getId()));

	// First element of the vector;
	XMLNode* previousElement;
	previousElement = partElement->InsertFirstChild(getMeasureElement(sourcePart.measures[0]));
	for (unsigned int i = 1; i < sourcePart.measures.size(); i++)	{
		previousElement = partElement->InsertAfterChild(previousElement, getMeasureElement(sourcePart.measures[i]));
	}

	return partElement;
}

XMLElement* MusicXMLGenerator::getMeasureElement(Measure currentMeasure) {
	XMLElement* measureElement = xmlDoc.NewElement(Utilities::stringToCharPtr(currentMeasure.getTagName()));

	measureElement->SetAttribute("number", Utilities::stringToCharPtr(currentMeasure.getNumber()));
	if (currentMeasure.attribute.division.getDivisions() != "")	{
		XMLNode* previousElement;
		previousElement = measureElement->InsertFirstChild(getAttribute(currentMeasure));

		// First element of the vector;
		previousElement = measureElement->InsertAfterChild(previousElement, getNote(currentMeasure.notes[0]));
		for (unsigned int i = 1; i < currentMeasure.notes.size(); i++)	{
			previousElement = measureElement->InsertAfterChild(previousElement, getNote(currentMeasure.notes[i]));
		}
	}
	else	{
		// First element of the vector;
		XMLNode* previousElement;
		previousElement = measureElement->InsertFirstChild(getNote(currentMeasure.notes[0]));
		for (unsigned int i = 1; i < currentMeasure.notes.size(); i++)	{
			previousElement = measureElement->InsertAfterChild(previousElement, getNote(currentMeasure.notes[i]));
		}
	}
	if (currentMeasure.barLine.getLocation() != "")	{
		measureElement->InsertEndChild(getBarLine(currentMeasure));
	}

	return measureElement;
}

XMLElement* MusicXMLGenerator::getAttribute(Measure currentMeasure) {
	XMLElement* attributeElement = xmlDoc.NewElement(Utilities::stringToCharPtr(currentMeasure.attribute.getTagName()));
	XMLNode* previousElement;

	previousElement = attributeElement->InsertFirstChild(getDivisions(currentMeasure));
	previousElement = attributeElement->InsertAfterChild(previousElement, getKey(currentMeasure));
	previousElement = attributeElement->InsertAfterChild(previousElement, getTime(currentMeasure));
	attributeElement->InsertEndChild(getClef(currentMeasure));

	return attributeElement;
}

XMLElement* MusicXMLGenerator::getDivisions(Measure currentMeasure) {
	XMLElement* divisionsElement = xmlDoc.NewElement(Utilities::stringToCharPtr(currentMeasure.attribute.division.getTagName()));

	divisionsElement->SetText(Utilities::stringToCharPtr(currentMeasure.attribute.division.getDivisions()));

	return divisionsElement;
}

XMLElement* MusicXMLGenerator::getKey(Measure currentMeasure) {
	XMLElement* keyElement = xmlDoc.NewElement(Utilities::stringToCharPtr(currentMeasure.attribute.key.getTagName()));

	keyElement->InsertFirstChild(getFifths(currentMeasure));
	keyElement->InsertEndChild(getMode(currentMeasure));

	return keyElement;
}

XMLElement* MusicXMLGenerator::getFifths(Measure currentMeasure) {
	XMLElement* fifthsElement = xmlDoc.NewElement(Utilities::stringToCharPtr(currentMeasure.attribute.key.fifths.getTagName()));

	fifthsElement->SetText(Utilities::stringToCharPtr(currentMeasure.attribute.key.fifths.getFifths()));

	return fifthsElement;
}

XMLElement* MusicXMLGenerator::getMode(Measure currentMeasure) {
	XMLElement* modeElement = xmlDoc.NewElement(Utilities::stringToCharPtr(currentMeasure.attribute.key.mode.getTagName()));

	modeElement->SetText(Utilities::stringToCharPtr(currentMeasure.attribute.key.mode.getMode()));

	return modeElement;
}

XMLElement* MusicXMLGenerator::getTime(Measure currentMeasure) {
	XMLElement* timeElement = xmlDoc.NewElement(Utilities::stringToCharPtr(currentMeasure.attribute.time.getTagName()));

	timeElement->InsertFirstChild(getBeats(currentMeasure));
	timeElement->InsertEndChild(getBeatType(currentMeasure));

	return timeElement;
}

XMLElement* MusicXMLGenerator::getBeats(Measure currentMeasure) {
	XMLElement* beatsElement = xmlDoc.NewElement(Utilities::stringToCharPtr(currentMeasure.attribute.time.beats.getTagName()));

	beatsElement->SetText(Utilities::stringToCharPtr(currentMeasure.attribute.time.beats.getBeats()));

	return beatsElement;
}

XMLElement* MusicXMLGenerator::getBeatType(Measure currentMeasure) {
	XMLElement* beatTypeElement = xmlDoc.NewElement(Utilities::stringToCharPtr(currentMeasure.attribute.time.beatType.getTagName()));

	beatTypeElement->SetText(Utilities::stringToCharPtr(currentMeasure.attribute.time.beatType.getBeatType()));

	return beatTypeElement;
}

XMLElement* MusicXMLGenerator::getClef(Measure currentMeasure) {
	XMLElement* clefElement = xmlDoc.NewElement(Utilities::stringToCharPtr(currentMeasure.attribute.clef.getTagName()));

	clefElement->InsertFirstChild(getSign(currentMeasure));
	clefElement->InsertEndChild(getLine(currentMeasure));

	return clefElement;
}

XMLElement* MusicXMLGenerator::getSign(Measure currentMeasure) {
	XMLElement* signElement = xmlDoc.NewElement(Utilities::stringToCharPtr(currentMeasure.attribute.clef.sign.getTagName()));

	signElement->SetText(Utilities::stringToCharPtr(currentMeasure.attribute.clef.sign.getSign()));

	return signElement;
}

XMLElement* MusicXMLGenerator::getLine(Measure currentMeasure) {
	XMLElement* lineElement = xmlDoc.NewElement(Utilities::stringToCharPtr(currentMeasure.attribute.clef.line.getTagName()));

	lineElement->SetText(Utilities::stringToCharPtr(currentMeasure.attribute.clef.line.getLine()));

	return lineElement;
}

XMLElement* MusicXMLGenerator::getNote(Note currentNote) {
	XMLElement* noteElement = xmlDoc.NewElement(Utilities::stringToCharPtr(currentNote.getTagName()));
	XMLNode* previousElement;

	if (currentNote.isRest())	{
		previousElement = noteElement->InsertFirstChild(getRest(currentNote));
		previousElement = noteElement->InsertAfterChild(previousElement, getDuration(currentNote));
		previousElement = noteElement->InsertAfterChild(previousElement, getVoice(currentNote));
		previousElement = noteElement->InsertAfterChild(previousElement, getType(currentNote));
	}
	else	{
		noteElement->SetAttribute("default-x", Utilities::stringToCharPtr(currentNote.getDefaultX()));
		noteElement->SetAttribute("default-y", Utilities::stringToCharPtr(currentNote.getDefaultY()));
		previousElement = noteElement->InsertFirstChild(getPitch(currentNote));
		previousElement = noteElement->InsertAfterChild(previousElement, getDuration(currentNote));
		previousElement = noteElement->InsertAfterChild(previousElement, getVoice(currentNote));
		previousElement = noteElement->InsertAfterChild(previousElement, getType(currentNote));
		noteElement->InsertEndChild(getStem(currentNote));
	}

	return noteElement;
}

XMLElement* MusicXMLGenerator::getPitch(Note currentNote) {
	XMLElement* pitchElement = xmlDoc.NewElement(Utilities::stringToCharPtr(currentNote.pitch.getTagName()));

	pitchElement->InsertFirstChild(getStep(currentNote));
	pitchElement->InsertEndChild(getOctave(currentNote));

	return pitchElement;
}

XMLElement* MusicXMLGenerator::getStep(Note currentNote) {
	XMLElement* stepElement = xmlDoc.NewElement(Utilities::stringToCharPtr(currentNote.pitch.step.getTagName()));

	stepElement->SetText(Utilities::stringToCharPtr(currentNote.pitch.step.getStep()));

	return stepElement;
}

XMLElement* MusicXMLGenerator::getOctave(Note currentNote) {
	XMLElement* octaveElement = xmlDoc.NewElement(Utilities::stringToCharPtr(currentNote.pitch.octave.getTagName()));

	octaveElement->SetText(Utilities::stringToCharPtr(currentNote.pitch.octave.getOctave()));

	return octaveElement;
}

XMLElement* MusicXMLGenerator::getDuration(Note currentNote) {
	XMLElement* durationElement = xmlDoc.NewElement(Utilities::stringToCharPtr(currentNote.duration.getTagName()));

	durationElement->SetText(Utilities::stringToCharPtr(currentNote.duration.getDuration()));

	return durationElement;
}

XMLElement* MusicXMLGenerator::getVoice(Note currentNote) {
	XMLElement* voiceElement = xmlDoc.NewElement(Utilities::stringToCharPtr(currentNote.voice.getTagName()));

	voiceElement->SetText(Utilities::stringToCharPtr(currentNote.voice.getVoice()));

	return voiceElement;
}

XMLElement* MusicXMLGenerator::getType(Note currentNote) {
	XMLElement* typeElement = xmlDoc.NewElement(Utilities::stringToCharPtr(currentNote.type.getTagName()));

	typeElement->SetText(Utilities::stringToCharPtr(currentNote.type.getType()));

	return typeElement;
}

XMLElement* MusicXMLGenerator::getStem(Note currentNote) {
	XMLElement* stemElement = xmlDoc.NewElement(Utilities::stringToCharPtr(currentNote.stem.getTagName()));

	stemElement->SetText(Utilities::stringToCharPtr(currentNote.stem.getStem()));

	return stemElement;
}

XMLElement* MusicXMLGenerator::getRest(Note currentNote) {
	if (currentNote.isRest())	{
		XMLElement* restElement = xmlDoc.NewElement("rest");
		return restElement;
	}
}

XMLElement* MusicXMLGenerator::getBarLine(Measure currentMeasure) {
	XMLElement* barLineElement = xmlDoc.NewElement(Utilities::stringToCharPtr(currentMeasure.barLine.getTagName()));

	barLineElement->SetAttribute("location", Utilities::stringToCharPtr(currentMeasure.barLine.getLocation()));
	barLineElement->InsertFirstChild(getBarStyle(currentMeasure));

	return barLineElement;
}

XMLElement* MusicXMLGenerator::getBarStyle(Measure currentMeasure) {
	XMLElement* barStyleElement = xmlDoc.NewElement(Utilities::stringToCharPtr(currentMeasure.barLine.barStyle.getTagName()));

	barStyleElement->SetText(Utilities::stringToCharPtr(currentMeasure.barLine.barStyle.getBarStyle()));

	return barStyleElement;
}

void MusicXMLGenerator::generateMusicXML(string fileName) {
	// The root of a MusicXML file is always "score-partwise". So this is mandatory for every file we want to generate.

	XMLNode* root = xmlDoc.NewElement("score-partwise");
	XMLNode* previousElement;

	previousElement = root->InsertFirstChild(getPartList());
	previousElement = root->InsertAfterChild(previousElement, getPart());

	xmlDoc.InsertFirstChild(root);
//	xmlDoc.InsertFirstChild(getDocType());
	xmlDoc.InsertFirstChild(getDeclaration());

	int position = fileName.find(".xml");
	fileName.insert(position, "AsMusicXML");
	xmlDoc.SaveFile(Utilities::stringToCharPtr(fileName));
}

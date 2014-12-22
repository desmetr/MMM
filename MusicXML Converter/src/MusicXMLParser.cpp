/*
 * MusicXMLParser.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: Rafael De Smet
 */

#include "MusicXMLParser.h"

using namespace std;
using namespace tinyxml2;

MusicXMLParser::MusicXMLParser() {
}

MusicXMLParser::~MusicXMLParser() {
}

const Part& MusicXMLParser::getPart() const 			{	return part;		}
const PartList& MusicXMLParser::getPartList() const 	{	return partList;	}

SuccessEnum MusicXMLParser::parse(string fileName) {
	XMLDocument doc;
	XMLElement* root;

	try	{
		doc.LoadFile(fileName.c_str());
		if (doc.ErrorID() != 0)		{
			throw runtime_error("File could not be opened.");
		}

		root = doc.FirstChildElement();
		checkElement(root);
	}
	catch (exception& e)	{
		cout << e.what() << endl;
		return FAILURE;
	}

	try	{
		string rootValue = root->Value();
		if (rootValue == "score-partwise")	{
			for (XMLElement* elem = root->FirstChildElement(); elem != nullptr; elem = elem->NextSiblingElement())	{
				checkElement(elem);

				string elemName = elem->Value();

				// Parse the first block, parent = part-list.
				if (elemName == "part-list")	{
					for (XMLElement* partListElem = elem->FirstChildElement(); partListElem != nullptr; partListElem = partListElem->NextSiblingElement())	{
						checkElement(partListElem);

						string partListElemName = partListElem->Value();

						if (partListElemName == "score-part")	{
							const char* id = partListElem->Attribute("id");
							partList.scorePart.setId(id);

							for (XMLElement* scorePartElem = partListElem->FirstChildElement(); scorePartElem != nullptr; scorePartElem = scorePartElem->NextSiblingElement())	{
								checkElement(scorePartElem);
								string scorePartElemName = scorePartElem->Value();

								if (scorePartElemName == "part-name")	{
									partList.scorePart.partName.setName(scorePartElem->GetText());
								}
								if (scorePartElemName == "score-instrument")	{
									const char* id = scorePartElem->Attribute("id");
									partList.scorePart.scoreInstrument.setId(id);

									for (XMLElement* instrumentNameElem = scorePartElem->FirstChildElement(); instrumentNameElem != nullptr; instrumentNameElem = instrumentNameElem->NextSiblingElement())	{
										checkElement(instrumentNameElem);

										string instrumentNameElemName = instrumentNameElem->Value();

										if (instrumentNameElemName == "instrument-name")	{
											partList.scorePart.scoreInstrument.instrumentName.setInstrumentName(instrumentNameElem->GetText());
										}
									}
								}
								if (scorePartElemName == "midi-instrument")		{
									const char* id = scorePartElem->Attribute("id");
									partList.scorePart.midiInstrument.setId(id);

									for (XMLElement* midiInstrumentElem = scorePartElem->FirstChildElement(); midiInstrumentElem != nullptr; midiInstrumentElem = midiInstrumentElem->NextSiblingElement())		{
										checkElement(midiInstrumentElem);

										string midiInstrumentElemName = midiInstrumentElem->Value();

										if (midiInstrumentElemName == "midi-channel")	{
											partList.scorePart.midiInstrument.midiChannel.setMidiChannel(midiInstrumentElem->GetText());
										}
										if (midiInstrumentElemName == "midi-program")	{
											partList.scorePart.midiInstrument.midiProgram.setMidiProgram(midiInstrumentElem->GetText());
										}
										if (midiInstrumentElemName == "volume")	{
											partList.scorePart.midiInstrument.volume.setVolume(midiInstrumentElem->GetText());
										}
										if (midiInstrumentElemName == "pan")	{
											partList.scorePart.midiInstrument.pan.setPan(midiInstrumentElem->GetText());
										}
									}
								}
							}
						}
					}
				}

				// Parse the second block, parent = part.
				if (elemName == "part")	{
					const char* partID = elem->Attribute("id");
					part.setId(partID);

					for (XMLElement* partElem = elem->FirstChildElement(); partElem != nullptr; partElem = partElem->NextSiblingElement())	{
						checkElement(partElem);

						string partElemName = partElem->Value();

						Measure tempMeasure;
						if (partElemName == "measure")	{
							const char* measureNumber = partElem->Attribute("number");
							tempMeasure.setNumber(measureNumber);

							for (XMLElement* measureElem = partElem->FirstChildElement(); measureElem != nullptr; measureElem = measureElem->NextSiblingElement())	{
								checkElement(measureElem);

								string measureElemName = measureElem->Value();

								if (measureElemName == "attributes")	{
									for (XMLElement* attributeElem = measureElem->FirstChildElement(); attributeElem != nullptr; attributeElem = attributeElem->NextSiblingElement())	{
										checkElement(attributeElem);

										string attributeElemName = attributeElem->Value();

										if (attributeElemName == "divisions")	{
											tempMeasure.attribute.division.setDivisions(attributeElem->GetText());
										}
										if (attributeElemName == "key")	{
											for (XMLElement* keyElem = attributeElem->FirstChildElement(); keyElem != nullptr; keyElem = keyElem->NextSiblingElement())	{
												checkElement(keyElem);

												string keyElemName = keyElem->Value();

												if (keyElemName == "fifths")	{
													tempMeasure.attribute.key.fifths.setFifths(keyElem->GetText());
												}
												if (keyElemName == "mode")	{
													tempMeasure.attribute.key.mode.setMode(keyElem->GetText());
												}
											}
										}
										if (attributeElemName == "time")	{
											for (XMLElement* timeElem = attributeElem->FirstChildElement(); timeElem != nullptr; timeElem = timeElem->NextSiblingElement())	{
												checkElement(timeElem);

												string timeElemName = timeElem->Value();

												if (timeElemName == "beats")	{
													tempMeasure.attribute.time.beats.setBeats(timeElem->GetText());
												}
												if (timeElemName == "beat-type")	{
													tempMeasure.attribute.time.beatType.setBeatType(timeElem->GetText());
												}
											}
										}
										if (attributeElemName == "clef")	{
											for (XMLElement* clefElem = attributeElem->FirstChildElement(); clefElem != nullptr; clefElem = clefElem->NextSiblingElement())	{
												checkElement(clefElem);

												string clefElemName = clefElem->Value();

												if (clefElemName == "sign")	{
													tempMeasure.attribute.clef.sign.setSign(clefElem->GetText());
												}
												if (clefElemName == "line")	{
													tempMeasure.attribute.clef.line.setLine(clefElem->GetText());
												}
											}
										}
									}
								}
								if (measureElemName == "note")	{
									Note tempNote;

									for (XMLElement* noteElem = measureElem->FirstChildElement(); noteElem != nullptr; noteElem = noteElem->NextSiblingElement())	{
										checkElement(noteElem);

										string noteElemName = noteElem->Value();

										if (noteElemName == "rest")	{
											tempNote.setRest(true);
										}
										if (noteElemName == "duration")	{
											tempNote.duration.setDuration(noteElem->GetText());
										}
										if (noteElemName == "voice")	{
											tempNote.voice.setVoice(noteElem->GetText());
										}
										if (noteElemName == "type")	{
											tempNote.type.setType(noteElem->GetText());
										}
										if (noteElemName == "stem")	{
											tempNote.stem.setStem(noteElem->GetText());
										}
										if (noteElemName == "pitch")	{
											for (XMLElement* pitchElem = noteElem->FirstChildElement(); pitchElem != nullptr; pitchElem = pitchElem->NextSiblingElement())	{
												checkElement(pitchElem);

												string pitchElemName = pitchElem->Value();

												if (pitchElemName == "step")	{
													tempNote.pitch.step.setStep(pitchElem->GetText());
												}
												if (pitchElemName == "octave")	{
													tempNote.pitch.octave.setOctave(pitchElem->GetText());
												}
											}
										}
									}

									if (!tempNote.isRest())	{
										const char* noteDefaultX = measureElem->Attribute("default-x");
										tempNote.setDefaultX(noteDefaultX);
										const char* noteDefaultY = measureElem->Attribute("default-y");
										tempNote.setDefaultY(noteDefaultY);
									}

									tempMeasure.notes.push_back(tempNote);
								}
								if (measureElemName == "barline")	{
									const char* location = measureElem->Attribute("location");
									tempMeasure.barLine.setLocation(location);

									for (XMLElement* barLineElem = measureElem->FirstChildElement(); barLineElem != nullptr; barLineElem = barLineElem->NextSiblingElement())	{
										checkElement(barLineElem);

										string barLineElemName = barLineElem->Value();

										if (barLineElemName == "bar-style")	{
											tempMeasure.barLine.barStyle.setBarStyle(barLineElem->GetText());
										}
									}
								}
							}
							part.measures.push_back(tempMeasure);
						}
					}
				}
			}
		}
	}
	catch (exception& e)	{
		cout << e.what() << endl;
		return FAILURE;
	}
	return SUCCESS;
}

void MusicXMLParser::print() {
	partList.print();
	part.print();
}

SuccessEnum MusicXMLParser::checkElement(XMLElement* element) {
	if (element == NULL) 	{
		throw runtime_error("Parser could not find a necessary XML element, check you files for errors.");
	}
	return SUCCESS;
}

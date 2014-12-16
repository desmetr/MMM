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

SuccessEnum MusicXMLParser::parse(string fileName) {
	XMLDocument doc;
	XMLElement* root;

	try	{
		doc.LoadFile(fileName.c_str());
		if (doc.ErrorID() != 0)		{
			cout << "The specified file could not be found, aborting..." << endl;
			return FAILURE;
		}

		root = doc.FirstChildElement();
		if (root == NULL)	{
			cerr << "Failed to load file: No root element." << endl;
			doc.Clear();
			return FAILURE;
		}
	}
	catch (exception& e)	{
		cout << e.what() << endl;
		return FAILURE;
	}

	try	{
		string rootValue = root->Value();
		if (rootValue == "score-partwise")	{
			for (XMLElement* elem = root->FirstChildElement(); elem != nullptr; elem = elem->NextSiblingElement())	{
				string elemName = elem->Value();

				// Parse the first block, parent = part-list.
				if (elemName == "part-list")	{
					for (XMLElement* partListElem = elem->FirstChildElement(); partListElem != nullptr; partListElem = partListElem->NextSiblingElement())	{
						string partListElemName = partListElem->Value();

						if (partListElemName == "part-group")	{
							const char* partGroupType = partListElem->Attribute("type");
							const char* partGroupNumber = partListElem->Attribute("number");
							partList.setPartGroupNumber(partGroupNumber);
							partList.setPartGroupType(partGroupType);
						}
						if (partListElemName == "score-part")	{
							const char* id = partListElem->Attribute("id");
							partList.scorePart.setId(id);

							for (XMLElement* scorePartElem = partListElem->FirstChildElement(); scorePartElem != nullptr; scorePartElem = scorePartElem->NextSiblingElement())	{
								string scorePartElemName = scorePartElem->Value();

								if (scorePartElemName == "part-name")	{
									partList.scorePart.setPartName(scorePartElem->GetText());
								}
								if (scorePartElemName == "score-instrument")	{
									const char* id = scorePartElem->Attribute("id");
									partList.scorePart.scoreInstrument.setId(id);

									for (XMLElement* instrumentNameElem = scorePartElem->FirstChildElement(); instrumentNameElem != nullptr; instrumentNameElem = instrumentNameElem->NextSiblingElement())	{
										string instrumentNameElemName = instrumentNameElem->Value();

										if (instrumentNameElemName == "instrument-name")	{
											partList.scorePart.scoreInstrument.setInstrumentName(instrumentNameElem->GetText());
										}
									}
								}
								if (scorePartElemName == "midi-instrument")		{
									const char* id = scorePartElem->Attribute("id");
									partList.scorePart.midiInstrument.setId(id);

									for (XMLElement* midiInstrumentElem = scorePartElem->FirstChildElement(); midiInstrumentElem != nullptr; midiInstrumentElem = midiInstrumentElem->NextSiblingElement())		{
										string midiInstrumentElemName = midiInstrumentElem->Value();

										if (midiInstrumentElemName == "midi-channel")	{
											partList.scorePart.midiInstrument.setMidiChannel(midiInstrumentElem->GetText());
										}
										if (midiInstrumentElemName == "midi-program")	{
											partList.scorePart.midiInstrument.setMidiProgram(midiInstrumentElem->GetText());
										}
										if (midiInstrumentElemName == "volume")	{
											partList.scorePart.midiInstrument.setVolume(midiInstrumentElem->GetText());
										}
										if (midiInstrumentElemName == "pan")	{
											partList.scorePart.midiInstrument.setPan(midiInstrumentElem->GetText());
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
						string partElemName = partElem->Value();

						Measure tempMeasure;
						if (partElemName == "measure")	{
							const char* measureNumber = partElem->Attribute("number");
							tempMeasure.setNumber(measureNumber);

							for (XMLElement* measureElem = partElem->FirstChildElement(); measureElem != nullptr; measureElem = measureElem->NextSiblingElement())	{
								string measureElemName = measureElem->Value();

								if (measureElemName == "attributes")	{
									for (XMLElement* attributeElem = measureElem->FirstChildElement(); attributeElem != nullptr; attributeElem = attributeElem->NextSiblingElement())	{
										string attributeElemName = attributeElem->Value();
										if (attributeElemName == "divisions")	{
											tempMeasure.attribute.setDivisions(attributeElem->GetText());
										}
										if (attributeElemName == "key")	{
											for (XMLElement* keyElem = attributeElem->FirstChildElement(); keyElem != nullptr; keyElem = keyElem->NextSiblingElement())	{
												string keyElemName = keyElem->Value();
												if (keyElemName == "fifths")	{
													tempMeasure.attribute.key.setFifths(keyElem->GetText());
												}
												if (keyElemName == "mode")	{
													tempMeasure.attribute.key.setMode(keyElem->GetText());
												}
											}
										}
										if (attributeElemName == "time")	{
											for (XMLElement* timeElem = attributeElem->FirstChildElement(); timeElem != nullptr; timeElem = timeElem->NextSiblingElement())	{
												string timeElemName = timeElem->Value();
												if (timeElemName == "beats")	{
													tempMeasure.attribute.time.setBeats(timeElem->GetText());
												}
												if (timeElemName == "beat-type")	{
													tempMeasure.attribute.time.setBeatType(timeElem->GetText());
												}
											}
										}
										if (attributeElemName == "clef")	{
											for (XMLElement* clefElem = attributeElem->FirstChildElement(); clefElem != nullptr; clefElem = clefElem->NextSiblingElement())	{
												string clefElemName = clefElem->Value();
												if (clefElemName == "sign")	{
													tempMeasure.attribute.clef.setSign(clefElem->GetText());
												}
												if (clefElemName == "line")	{
													tempMeasure.attribute.clef.setLine(clefElem->GetText());
												}
											}
										}
									}
								}
								if (measureElemName == "note")	{
									Note tempNote;

									const char* noteDefaultX = measureElem->Attribute("default-x");
									tempNote.setDefaultX(noteDefaultX);
									const char* noteDefaultY = measureElem->Attribute("default-y");
									tempNote.setDefaultY(noteDefaultY);

									for (XMLElement* noteElem = measureElem->FirstChildElement(); noteElem != nullptr; noteElem = noteElem->NextSiblingElement())	{
										string noteElemName = noteElem->Value();
										if (noteElemName == "duration")	{
											tempNote.setDuration(noteElem->GetText());
										}
										if (noteElemName == "voice")	{
											tempNote.setVoice(noteElem->GetText());
										}
										if (noteElemName == "type")	{
											tempNote.setType(noteElem->GetText());
										}
										if (noteElemName == "stem")	{
											tempNote.setStem(noteElem->GetText());
										}
										if (noteElemName == "pitch")	{
											for (XMLElement* pitchElem = noteElem->FirstChildElement(); pitchElem != nullptr; pitchElem = pitchElem->NextSiblingElement())	{
												string pitchElemName = pitchElem->Value();
												if (pitchElemName == "step")	{
													tempNote.pitch.setStep(pitchElem->GetText());
												}
												if (pitchElemName == "octave")	{
													tempNote.pitch.setOctave(pitchElem->GetText());
												}
											}
										}
										if (noteElemName == "rest")	{
											tempNote.setRest(true);
										}
									}

									tempMeasure.notes.push_back(tempNote);
								}
								if (measureElemName == "barline")	{
									const char* location = measureElem->Attribute("location");
									tempMeasure.barLine.setLocation(location);

									for (XMLElement* barLineElem = measureElem->FirstChildElement(); barLineElem != nullptr; barLineElem = barLineElem->NextSiblingElement())	{
										string barLineElemName = barLineElem->Value();
										if (barLineElemName == "bar-style")	{
											tempMeasure.barLine.setBarStyle(barLineElem->GetText());
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
	cout << "Printing partList" << endl;
	cout << "-----------------" << endl;
	partList.print();
	cout << endl << "Printing part" << endl;
	cout << "-------------" << endl;
	part.print();
}

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

				if (elemName == "part-list")	{
					for (XMLElement* partListElem = elem->FirstChildElement(); partListElem != nullptr; partListElem = partListElem->NextSiblingElement())	{
						string partListElemName = partListElem->Value();

						if (partListElemName == "part-group")	{
							const char* partGroupType = partListElem->Attribute("type");
							const char* number = partListElem->Attribute("number");
							partList.setNumber(number);
							partList.setPartGroupType(partGroupType);
						}
						if (partListElemName == "score-part")	{
							const char* id = partListElem->Attribute("id");
							scorePart.setId(id);

							for (XMLElement* scorePartElem = partListElem->FirstChildElement(); scorePartElem != nullptr; scorePartElem = scorePartElem->NextSiblingElement())	{
								string scorePartElemName = scorePartElem->Value();

								if (scorePartElemName == "part-name")	{
									scorePart.setPartName(scorePartElem->GetText());
								}
								if (scorePartElemName == "score-instrument")	{
									const char* id = scorePartElem->Attribute("id");
									scoreInstrument.setId(id);

									for (XMLElement* instrumentNameElem = scorePartElem->FirstChildElement(); instrumentNameElem != nullptr; instrumentNameElem = instrumentNameElem->NextSiblingElement())	{
										string instrumentNameElemName = instrumentNameElem->Value();

										if (instrumentNameElemName == "instrument-name")	{
											scoreInstrument.setInstrumentName(instrumentNameElem->GetText());
										}
									}
								}
								if (scorePartElemName == "midi-instrument")		{
									const char* id = scorePartElem->Attribute("id");
									midiInstrument.setId(id);

									for (XMLElement* midiChannelElem = scorePartElem->FirstChildElement(); midiChannelElem != nullptr; midiChannelElem = midiChannelElem->NextSiblingElement())	{
										string midiChannelElemName = midiChannelElem->Value();
										if (midiChannelElemName == "midi-channel")	{
											midiInstrument.setMidiChannel(midiChannelElem->GetText());
										}
									}
									for (XMLElement* midiProgramElem = scorePartElem->FirstChildElement(); midiProgramElem != nullptr; midiProgramElem = midiProgramElem->NextSiblingElement())	{
										string midiProgramElemName = midiProgramElem->Value();
										if (midiProgramElemName == "midi-program")	{
											midiInstrument.setMidiProgram(midiProgramElem->GetText());
										}
									}
									for (XMLElement* volumeElem = scorePartElem->FirstChildElement(); volumeElem != nullptr; volumeElem = volumeElem->NextSiblingElement())	{
										string volumeElemName = volumeElem->Value();
										if (volumeElemName == "volume")	{
											midiInstrument.setVolume(volumeElem->GetText());
										}
									}
									for (XMLElement* panElem = scorePartElem->FirstChildElement(); panElem != nullptr; panElem = panElem->NextSiblingElement())	{
										string panElemName = panElem->Value();
										if (panElemName == "pan")	{
											midiInstrument.setPan(panElem->GetText());
										}
									}
								}
							}
						}
					}
				}
			}
		}
		midiInstrument.print();
		partList.print();
		scoreInstrument.print();
		scorePart.print();
	}
	catch (exception& e)	{
		cout << e.what() << endl;
		return FAILURE;
	}
	return SUCCESS;
}

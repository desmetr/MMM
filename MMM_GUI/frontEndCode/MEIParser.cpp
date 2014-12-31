#include "MEIParser.h"

MEIParser::MEIParser(){
	noteMap['c'] = -50.0;
	noteMap['d'] = -45.0;
	noteMap['e'] = -40.0;
	noteMap['f'] = -35.0;
	noteMap['g'] = -30.0;
	noteMap['a'] = -25.0;
	noteMap['b'] = -20.0;

	noteNameMap['c'] = "C";
	noteNameMap['d'] = "D";
	noteNameMap['e'] = "E";
	noteNameMap['f'] = "F";
	noteNameMap['g'] = "G";
	noteNameMap['a'] = "A";
	noteNameMap['b'] = "B";

	typeMap[2] = "half";
	typeMap[4] = "quarter";
	typeMap[8] = "eight";
	typeMap[16] = "sixteenth";
};
MEIParser::~MEIParser(){};

void MEIParser::checkElement(tinyxml2::XMLElement* el){
	if(el == NULL) throw std::runtime_error("Parser could not find a necessary XML element, check you files for errors.");
}

void MEIParser::parse(string fileName){
	tinyxml2::XMLDocument meiFile;

	//load the MEI xml file.
	meiFile.LoadFile(fileName.c_str());
	//check if file opened correctly.
	if(meiFile.ErrorID() != 0){
		throw std::runtime_error("File could not be opened.");
	}

	//No prob -> continue -> get root
	tinyxml2::XMLElement* meiRoot = meiFile.FirstChildElement();
	//check if root correct
	checkElement(meiRoot);

	//check MEI contents of root
	string diepeZucht = "mei";
	if(meiRoot->Value() != diepeZucht) throw std::runtime_error("Root tag is not mei - wrong file?");

	//next up is the meiHead tag (normally) which we don't save anywhere, ignoring! -> immediately request music data.
	tinyxml2::XMLElement* dataWalker = meiRoot->FirstChildElement("music")->FirstChildElement("body")->FirstChildElement("mdiv")->FirstChildElement("score");
	//check whether this element is ok
	checkElement(dataWalker);

	//get the data from the scoreDef element.
	tinyxml2::XMLElement* scoreDef = dataWalker->FirstChildElement("scoreDef");
	if(scoreDef != nullptr){
		parseScoreDef(scoreDef);
	}
	else throw std::runtime_error("No scoredef element in xml, aborting.");

	//get the data from the <section> element.
	tinyxml2::XMLElement* section = dataWalker->FirstChildElement("section");
	//hand over to control to the parse section function.
	if(section != nullptr){
		parseSection(section);
	}
	else throw std::runtime_error("No section element in xml, aborting.");



}

void MEIParser::parseScoreDef(tinyxml2::XMLElement* elpointer){
	//check whether the element is ok
	checkElement(elpointer);

	//now actually get the data
	string dataHolder; //this variable temporarily holds parsed data. Useful for checks.

	//meter.count
	dataHolder = elpointer->Attribute("meter.count");
	if(dataHolder == "") throw std::runtime_error("No meter.count attribute in elpointer tag, aborting.");
	scoreDefContainer.MAAT_BOVEN_VAR = stoi(dataHolder); //IGNORE THE STOI WARNINGS, IT'S PART OF THE C++11 STANDARD BUT ECLIPSE IS SLOW ON LEARNING NEW STUFF.

	//meter.unit
	dataHolder = elpointer->Attribute("meter.unit");
	if(dataHolder == "") throw std::runtime_error("no meter.unit in elpointer tag, aborting.");
	scoreDefContainer.MAAT_ONDER_VAR = stoi(dataHolder);

	//key.mode
	dataHolder = elpointer->Attribute("key.mode");
	if(dataHolder == "") throw std::runtime_error("no key.mode in elpointer tag, aborting.");
	scoreDefContainer.SCHAAL_VAR = dataHolder;

	//get the staffDef
	tinyxml2::XMLElement* stafDef = elpointer->FirstChildElement("staffGrp")->FirstChildElement("staffDef");
	checkElement(stafDef); // check if it is not null

	//par number
	dataHolder = stafDef->Attribute("n");
	if(dataHolder =="") throw std::runtime_error("no 'n' attribute in staffDef tag, aborting");
	scoreDefContainer.STAFF_NUMBER_VAR = stoi(dataHolder);

	//part id
	dataHolder = stafDef->Attribute("xml:id");
	if(dataHolder =="") throw std::runtime_error("no 'xml:id' attribute in staffDef tag, aborting");
	scoreDefContainer.PART_ID_VAR = dataHolder;

	//part name
	dataHolder = stafDef->Attribute("label");
	if(dataHolder =="") throw std::runtime_error("no 'label' attribute in staffDef tag, aborting");
	scoreDefContainer.PART_NAME_VAR = dataHolder;

	//get the line on which the key sits.
	dataHolder = stafDef->Attribute("clef.line");
	if(dataHolder =="") throw std::runtime_error("no 'clef.line' attribute in staffDef tag, aborting");
	scoreDefContainer.CLEF_LINE_VAR = stoi(dataHolder);

	//get the type of key sign
	dataHolder = stafDef->Attribute("clef.shape");
	if(dataHolder =="") throw std::runtime_error("no 'clef.type' attribute in staffDef tag, aborting");
	scoreDefContainer.CLEF_TYPE_VAR = dataHolder;
}

void MEIParser::parseSection(tinyxml2::XMLElement* section){
//	//temporary data holder
	string dataHolder;

	//iterate over all measures, extracting the data
	for(tinyxml2::XMLElement* maat = section->FirstChildElement("measure"); maat != nullptr; maat = maat->NextSiblingElement()){

		measureData mc;

		dataHolder = maat->Attribute("n");
		if(dataHolder == "") throw std::runtime_error("no 'n' attribute in measure tag, aborting");
		mc.MEASURE_NUMBER_VAR = stoi(dataHolder);


		if(maat->Attribute("right") == NULL) mc.GENERATE_MEASURE_END = false;
		else mc.GENERATE_MEASURE_END = true;

		for(tinyxml2::XMLElement* noot = maat->FirstChildElement("staff")->FirstChildElement("layer")->FirstChildElement("note"); noot != nullptr; noot = noot->NextSiblingElement()){
			//TODO: STAFF NUMBER WAS SKIPPED HERE (!)
			noteData n;

			//Check whether it is a rest or a note.
			string restName = "rest";
			string elType = noot->Name();
			bool isRest = (elType == restName);
			if( !isRest ){
				dataHolder = noot->Attribute("pname");
				if(dataHolder == "") throw std::runtime_error("No 'pname' attribute in note tag, aborting");
				n.NOTE_NAME_VAR = dataHolder;

				dataHolder = noot->Attribute("oct");
				if(dataHolder == "") throw std::runtime_error("No 'oct' attribute in note tag, aborting");
				n.NOTE_OCTAVE_VAR = stoi(dataHolder);

				dataHolder = noot->Attribute("dur");
				if(dataHolder == "") throw std::runtime_error("No 'dur' attribute in note tag, aborting");
				n.NOTE_DURATION_VAR = stoi(dataHolder);

				dataHolder = noot->Attribute("stem.dir");
				if(dataHolder == "") throw std::runtime_error("No 'stem.dir' attribute in note tag, aborting");
				n.STEM_DIR_VAR = dataHolder;

                n.IS_REST = false;

				mc.NOTES.push_back(n);
			}
			else{
				dataHolder = noot->Attribute("dur");
				if(dataHolder == "") throw std::runtime_error("No 'dur' attribute in note tag, aborting");
				n.NOTE_DURATION_VAR = stoi(dataHolder);
				n.IS_REST = true;
				n.NOTE_NAME_VAR = "";
				n.NOTE_OCTAVE_VAR = 0;
				n.STEM_DIR_VAR = "und";
				mc.NOTES.push_back(n);
			}
		}
		measures.push_back(mc);
	}
}

void MEIParser::mapData(){
	/* This function maps the parsed MEI data from the
	 * intermediary MEI dataContainers to MusicXML objects.
	 * From thereon, MusicXML, CSV and MIDI can be generated.
	 */
	bool firstMeasureSet = false;

	partList.scorePart.setId(scoreDefContainer.PART_ID_VAR);
	partList.scorePart.partName.setName(scoreDefContainer.PART_NAME_VAR);
	partList.scorePart.scoreInstrument.setId("P1-13");
	partList.scorePart.scoreInstrument.instrumentName.setInstrumentName(scoreDefContainer.PART_NAME_VAR);

	partList.scorePart.midiInstrument.setId("P1-13");
	partList.scorePart.midiInstrument.midiChannel.setMidiChannel("1"); //fixed value.
	partList.scorePart.midiInstrument.midiProgram.setMidiProgram("1"); //fixed value
	partList.scorePart.midiInstrument.volume.setVolume("78"); //fixed value.
	partList.scorePart.midiInstrument.pan.setPan("0"); //Who needs stereo pshhh

	part.setId(scoreDefContainer.PART_ID_VAR);
	for(measureData& m : measures){
		Measure maat;

		maat.setNumber( to_string(m.MEASURE_NUMBER_VAR) );
		if(!firstMeasureSet){
			maat.attribute.division.setDivisions("1");
			maat.attribute.clef.line.setLine(to_string(scoreDefContainer.CLEF_LINE_VAR));
			maat.attribute.clef.sign.setSign(scoreDefContainer.CLEF_TYPE_VAR );
			maat.attribute.key.fifths.setFifths("0"); //constant
			maat.attribute.key.mode.setMode(scoreDefContainer.SCHAAL_VAR);
			maat.attribute.time.beatType.setBeatType( to_string(scoreDefContainer.MAAT_ONDER_VAR) );
			maat.attribute.time.beats.setBeats( to_string(scoreDefContainer.MAAT_BOVEN_VAR) );
			firstMeasureSet = true;
		}

		if(m.GENERATE_MEASURE_END){
			maat.barLine.setLocation("right"); //const
			maat.barLine.barStyle.setBarStyle("light-heavy");
		}

		for(noteData& n : m.NOTES ){
			Note noot;
			if(!n.IS_REST){
				noot.setDefaultX(to_string(generateNoteX()));
				noot.setDefaultY( to_string(generateNoteY(n.NOTE_NAME_VAR[0],n.NOTE_OCTAVE_VAR)));
				noot.setRest(false);
				noot.duration.setDuration("1");
				noot.type.setType(generateNoteType(n.NOTE_DURATION_VAR));
				noot.stem.setStem(n.STEM_DIR_VAR);
				noot.pitch.step.setStep(noteNameMap.find(n.NOTE_NAME_VAR[0])->second);
				noot.pitch.octave.setOctave(to_string(n.NOTE_OCTAVE_VAR));
				noot.voice.setVoice("1"); //CONST
				maat.notes.push_back(noot);
			}
			else{
				noot.setRest(true);
				noot.duration.setDuration("1"); //const
				noot.voice.setVoice("1"); //const
				noot.type.setType(generateNoteType(n.NOTE_DURATION_VAR));
				maat.notes.push_back(noot);
			}
		}
		part.measures.push_back(maat);
		x = 12.0;
	}

}

int MEIParser::generateNoteY(char name, int octave){
	double offset = -140 + (octave * 35);
	return offset + noteMap.find(name)->second;
}

double MEIParser::generateNoteX(){
	if(firstMeasure){
		x = 79.15;
		firstMeasure = false;
		return x;
	}
	else{
		x += 113.19;
		return x;
	}
}

string MEIParser::generateNoteType(int number){
	return typeMap.find(number)->second;
}

void MEIParser::debugOut(){
	cout << "<[GENERAL INFO]>" << endl << endl;
	cout << "[MAATSOORT]: " << scoreDefContainer.MAAT_BOVEN_VAR << "/" << scoreDefContainer.MAAT_ONDER_VAR << endl;
	cout << "[SCHAAL]: " << scoreDefContainer.SCHAAL_VAR << endl;
	cout << "[PART]: " << scoreDefContainer.STAFF_NUMBER_VAR << endl;
	cout << "\t [ID]: " << scoreDefContainer.PART_ID_VAR << endl;
	cout << "\t [LABEL]: " << scoreDefContainer.PART_NAME_VAR << endl;
	cout << "\t [SLEUTEL-LIJN]: " << scoreDefContainer.CLEF_LINE_VAR<< endl;
	cout << "\t [SLEUTEL-TYPE]: " << scoreDefContainer.CLEF_TYPE_VAR << endl << endl;
	cout << "<[MUSIC DATA]>" << endl << endl;
	for(measureData& m : measures){
		cout << "[MAAT]: nummer: " << m.MEASURE_NUMBER_VAR << " [END?] " << m.GENERATE_MEASURE_END << endl;
		for(noteData& n : m.NOTES){
			cout << "\t";
			if(!n.IS_REST){
				cout << "[NAAM] " << n.NOTE_NAME_VAR << " [OCTAAF] " << n.NOTE_OCTAVE_VAR << " [DUUR] 1/" << n.NOTE_DURATION_VAR << " maat [STEEL RICHTING] " << n.STEM_DIR_VAR << endl;
			}else{
				cout << "[RUST] " << " [DUUR] 1/" << n.NOTE_DURATION_VAR << endl;
			}
		}
	}
//
//	cout << "================MUSICXML========================" << endl;
//	partList.print();
//	part.print();
}

PartList MEIParser::getPartList() const{
	return this->partList;
}

Part MEIParser::getPart() const{
	return this->part;
}

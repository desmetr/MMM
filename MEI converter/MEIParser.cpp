#include "MEIParser.h"

MEIParser::MEIParser(){
	noteMap['C'] = -50.0;
	noteMap['D'] = -45.0;
	noteMap['E'] = -40.0;
	noteMap['F'] = -35.0;
	noteMap['G'] = -30.0;
	noteMap['A'] = -25.0;
	noteMap['B'] = -20.0;
};
MEIParser::~MEIParser(){};

void MEIParser::checkElement(tinyxml2::XMLElement* el){
	if(el == NULL) throw std::runtime_error("Parser could not find a necessary XML element, check you files for errors.");
}

succesEnum MEIParser::parse(string fileName){
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

	//we're done!
	return SUCCES;


}

void MEIParser::parseScoreDef(tinyxml2::XMLElement* elpointer){
	//IGNORE ALL STOI ERRORS- ECLIPSE , NOT CODE ERROR!!!

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

	//"WE HAVE TO GO DEEPER!" -> parse the staffDef (aka a part 'definition' in music xml);
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
	//temporary data holder
	string dataHolder;

	//iterate over all measures, extracting the data
	for(tinyxml2::XMLElement* maat = section->FirstChildElement("measure"); maat != nullptr; maat = maat->NextSiblingElement()){
		//Create new measure
		measureData mc;

		//get the measure number.
		dataHolder = maat->Attribute("n");
		if(dataHolder == "") throw std::runtime_error("no 'n' attribute in measure tag, aborting");
		mc.MEASURE_NUMBER_VAR = stoi(dataHolder);



		//check if the measure generates a measure end
		//this does not produce an error because it is optional.
		if(maat->Attribute("right") != NULL) mc.GENERATE_MEASURE_END = true;
		else mc.GENERATE_MEASURE_END = false;

		//parse all notes.
		for(tinyxml2::XMLElement* noot = maat->FirstChildElement("staff")->FirstChildElement("layer")->FirstChildElement("note"); noot != nullptr; noot = noot->NextSiblingElement()){
			//TODO: STAFF NUMBER WAS SKIPPED HERE (!)

			//create new note
			noteData n;

			//get the name of the note
			dataHolder = noot->Attribute("pname");
			if(dataHolder == "") throw std::runtime_error("No 'pname' attribute in note tag, aborting");
			n.NOTE_NAME_VAR = dataHolder;

			//get the octave of the note
			dataHolder = noot->Attribute("oct");
			if(dataHolder == "") throw std::runtime_error("No 'oct' attribute in note tag, aborting");
			n.NOTE_OCTAVE_VAR = stoi(dataHolder);

			//get the duration of the note
			dataHolder = noot->Attribute("dur");
			if(dataHolder == "") throw std::runtime_error("No 'dur' attribute in note tag, aborting");
			n.NOTE_DURATION_VAR = stoi(dataHolder);



			//get the stem direction of the note (d or q)
			dataHolder = noot->Attribute("stem.dir");
			if(dataHolder == "") throw std::runtime_error("No 'stem.dir' attribute in note tag, aborting");
			n.STEM_DIR_VAR = dataHolder;

			//add the note to the measure -> DONE:
			mc.NOTES.push_back(n);
		}

		//finally , add the measure to the parsed measures.
		measures.push_back(mc);
	}

	//Yay , done!

}

succesEnum MEIParser::mapData(){
	//IGNORE ALL to_string ERRORS IN ECLIPSE.

	//map all data onto the musicXML objects.
	partList.setPartGroupType("start");
	partList.setPartGroupNumber("1"); //WARNING THIS IS STATIC RIGHT NOW. MORE PARTS = AUTO RISE PART NUMBER
	//set all scorePart data.
	partList.scorePart.setId(scoreDefContainer.PART_ID_VAR);
	partList.scorePart.setPartName(scoreDefContainer.PART_NAME_VAR);
	partList.scorePart.scoreInstrument.setId("P1-13");
	partList.scorePart.scoreInstrument.setInstrumentName(scoreDefContainer.PART_NAME_VAR);
	//midi data
	partList.scorePart.midiInstrument.setMidiChannel("1"); //currently fixed.
	partList.scorePart.midiInstrument.setMidiProgram("1"); //currently fixed.
	partList.scorePart.midiInstrument.setVolume("78"); //currently fixed.
	partList.scorePart.midiInstrument.setPan("0");//WHO NEEDS STEREO ANYWAY
	//part data
	part.setId(scoreDefContainer.PART_ID_VAR);
	for(measureData& m : measures){
		//create musicXML measure
		Measure maat;

		//fill it up with parsed data from MEI
		maat.setNumber( to_string(m.MEASURE_NUMBER_VAR) );

		maat.attribute.setDivisions("1"); //const;

		maat.attribute.clef.setLine( to_string(scoreDefContainer.CLEF_LINE_VAR));
		maat.attribute.clef.setSign( scoreDefContainer.CLEF_TYPE_VAR);

		maat.attribute.key.setFifths("0"); //const;
		maat.attribute.key.setMode( scoreDefContainer.SCHAAL_VAR);

		maat.attribute.time.setBeatType( to_string(scoreDefContainer.MAAT_ONDER_VAR));
		maat.attribute.time.setBeats( to_string(scoreDefContainer.MAAT_BOVEN_VAR));

		maat.barLine.setLocation("right"); //const
		maat.barLine.setBarStyle("light-heavy");

		for(noteData& n : m.NOTES ){
			//create musicXML note.
			Note noot;

			//CONTINUE HERE

		}



		//reset start note position
		x = 12.0;
	}


	return SUCCES;
}

int MEIParser::generateNoteY(char name, int octave){
	double offset = -140 + octave * 35;
	return offset + noteMap.find(name);
}

double MEIParser::generateNoteX(){
	if(firstMeasure){
		x = 79.15;
	}
	else{
		return x + 113.19;
	}
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
			cout << "[NAAM] " << n.NOTE_NAME_VAR << " [OCTAAF] " << n.NOTE_OCTAVE_VAR << " [DUUR] 1/" << n.NOTE_DURATION_VAR << " maat [STEEL RICHTING] " << n.STEM_DIR_VAR << endl;
		}
	}


}

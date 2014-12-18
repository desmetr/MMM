/*
 * MEIGenerator.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: jago
 */

#include "MEIGenerator.h"

MEIGenerator::MEIGenerator(const PartList& partList,const Part& part){
	//initialize the string to int beat type map.
	setMaps();

	//Generate MEI data structures.
	scoreDef.PART_ID_VAR = partList.scorePart.getId();
	scoreDef.PART_NAME_VAR = partList.scorePart.partName.getName();
	scoreDef.PART_NAME_VAR = partList.scorePart.scoreInstrument.instrumentName.getInstrumentName();
	//MIDI is not supported (yet)

	for(const Measure& m : part.measures){

		measureData maat;
		maat.MEASURE_NUMBER_VAR = stoi(m.getNumber());
		//This data is only in the first measure in MusicXML, but for uniformity's sake,
		//We put it in the measure's for loop.
		//We make sure data doesn't get overwritten with nonsense by checking if this is the data-containing measure.
		if(m.attribute.clef.getLine().size() != 0){
			scoreDef.CLEF_TYPE_VAR = m.attribute.clef.getSign();
			scoreDef.CLEF_LINE_VAR = stoi( m.attribute.clef.getLine() );
			scoreDef.MAAT_ONDER_VAR = stoi( m.attribute.time.getBeatType() );
			scoreDef.MAAT_BOVEN_VAR = stoi( m.attribute.time.getBeats() );
			scoreDef.SCHAAL_VAR = m.attribute.key.getMode();
			scoreDef.STAFF_NUMBER_VAR = 1; //static right now;
		}

		if(m.barLine.getLocation() == "right"){
			maat.GENERATE_MEASURE_END = true;
		}
		else{
			maat.GENERATE_MEASURE_END = false;
		}

		//convert notes.
		for(const Note& n : m.notes){
			noteData noot;
			noot.NOTE_DURATION_VAR = typeMap.find(n.type.getType())->second;
			noot.STEM_DIR_VAR = n.stem.getStem();
			noot.NOTE_NAME_VAR = n.pitch.step.getStep();
			noot.NOTE_OCTAVE_VAR = stoi(n.pitch.octave.getOctave());
			maat.NOTES.push_back(noot);
		}
		measures.push_back(maat);
	}
}

MEIGenerator::MEIGenerator(){};

void MEIGenerator::setMaps(){
	//convert text beat type to int beat type.
	typeMap["half"] = 2;
	typeMap["quarter"] = 4;
	typeMap["eight"] = 8;
	typeMap["sixteenth"] = 16;
}

void MEIGenerator::generateXML(string fileName){
	//generate the document.
	tinyxml2::XMLDocument doc;
	//generate the xml type declaration
//	tinyxml2::XMLDeclaration* declaration = doc.NewDeclaration( "1.0");
//	doc.LinkEndChild( declaration );

	//generate the music, mdiv, score base elements//////////////////////////
	tinyxml2::XMLElement* musicElement = doc.NewElement("music");
	doc.LinkEndChild( musicElement );

	tinyxml2::XMLElement* mdivElement = doc.NewElement( "mdiv" );
	musicElement->LinkEndChild( mdivElement );

	tinyxml2::XMLElement* scoreElement = doc.NewElement( "score" );
	mdivElement->LinkEndChild( scoreElement );
	/////////////////////////////////////////////////////////////////////////

	//start the score definition/////////////////////////////////////////////
	tinyxml2::XMLElement* scoreDefElement = doc.NewElement( "scoreDef" );
	scoreElement->LinkEndChild( scoreDefElement );
	//set the data for the scoreDef element.
	scoreDefElement->SetAttribute("meter.count",scoreDef.MAAT_BOVEN_VAR);
	scoreDefElement->SetAttribute("meter.unit",scoreDef.MAAT_ONDER_VAR);
	scoreDefElement->SetAttribute("key.sig", 0);
	scoreDefElement->SetAttribute("key.mode", scoreDef.SCHAAL_VAR.c_str());

	//set stafGrp tag
	tinyxml2::XMLElement* staffGroup = doc.NewElement( "staffGrp" );
	scoreDefElement->LinkEndChild(staffGroup);

	//set the staffDeff tag
	tinyxml2::XMLElement* staffDef = doc.NewElement( "staffDef" );
	staffGroup->LinkEndChild(staffDef);
	//set the data for the staff def tag.
	staffDef->SetAttribute("n",scoreDef.STAFF_NUMBER_VAR);
	staffDef->SetAttribute("xml:id",scoreDef.PART_ID_VAR.c_str());
	staffDef->SetAttribute("label",scoreDef.PART_NAME_VAR.c_str());
	staffDef->SetAttribute("lines",5);
	staffDef->SetAttribute("clef.line",scoreDef.CLEF_LINE_VAR);
	staffDef->SetAttribute("clef.shape",scoreDef.CLEF_TYPE_VAR.c_str());

	//section tag:
	tinyxml2::XMLElement* sectionElement = doc.NewElement("section");
	scoreElement->LinkEndChild(sectionElement);

	//start linking measure tags.
	unsigned int measureNumber = 0;
	unsigned int id = 0;
	for(measureData& m : measures){
		//create new measure
		tinyxml2::XMLElement* newMeasure = doc.NewElement("measure");
		sectionElement->LinkEndChild(newMeasure);
		//auto generate the measure number. (timewise vs partwise incompatible.)
		newMeasure->SetAttribute("n", measureNumber);
		measureNumber++; //increase measure number
		//auto generate id, idk if this is useful or not.
		newMeasure->SetAttribute("xml:id",id);
		id++; //increment id.

		if(m.GENERATE_MEASURE_END){
			newMeasure->SetAttribute("right","end");
		}

		//set up staff tag
		tinyxml2::XMLElement* staff = doc.NewElement("staff");
		newMeasure->LinkEndChild(staff);
		staff->SetAttribute("n", 1);//Currently static, could use a lookup mechanism too i guess.

		//set up layer tag
		tinyxml2::XMLElement* layer = doc.NewElement("layer");
		staff->LinkEndChild(layer);

		layer->SetAttribute("n", 1);//Currently static, I think it's always 1

		for(noteData& n : m.NOTES){
			tinyxml2::XMLElement* newNote = doc.NewElement("note");
			layer->LinkEndChild(newNote);

			//setup the note Data!
			newNote->SetAttribute("xml:id",id);
			id++;

			newNote->SetAttribute("pname",n.NOTE_NAME_VAR.c_str());
			newNote->SetAttribute("oct", n.NOTE_OCTAVE_VAR);
			newNote->SetAttribute("dur", n.NOTE_DURATION_VAR);
			newNote->SetAttribute("stem.dir", n.STEM_DIR_VAR.c_str());
		}
	}

	//done generating->save
	doc.SaveFile(fileName.c_str());
}

void MEIGenerator::debugOut(){
	//Print out the info of our MEI.
	cout << "<[GENERAL INFO]>" << endl << endl;
	cout << "[MAATSOORT]: " << scoreDef.MAAT_BOVEN_VAR << "/" << scoreDef.MAAT_ONDER_VAR << endl;
	cout << "[SCHAAL]: " << scoreDef.SCHAAL_VAR << endl;
	cout << "\t [ID]: " << scoreDef.PART_ID_VAR << endl;
	cout << "\t [LABEL]: " << scoreDef.PART_NAME_VAR << endl;
	cout << "\t [SLEUTEL-LIJN]: " << scoreDef.CLEF_LINE_VAR<< endl;
	cout << "\t [SLEUTEL-TYPE]: " << scoreDef.CLEF_TYPE_VAR << endl << endl;
	cout << "<[MUSIC DATA]>" << endl << endl;
	for(measureData& m : measures){
		cout << "[MAAT]: nummer: " << m.MEASURE_NUMBER_VAR << " [END?] " << m.GENERATE_MEASURE_END << endl;
		for(noteData& n : m.NOTES){
			cout << "\t";
			cout << "[NAAM] " << n.NOTE_NAME_VAR << " [OCTAAF] " << n.NOTE_OCTAVE_VAR << " [DUUR] 1/" << n.NOTE_DURATION_VAR << " maat [STEEL RICHTING] " << n.STEM_DIR_VAR << endl;
		}
	}
}

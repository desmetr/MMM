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

		if(m.attribute.clef.line.getLine().size() != 0){
			scoreDef.CLEF_TYPE_VAR = m.attribute.clef.sign.getSign();
			scoreDef.CLEF_LINE_VAR = stoi( m.attribute.clef.line.getLine() );
			scoreDef.MAAT_ONDER_VAR = stoi( m.attribute.time.beatType.getBeatType() );
			scoreDef.MAAT_BOVEN_VAR = stoi( m.attribute.time.beats.getBeats() );
			scoreDef.SCHAAL_VAR = m.attribute.key.mode.getMode();
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
			if(!n.isRest()){
				noot.NOTE_DURATION_VAR = typeMap.find(n.type.getType())->second;
				noot.STEM_DIR_VAR = n.stem.getStem();
				noot.NOTE_NAME_VAR = noteMap.find(n.pitch.step.getStep()[0])->second;
				noot.NOTE_OCTAVE_VAR = stoi(n.pitch.octave.getOctave());
                noot.IS_REST = false;
				maat.NOTES.push_back(noot);

			}
			else{
				noot.NOTE_DURATION_VAR = typeMap.find(n.type.getType())->second;
				noot.IS_REST = true;
				maat.NOTES.push_back(noot);
			}
		}
		measures.push_back(maat);
	}
}

MEIGenerator::MEIGenerator(){};

void MEIGenerator::setMaps(){
	typeMap["half"] = 2;
	typeMap["quarter"] = 4;
	typeMap["eight"] = 8;
	typeMap["sixteenth"] = 16;

	noteMap['C'] = 'c';
	noteMap['D'] = 'd';
	noteMap['E'] = 'e';
	noteMap['F'] = 'f';
	noteMap['G'] = 'g';
	noteMap['A'] = 'a';
	noteMap['B'] = 'b';
}

void MEIGenerator::generateXML(string fileName){
	/*generates an MEI object out of intermediary MEI objects*/
	tinyxml2::XMLDocument doc;

    tinyxml2::XMLDeclaration* declaration = doc.NewDeclaration( "xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"");
	doc.LinkEndChild( declaration );

	tinyxml2::XMLElement* meiElement =doc.NewElement("mei");
	doc.LinkEndChild(meiElement);
	meiElement->SetAttribute("xmlns","http://www.music-encoding.org/ns/mei");
    meiElement->SetAttribute("xmlns:xlink","http://www.w3.org/1999/xlink");
	meiElement->SetAttribute("meiversion","2013");


	generateHead(doc,meiElement); //generate al the header info here.

	//generate the music, mdiv, score base elements//////////////////////////
	tinyxml2::XMLElement* musicElement = doc.NewElement("music");
	meiElement->LinkEndChild( musicElement );

	tinyxml2::XMLElement* body = doc.NewElement("body");
	musicElement->LinkEndChild(body);

	tinyxml2::XMLElement* mdivElement = doc.NewElement( "mdiv" );
	body->LinkEndChild( mdivElement );

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
	unsigned int measureNumber = 1;
	unsigned int id = 0;
	for(measureData& m : measures){
		//create new measure
		tinyxml2::XMLElement* newMeasure = doc.NewElement("measure");
		sectionElement->LinkEndChild(newMeasure);
		//auto generate the measure number. (timewise vs partwise incompatible.)
		newMeasure->SetAttribute("n", measureNumber);
		measureNumber++; //increase measure number
		//auto generate id, idk if this is useful or not.
		string newId = "d" + to_string(id);
		newMeasure->SetAttribute("xml:id", newId.c_str());
		id++; //increment id.

		if(m.GENERATE_MEASURE_END){
			newMeasure->SetAttribute("right","end");
		}

		//set up staff tag
		tinyxml2::XMLElement* staff = doc.NewElement("staff");
		newMeasure->LinkEndChild(staff);
		staff->SetAttribute("n", 1); //constant

		//set up layer tag
		tinyxml2::XMLElement* layer = doc.NewElement("layer");
		staff->LinkEndChild(layer);

		layer->SetAttribute("n", 1); //constant

		for(noteData& n : m.NOTES){


			if(!n.IS_REST){
				tinyxml2::XMLElement* newNote = doc.NewElement("note");
				layer->LinkEndChild(newNote);

				string newId = "d" + to_string(id);
				newNote->SetAttribute("xml:id", newId.c_str() );
				id++;

				newNote->SetAttribute("pname",n.NOTE_NAME_VAR.c_str());
				newNote->SetAttribute("oct", n.NOTE_OCTAVE_VAR);
				newNote->SetAttribute("dur", n.NOTE_DURATION_VAR);
				newNote->SetAttribute("stem.dir", n.STEM_DIR_VAR.c_str());
			}
			else{
				tinyxml2::XMLElement* newRest = doc.NewElement("rest");
				layer->LinkEndChild(newRest);

				string newId = "d" + to_string(id);
				newRest->SetAttribute("xml:id", newId.c_str());
				id++;
				newRest->SetAttribute("dur",n.NOTE_DURATION_VAR);
			}
		}
	}

	//done generating->save
	doc.SaveFile(fileName.c_str());
}

void MEIGenerator::generateHead(tinyxml2::XMLDocument& doc,tinyxml2::XMLElement* meiRoot){

	tinyxml2::XMLElement* meiHeadElement = doc.NewElement("meiHead");
	meiRoot->LinkEndChild( meiHeadElement );

	tinyxml2::XMLElement* fileDescElement = doc.NewElement("fileDesc");
	meiHeadElement->LinkEndChild( fileDescElement );

	tinyxml2::XMLElement* titleStmtElement = doc.NewElement("titleStmt");
	fileDescElement->LinkEndChild( titleStmtElement );

	tinyxml2::XMLElement* titleElement = doc.NewElement("title");
	titleStmtElement->LinkEndChild( titleElement );

	tinyxml2::XMLElement* pubStmtElement = doc.NewElement("pubStmt");
	fileDescElement->LinkEndChild( pubStmtElement );

	tinyxml2::XMLElement* sourceDesc = doc.NewElement("sourceDesc");
	fileDescElement->LinkEndChild( sourceDesc );

	tinyxml2::XMLElement* source = doc.NewElement("source");
	sourceDesc->LinkEndChild( source );

	tinyxml2::XMLElement* titleStmt2 = doc.NewElement("titleStmt");
	source->LinkEndChild(titleStmt2);

	tinyxml2::XMLElement* titleElement2 = doc.NewElement("title");
	titleStmt2->LinkEndChild( titleElement2 );

	tinyxml2::XMLElement* pubStmt2 = doc.NewElement("pubStmt");
	source->LinkEndChild(pubStmt2);

	tinyxml2::XMLElement* encodingDesc = doc.NewElement("encodingDesc");
	meiHeadElement->LinkEndChild(encodingDesc);

	tinyxml2::XMLElement* editorialDecl = doc.NewElement("editorialDecl");
	encodingDesc->LinkEndChild(editorialDecl);

	tinyxml2::XMLElement* normalization = doc.NewElement("normalization");
	editorialDecl->LinkEndChild(normalization);

	tinyxml2::XMLElement* p = doc.NewElement("p");
	normalization->LinkEndChild(p);

	tinyxml2::XMLElement* revisionDesc = doc.NewElement("revisionDesc");
	meiHeadElement->LinkEndChild(revisionDesc);

	tinyxml2::XMLElement* change = doc.NewElement("change");
	revisionDesc->LinkEndChild(change);
	change->SetAttribute("n",1);

	tinyxml2::XMLElement* respStmt = doc.NewElement("respStmt");
	change->LinkEndChild(respStmt);

	tinyxml2::XMLElement* changeDesc = doc.NewElement("changeDesc");
	change->LinkEndChild(changeDesc);

	tinyxml2::XMLElement* p2 = doc.NewElement("p");
	changeDesc->LinkEndChild(p2);

	tinyxml2::XMLElement* date = doc.NewElement("date");
	change->LinkEndChild(date);
	date->SetText("1995-03-09"); // happy birthday to me!
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
			if(!n.IS_REST){
				cout << "[NAAM] " << n.NOTE_NAME_VAR << " [OCTAAF] " << n.NOTE_OCTAVE_VAR << " [DUUR] 1/" << n.NOTE_DURATION_VAR << " maat [STEEL RICHTING] " << n.STEM_DIR_VAR << endl;
			}else{
				cout << "[RUST] " << " [DUUR] 1/" << n.NOTE_DURATION_VAR << endl;
			}
		}
	}
}

/*
 * MEIGenerator.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: jago
 */

#include "MEIGenerator.h"

MEIGenerator::MEIGenerator(const PartList& partList,const Part& part){
	setMaps();
	//Generate intermediary data structures.
	//general info
	scoreDef.PART_ID_VAR = partList.scorePart.getId();
	scoreDef.PART_NAME_VAR = partList.scorePart.partName.getName();
	scoreDef.PART_NAME_VAR = partList.scorePart.scoreInstrument.instrumentName.getInstrumentName();
	//midi data is not ported (yet)
	for(const Measure& m : part.measures){
		measureData maat;
		maat.MEASURE_NUMBER_VAR = stoi(m.getNumber());

		if(m.attribute.clef.getLine().size() != 0){
			scoreDef.CLEF_TYPE_VAR = m.attribute.clef.getSign();
			scoreDef.CLEF_LINE_VAR = stoi( m.attribute.clef.getLine() );
			scoreDef.MAAT_ONDER_VAR = stoi( m.attribute.time.getBeatType() );
			scoreDef.MAAT_BOVEN_VAR = stoi( m.attribute.time.getBeats() );
			scoreDef.SCHAAL_VAR = m.attribute.key.getMode();
		}

		if(m.barLine.getLocation() == "right") maat.GENERATE_MEASURE_END = true;
		else maat.GENERATE_MEASURE_END = false;


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

	typeMap["half"] = 2;
	typeMap["quarter"] = 4;
	typeMap["eight"] = 8;
	typeMap["sixteenth"] = 16;
}

void MEIGenerator::debugOut(){
	cout << "<[GENERAL INFO]>" << endl << endl;
	cout << "[MAATSOORT]: " << scoreDef.MAAT_BOVEN_VAR << "/" << scoreDef.MAAT_ONDER_VAR << endl;
	cout << "[SCHAAL]: " << scoreDef.SCHAAL_VAR << endl;
	//cout << "[PART]: " << scoreDef.STAFF_NUMBER_VAR << endl; NOT PARSED ask rafael.
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

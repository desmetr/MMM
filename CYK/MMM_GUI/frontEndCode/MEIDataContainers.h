/*
 * MEIDataContainer.h
 *
 *  Created on: Dec 16, 2014
 *      Author: jago
 */

#ifndef MEIDATACONTAINERS_H_
#define MEIDATACONTAINERS_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

struct scoreDefData{
	int MAAT_BOVEN_VAR;
	int MAAT_ONDER_VAR;
	string SCHAAL_VAR;
	string PART_ID_VAR;
	string PART_NAME_VAR;
	int CLEF_LINE_VAR;
	string CLEF_TYPE_VAR;
	int STAFF_NUMBER_VAR;
};

struct noteData{
	string NOTE_NAME_VAR;
	int NOTE_OCTAVE_VAR;
	int NOTE_DURATION_VAR;
	string STEM_DIR_VAR;
	bool IS_REST; //if it is a rest, only duration is of importance.
};


struct measureData{
	int MEASURE_NUMBER_VAR;
	int STAFF_NUMBER_VAR; //NOTE: IDK if necessary, but it can be used to derive CLEF_TYPE and CLEF_LINE in music_xml;
	vector<noteData> NOTES; //these are in order of parsing(!!);
	bool GENERATE_MEASURE_END;
};





#endif /* MEIDATACONTAINERS_H_ */

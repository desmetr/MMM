/*
 * ScorePart.h
 *
 *  Created on: Dec 15, 2014
 *      Author: Rafael De Smet
 */

#ifndef SCOREPART_H_
#define SCOREPART_H_

#include <string>
#include <iostream>
#include "PartName.h"
#include "ScoreInstrument.h"
#include "MidiInstrument.h"

class ScorePart {
public:
	ScorePart();
	virtual ~ScorePart();

	PartName partName;
	ScoreInstrument scoreInstrument;
	MidiInstrument midiInstrument;

	const std::string& getId() const;
	const std::string& getTagName() const;

	void setId(const std::string& id);

	void print();

private:
	std::string id;

	std::string tagName = "score-part";
//	const std::string tagName = "score-part";
};

#endif /* SCOREPART_H_ */

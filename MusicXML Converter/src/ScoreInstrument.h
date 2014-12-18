/*
 * ScoreInstrument.h
 *
 *  Created on: Dec 15, 2014
 *      Author: Rafael De Smet
 */

#ifndef SCOREINSTRUMENT_H_
#define SCOREINSTRUMENT_H_

#include <string>
#include <iostream>
#include "InstrumentName.h"

class ScoreInstrument {
public:
	ScoreInstrument();
	virtual ~ScoreInstrument();

	InstrumentName instrumentName;

	const std::string& getId() const;
	const std::string& getTagName() const;

	void setId(const std::string& id);

	void print();

private:
	std::string id;

	const std::string tagName = "score-instrument";
};


#endif /* SCOREINSTRUMENT_H_ */

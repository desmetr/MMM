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

class ScoreInstrument {
public:
	ScoreInstrument();
	virtual ~ScoreInstrument();

	const std::string& getId() const;
	const std::string& getInstrumentName() const;
	const std::string& getTagName() const;

	void setId(const std::string& id);
	void setInstrumentName(const std::string& instrumentName);

	void print();

private:
	std::string id;
	std::string instrumentName;

	const std::string tagName;
};


#endif /* SCOREINSTRUMENT_H_ */

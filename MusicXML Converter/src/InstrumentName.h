/*
 * InstrumentName.h
 *
 *  Created on: Dec 18, 2014
 *      Author: Rafael De Smet
 */

#ifndef INSTRUMENTNAME_H_
#define INSTRUMENTNAME_H_

#include <string>
#include <iostream>

class InstrumentName {
public:
	InstrumentName();
	virtual ~InstrumentName();

	const std::string& getInstrumentName() const;
	const std::string& getTagName() const;

	void setInstrumentName(const std::string& instrumentName);

	void print();

private:
	std::string instrumentName;

	const std::string tagName = "instrument-name";
};

#endif /* INSTRUMENTNAME_H_ */

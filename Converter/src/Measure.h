/*
 * Measure.h
 *
 *  Created on: Dec 16, 2014
 *      Author: Rafael De Smet
 */

#ifndef MEASURE_H_
#define MEASURE_H_

#include <string>
#include <iostream>
#include <vector>
#include "Attribute.h"
#include "Note.h"
#include "BarLine.h"

class Measure {
public:
	Measure();
	virtual ~Measure();

	Attribute attribute;
	std::vector<Note> notes;
	BarLine barLine;

	const std::string& getNumber() const;
	const std::string& getTagName() const;

	void setNumber(const std::string& number);

	void print();

private:
	std::string number;
//	int number;

	const std::string tagName = "measure";
};

#endif /* MEASURE_H_ */

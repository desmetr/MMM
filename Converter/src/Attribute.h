/*
 * Attribute.h
 *
 *  Created on: Dec 16, 2014
 *      Author: Rafael De Smet
 */

#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

#include <string>
#include <iostream>
#include "Division.h"
#include "Key.h"
#include "Time.h"
#include "Clef.h"

class Attribute {
public:
	Attribute();
	virtual ~Attribute();

	Division division;
	Key key;
	Time time;
	Clef clef;

	const std::string& getDivisions() const;
	const std::string& getTagName() const;

	void setDivisions(const std::string& divisions);

	void print();

private:
	const std::string tagName = "attributes";
};

#endif /* ATTRIBUTE_H_ */

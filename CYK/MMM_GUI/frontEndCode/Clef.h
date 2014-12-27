/*
 * Clef.h
 *
 *  Created on: Dec 16, 2014
 *      Author: Rafael De Smet
 */

#ifndef CLEF_H_
#define CLEF_H_

#include <string>
#include <iostream>
#include "Sign.h"
#include "Line.h"

class Clef {
public:
	Clef();
	virtual ~Clef();

	Sign sign;
	Line line;

	const std::string& getTagName() const;

	void print();

private:
	std::string tagName = "clef";
};

#endif /* CLEF_H_ */

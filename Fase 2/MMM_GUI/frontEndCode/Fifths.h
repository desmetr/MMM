/*
 * Fifths.h
 *
 *  Created on: Dec 18, 2014
 *      Author: Rafael De Smet
 */

#ifndef FIFTHS_H_
#define FIFTHS_H_

#include <string>
#include <iostream>

class Fifths {
public:
	Fifths();
	virtual ~Fifths();

	const std::string& getFifths() const;
	const std::string& getTagName() const;

	void setFifths(const std::string& fifths);

	void print();

private:
	std::string fifths;

	std::string tagName = "fifths";
};

#endif /* FIFTHS_H_ */

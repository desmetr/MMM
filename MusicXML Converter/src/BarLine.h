/*
 * BarLine.h
 *
 *  Created on: Dec 16, 2014
 *      Author: Rafael De Smet
 */

#ifndef BARLINE_H_
#define BARLINE_H_

#include <string>
#include <iostream>
#include "BarStyle.h"

class BarLine {
public:
	BarLine();
	virtual ~BarLine();

	BarStyle barStyle;

	const std::string& getLocation() const;
	const std::string& getTagName() const;

	void setLocation(const std::string& location);

	void print();

private:
	std::string location;

	std::string tagName = "barline";
//	const std::string tagName = "barline";
};

#endif /* BARLINE_H_ */

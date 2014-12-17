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

class BarLine {
public:
	BarLine();
	virtual ~BarLine();

	const std::string& getBarStyle() const;
	const std::string& getLocation() const;
	const std::string& getTagName() const;

	void setBarStyle(const std::string& barStyle);
	void setLocation(const std::string& location);

	void print();

private:
	std::string location;
	std::string barStyle;

	const std::string tagName = "barline";
};

#endif /* BARLINE_H_ */

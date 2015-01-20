/*
 * Line.h
 *
 *  Created on: Dec 18, 2014
 *      Author: Rafael De Smet
 */

#ifndef LINE_H_
#define LINE_H_

#include <string>
#include <iostream>

class Line {
public:
	Line();
	virtual ~Line();

	const std::string& getLine() const;
	const std::string& getTagName() const;

	void setLine(const std::string& line);

	void print();

private:
	std::string line;

	std::string tagName = "line";
};

#endif /* LINE_H_ */

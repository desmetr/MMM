/*
 * Line.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: Rafael De Smet
 */

#include "Line.h"

using namespace std;

Line::Line() {
}

Line::~Line() {
}

const string& Line::getLine() const 	{	return line;	}
const string& Line::getTagName() const 	{	return tagName;	}

void Line::setLine(const string& line) 	{	this->line = line;	}

void Line::print() {
	cout << "\t\t\t\tLine:" << endl;
	cout << "\t\t\t\t\tline: " << line << endl;
}

/*
 * Clef.cpp
 *
 *  Created on: Dec 16, 2014
 *      Author: Rafael De Smet
 */

#include "Clef.h"

using namespace std;

Clef::Clef() {
}

Clef::~Clef() {
}

const string& Clef::getLine() const 	{	return line;	}
const string& Clef::getSign() const 	{	return sign;	}
const string& Clef::getTagName() const 	{	return tagName;	}

void Clef::setLine(const string& line) 	{	this->line = line;	}
void Clef::setSign(const string& sign) 	{	this->sign = sign;	}

void Clef::print() {
	cout << "\t\t\tClef:" << endl;
	cout << "\t\t\t\tsign: " << sign << endl;
	cout << "\t\t\t\tline: " << line << endl;
}

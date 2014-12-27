/*
 * Measure.cpp
 *
 *  Created on: Dec 16, 2014
 *      Author: Rafael De Smet
 */

#include "Measure.h"

using namespace std;

Measure::Measure() {
}

Measure::~Measure() {
}

const string& Measure::getNumber() const 	{	return number;	}
const string& Measure::getTagName() const 	{	return tagName;	}

void Measure::setNumber(const string& number) 			{	this->number = number;			}

void Measure::print() {
	cout << "\tMeasure:" << endl;
	cout << "\t\tnumber: " << number << endl;
	attribute.print();
	cout << endl;
	for (auto& note : notes)	{
		note.print();
		cout << endl;
	}
	barLine.print();
}

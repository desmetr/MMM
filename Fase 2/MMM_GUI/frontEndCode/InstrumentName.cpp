/*
 * InstrumentName.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: Rafael De Smet
 */

#include "InstrumentName.h"

using namespace std;

InstrumentName::InstrumentName() {
}

InstrumentName::~InstrumentName() {
}

const string& InstrumentName::getInstrumentName() const 	{	return instrumentName;	}
const string& InstrumentName::getTagName() const 			{	return tagName;			}

void InstrumentName::setInstrumentName(const string& instrumentName) 	{	this->instrumentName = instrumentName;	}

void InstrumentName::print() {
	cout << "\t\t\tInstrumentName:" << endl;
	cout << "\t\t\t\tinstrument name: " << instrumentName << endl;
}

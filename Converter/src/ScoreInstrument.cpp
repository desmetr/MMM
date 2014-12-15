/*
 * ScoreInstrument.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: Rafael De Smet
 */

#include "ScoreInstrument.h"

using namespace std;

ScoreInstrument::ScoreInstrument() {
}

ScoreInstrument::~ScoreInstrument() {
}

const string& ScoreInstrument::getId() const 				{	return id;				}
const string& ScoreInstrument::getTagName() const 			{	return tagName;			}
const string& ScoreInstrument::getInstrumentName() const 	{	return instrumentName;	}

void ScoreInstrument::setId(const string& id) 								{	this->id = id;							}
void ScoreInstrument::setInstrumentName(const string& instrumentName) 		{	this->instrumentName = instrumentName;	}

void ScoreInstrument::print() {
	cout << "Attributes of ScoreInstrument: " << endl;
	cout << "\tID: " << id << endl;
	cout << "\tinstrumentName: " << instrumentName << endl;
}

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

void ScoreInstrument::setId(const string& id) 				{	this->id = id;			}

void ScoreInstrument::print() {
	cout << "\t\tScoreInstrument: " << endl;
	cout << "\t\t\tID: " << id << endl;
	instrumentName.print();
}

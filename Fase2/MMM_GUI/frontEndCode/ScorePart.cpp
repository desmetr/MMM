/*
 * ScorePart.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: Rafael De Smet
 */

#include "ScorePart.h"

using namespace std;

ScorePart::ScorePart() {

}

ScorePart::~ScorePart() {
}

const string& ScorePart::getId() const 			{	return id;			}
const string& ScorePart::getTagName() const 	{	return tagName;		}

void ScorePart::setId(const string& id) 			{	this->id = id;				}

void ScorePart::print() {
	cout << "\tScorePart:" << endl;
	cout << "\t\tID: " << id << endl;
	partName.print();
	scoreInstrument.print();
	midiInstrument.print();
}

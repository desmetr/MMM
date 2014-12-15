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
const string& ScorePart::getPartName() const 	{	return partName;	}
const string& ScorePart::getTagName() const 	{	return tagName;		}

void ScorePart::setId(const string& id) 			{	this->id = id;				}
void ScorePart::setPartName(const string& partName) {	this->partName = partName;	}

void ScorePart::print() {
	cout << "Attributes of ScorePart:" << endl;
	cout << "\tID: " << id << endl;
	cout << "\tpartName: " << partName << endl;
}

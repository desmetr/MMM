/*
 * Part.cpp
 *
 *  Created on: Dec 16, 2014
 *      Author: Rafael De Smet
 */

#include "Part.h"

using namespace std;

Part::Part() {
}

Part::~Part() {
}

const string& Part::getId() const 		{	return id;		}
const string& Part::getTagName() const 	{	return tagName;	}

void Part::setId(const string& id) 		{	this->id = id;	}

void Part::print() {
	cout << "Part:" << endl;
	cout << "\tID: " << id << endl;
	for (auto& measure : measures)	{
		measure.print();
	}
}

/*
 * BeatType.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: Rafael De Smet
 */

#include "BeatType.h"

using namespace std;

BeatType::BeatType() {
}

BeatType::~BeatType() {
}

const string& BeatType::getBeatType() const 	{	return beatType;	}
const string& BeatType::getTagName() const 		{	return tagName;		}

void BeatType::setBeatType(const string& beatType) 	{	this->beatType = beatType;	}

void BeatType::print() {
	cout << "\t\t\t\tBeatType:" << endl;
	cout << "\t\t\t\t\tbeat-type: " << beatType << endl;
}

/*
 * Time.cpp
 *
 *  Created on: Dec 16, 2014
 *      Author: Rafael De Smet
 */

#include "Time.h"

using namespace std;

Time::Time() {
}

Time::~Time() {
}

const string& Time::getBeats() const 		{	return beats;		}
const string& Time::getBeatType() const 	{	return beatType;	}
const string& Time::getTagName() const 		{	return tagName;		}

void Time::setBeats(const string& beats) 		{	this->beats = beats;		}
void Time::setBeatType(const string& beatType) 	{	this->beatType = beatType;	}

void Time::print() {
	cout << "Time:" << endl;
	cout << "\tbeats: " << beats << endl;
	cout << "\tbeatType: " << beatType << endl;
}

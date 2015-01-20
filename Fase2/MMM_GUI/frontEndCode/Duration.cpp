/*
 * Duration.cpp
 *
 *  Created on: Dec 17, 2014
 *      Author: Rafael De Smet
 */

#include "Duration.h"

using namespace std;

Duration::Duration() {
}

Duration::~Duration() {
}

const string& Duration::getDuration() const 	{	return duration;	}
const string& Duration::getTagName() const 		{	return tagName;		}

void Duration::setDuration(const string& duration) 	{	this->duration = duration;	}

void Duration::print() {
	cout << "\t\t\tDuration:" << endl;
	cout << "\t\t\t\tduration: " << duration << endl;
}

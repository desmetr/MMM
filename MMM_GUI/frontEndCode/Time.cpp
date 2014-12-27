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

const string& Time::getTagName() const 		{	return tagName;		}

void Time::print() {
	cout << "\t\t\tTime:" << endl;
	beats.print();
	beatType.print();
}

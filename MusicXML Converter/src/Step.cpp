/*
 * Step.cpp
 *
 *  Created on: Dec 17, 2014
 *      Author: Rafael De Smet
 */

#include "Step.h"

using namespace std;

Step::Step() {
}

Step::~Step() {
}

const string& Step::getStep() const 		{	return step;		}
const string& Step::getTagName() const 		{	return tagName;		}

void Step::setStep(const string& step) 		{	this->step = step;	}

void Step::print() {
	cout << "\t\t\t\tStep:" << endl;
	cout << "\t\t\t\t\tstep: " << step << endl;
}

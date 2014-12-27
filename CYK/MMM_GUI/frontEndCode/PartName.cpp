/*
 * PartName.cpp
 *
 *  Created on: Dec 17, 2014
 *      Author: Rafael De Smet
 */

#include "PartName.h"

using namespace std;

PartName::PartName() {
}

PartName::~PartName() {
}

const string& PartName::getName() const 		{	return name;		}
const string& PartName::getTagName() const 		{	return tagName;		}

void PartName::setName(const string& name) 		{	this->name = name;	}

void PartName::print() {
	cout << "\t\tPartName:" << endl;
	cout << "\t\t\tname: " << name << endl;
}

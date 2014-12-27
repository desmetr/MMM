/*
 * Type.cpp
 *
 *  Created on: Dec 17, 2014
 *      Author: Rafael De Smet
 */

#include "Type.h"

using namespace std;

Type::Type() {
}

Type::~Type() {
}

const string& Type::getTagName() const 		{	return tagName;	}
const string& Type::getType() const 		{	return type;	}

void Type::setType(const string& type) 		{	this->type = type;	}

void Type::print() {
	cout << "\t\t\tType:" << endl;
	cout << "\t\t\t\ttype: " << type << endl;
}

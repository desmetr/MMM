/*
 * Sign.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: Rafael De Smet
 */

#include "Sign.h"

using namespace std;

Sign::Sign() {
}

Sign::~Sign() {
}

const string& Sign::getSign() const 		{	return sign;	}
const string& Sign::getTagName() const		{	return tagName;	}

void Sign::setSign(const string& sign) 		{	this->sign = sign;	}

void Sign::print() {
	cout << "\t\t\t\tSign:" << endl;
	cout << "\t\t\t\t\tsign: " << sign << endl;
}

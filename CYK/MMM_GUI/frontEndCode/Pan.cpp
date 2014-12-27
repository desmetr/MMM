/*
 * Pan.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: Rafael De Smet
 */

#include "Pan.h"

using namespace std;

Pan::Pan() {
}

Pan::~Pan() {
}

const string& Pan::getPan() const 		{	return pan;		}
const string& Pan::getTagName() const 	{	return tagName;	}

void Pan::setPan(const string& pan) 	{	this->pan = pan;	}

void Pan::print() {
	cout << "\t\t\tPan: " << endl;
	cout << "\t\t\t\tpan: " << pan << endl;
}

/*
 * PartList.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: Rafael De Smet
 */

#include "PartList.h"

using namespace std;

PartList::PartList() {

}

PartList::~PartList() {
}

const string& PartList::getTagName() const 				{	return tagName;				}

void PartList::print() {
	cout << "PartList:" << endl;
	scorePart.print();
}

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

const string& PartList::getNumber() const 				{	return number;			}
const string& PartList::getPartGroupType() const 		{	return partGroupType;	}
const string& PartList::getTagName() const 				{	return tagName;			}

void PartList::setNumber(const string& number) 					{	this->number = number;					}
void PartList::setPartGroupType(const string& partGroupType) 	{	this->partGroupType = partGroupType;	}

void PartList::print() {
	cout << "Attributes of PartList:" << endl;
	cout << "\tnumber: " << number << endl;
	cout << "\tpartGroupType: " << partGroupType << endl;
}

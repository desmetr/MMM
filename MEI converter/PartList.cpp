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

const string& PartList::getPartGroupNumber() const 		{	return partGroupNumber;		}
const string& PartList::getPartGroupType() const 		{	return partGroupType;		}
const string& PartList::getTagName() const 				{	return tagName;				}

void PartList::setPartGroupNumber(const string& number) 		{	this->partGroupNumber = number;			}
void PartList::setPartGroupType(const string& partGroupType) 	{	this->partGroupType = partGroupType;	}

void PartList::print() {
	cout << "PartList:" << endl;
	cout << "\tpartGroupNumber: " << partGroupNumber << endl;
	cout << "\tpartGroupType: " << partGroupType << endl;
	scorePart.print();
}

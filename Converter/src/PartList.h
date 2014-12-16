/*
 * PartList.h
 *
 *  Created on: Dec 15, 2014
 *      Author: Rafael De Smet
 */

#ifndef PARTLIST_H_
#define PARTLIST_H_

#include <string>
#include <iostream>
#include "ScorePart.h"

class PartList {
public:
	PartList();
	virtual ~PartList();

	ScorePart scorePart;

	const std::string& getPartGroupNumber() const;
	const std::string& getPartGroupType() const;
	const std::string& getTagName() const;

	void setPartGroupNumber(const std::string& partGroupNumber);
	void setPartGroupType(const std::string& partGroupType);

	void print();

private:
	std::string partGroupType;
	std::string partGroupNumber;
//	int number;

	const std::string tagName = "part-list";
};

#endif /* PARTLIST_H_ */

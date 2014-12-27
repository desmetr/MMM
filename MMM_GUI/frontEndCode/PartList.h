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

	const std::string& getTagName() const;

	void print();

private:
	std::string tagName = "part-list";
//	const std::string tagName = "part-list";
};

#endif /* PARTLIST_H_ */

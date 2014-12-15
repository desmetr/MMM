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

class PartList {
public:
	PartList();
	virtual ~PartList();

	const std::string& getNumber() const;
	const std::string& getPartGroupType() const;
	const std::string& getTagName() const;

	void setNumber(const std::string& number);
	void setPartGroupType(const std::string& partGroupType);

	void print();

private:
	std::string partGroupType;
	std::string number;
//	int number;

	const std::string tagName = "part-list";
};

#endif /* PARTLIST_H_ */

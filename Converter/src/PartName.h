/*
 * PartName.h
 *
 *  Created on: Dec 17, 2014
 *      Author: Rafael De Smet
 */

#ifndef PARTNAME_H_
#define PARTNAME_H_

#include <string>
#include <iostream>

class PartName {
public:
	PartName();
	virtual ~PartName();

	const std::string& getName() const;
	const std::string& getTagName() const;

	void setName(const std::string& name);

	void print();

private:
	std::string name;

	const std::string tagName = "part-name";
};

#endif /* PARTNAME_H_ */

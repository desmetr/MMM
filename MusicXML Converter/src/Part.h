/*
 * Part.h
 *
 *  Created on: Dec 16, 2014
 *      Author: Rafael De Smet
 */

#ifndef PART_H_
#define PART_H_

#include <string>
#include <iostream>
#include <vector>
#include "Measure.h"

class Part {
public:
	Part();
	virtual ~Part();

	std::vector<Measure> measures;

	const std::string& getId() const;
	const std::string& getTagName() const;

	void setId(const std::string& id);

	void print();

private:
	std::string id;

	const std::string tagName = "part";
};

#endif /* PART_H_ */

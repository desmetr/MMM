/*
 * Division.h
 *
 *  Created on: Dec 17, 2014
 *      Author: Rafael De Smet
 */

#ifndef DIVISION_H_
#define DIVISION_H_

#include <string>
#include <iostream>

class Division {
public:
	Division();
	virtual ~Division();
	const std::string& getDivisions() const;
	void setDivisions(const std::string& divisions);
	const std::string& getTagName() const;

	void print();

private:
	std::string divisions;
//	int divisions;

	const std::string tagName = "divisions";
};

#endif /* DIVISION_H_ */

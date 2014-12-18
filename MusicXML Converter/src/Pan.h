/*
 * Pan.h
 *
 *  Created on: Dec 18, 2014
 *      Author: Rafael De Smet
 */

#ifndef PAN_H_
#define PAN_H_

#include <string>
#include <iostream>

class Pan {
public:
	Pan();
	virtual ~Pan();
	const std::string& getPan() const;
	const std::string& getTagName() const;

	void setPan(const std::string& pan);

	void print();

private:
	std::string pan;

	std::string tagName = "pan";
//	const std::string tagName = "pan";
};

#endif /* PAN_H_ */

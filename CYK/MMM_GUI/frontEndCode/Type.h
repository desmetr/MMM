/*
 * Type.h
 *
 *  Created on: Dec 17, 2014
 *      Author: Rafael De Smet
 */

#ifndef TYPE_H_
#define TYPE_H_

#include <string>
#include <iostream>

class Type {
public:
	Type();
	virtual ~Type();

	const std::string& getTagName() const;
	const std::string& getType() const;

	void setType(const std::string& type);

	void print();

private:
	std::string type;

	std::string tagName = "type";
//	const std::string tagName = "type";
};

#endif /* TYPE_H_ */

/*
 * Key.h
 *
 *  Created on: Dec 16, 2014
 *      Author: Rafael De Smet
 */

#ifndef KEY_H_
#define KEY_H_

#include <string>
#include <iostream>
#include "Fifths.h"
#include "Mode.h"

class Key {
public:
	Key();
	virtual ~Key();

	Fifths fifths;
	Mode mode;

	const std::string& getTagName() const;

	void print();

private:
	std::string tagName = "key";
//	const std::string tagName = "key";
};

#endif /* KEY_H_ */

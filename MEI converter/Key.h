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

class Key {
public:
	Key();
	virtual ~Key();
	const std::string& getFifths() const;
	const std::string& getMode() const;
	const std::string& getTagName() const;

	void setFifths(const std::string& fifths);
	void setMode(const std::string& mode);

	void print();

private:
	std::string fifths;
//	int fifths;
	std::string mode;
//	int mode;

	std::string tagName = "key";
//	const std::string tagName = "key";
};

#endif /* KEY_H_ */

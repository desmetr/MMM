/*
 * Stem.h
 *
 *  Created on: Dec 17, 2014
 *      Author: Rafael De Smet
 */

#ifndef STEM_H_
#define STEM_H_

#include <string>
#include <iostream>

class Stem {
public:
	Stem();
	virtual ~Stem();

	const std::string& getStem() const;
	const std::string& getTagName() const;

	void setStem(const std::string& stem);

	void print();

private:
	std::string stem;

	std::string tagName = "stem";
//	const std::string tagName = "stem";
};

#endif /* STEM_H_ */

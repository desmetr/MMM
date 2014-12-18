/*
 * Clef.h
 *
 *  Created on: Dec 16, 2014
 *      Author: Rafael De Smet
 */

#ifndef CLEF_H_
#define CLEF_H_

#include <string>
#include <iostream>

class Clef {
public:
	Clef();
	virtual ~Clef();

	const std::string& getLine() const;
	const std::string& getSign() const;
	const std::string& getTagName() const;

	void setLine(const std::string& line);
	void setSign(const std::string& sign);

	void print();

private:
	std::string sign;
	std::string line;
//	int line;

	std::string tagName = "clef";
//	const std::string tagName = "clef";
};

#endif /* CLEF_H_ */

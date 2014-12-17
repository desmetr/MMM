/*
 * BarStyle.h
 *
 *  Created on: Dec 17, 2014
 *      Author: Rafael De Smet
 */

#ifndef BARSTYLE_H_
#define BARSTYLE_H_

#include <string>
#include <iostream>

class BarStyle {
public:
	BarStyle();
	virtual ~BarStyle();

	const std::string& getBarStyle() const;
	const std::string& getTagName() const;

	void setBarStyle(const std::string& barStyle);

	void print();

private:
	std::string barStyle;

	const std::string tagName = "bar-style";
};

#endif /* BARSTYLE_H_ */

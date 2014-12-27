/*
 * Time.h
 *
 *  Created on: Dec 16, 2014
 *      Author: Rafael De Smet
 */

#ifndef TIME_H_
#define TIME_H_

#include <string>
#include <iostream>
#include "Beats.h"
#include "BeatType.h"

class Time {
public:
	Time();
	virtual ~Time();

	Beats beats;
	BeatType beatType;

	const std::string& getTagName() const;

	void print();

private:
	std::string tagName = "time";
};

#endif /* TIME_H_ */

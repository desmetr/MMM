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

class Time {
public:
	Time();
	virtual ~Time();

	const std::string& getBeats() const;
	const std::string& getBeatType() const;
	const std::string& getTagName() const;

	void setBeats(const std::string& beats);
	void setBeatType(const std::string& beatType);

	void print();

private:
	std::string beats;
//	int beats;
	std::string beatType;
//	int betaType;

	std::string tagName = "time";
//	const std::string tagName = "time";
};

#endif /* TIME_H_ */

/*
 * Duration.h
 *
 *  Created on: Dec 17, 2014
 *      Author: Rafael De Smet
 */

#ifndef DURATION_H_
#define DURATION_H_

#include <string>
#include <iostream>

class Duration {
public:
	Duration();
	virtual ~Duration();

	const std::string& getDuration() const;
	const std::string& getTagName() const;

	void setDuration(const std::string& duration);

	void print();

private:
	std::string duration;

	const std::string tagName = "duration";
};

#endif /* DURATION_H_ */

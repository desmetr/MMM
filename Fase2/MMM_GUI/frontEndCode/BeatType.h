/*
 * BeatType.h
 *
 *  Created on: Dec 18, 2014
 *      Author: Rafael De Smet
 */

#ifndef BEATTYPE_H_
#define BEATTYPE_H_

#include <string>
#include <iostream>

class BeatType {
public:
	BeatType();
	virtual ~BeatType();

	const std::string& getBeatType() const;
	const std::string& getTagName() const;

	void setBeatType(const std::string& beatType);

	void print();

private:
	std::string beatType;

	std::string tagName = "beat-type";
};

#endif /* BEATTYPE_H_ */

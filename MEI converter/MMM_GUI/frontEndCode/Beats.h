/*
 * Beats.h
 *
 *  Created on: Dec 18, 2014
 *      Author: Rafael De Smet
 */

#ifndef BEATS_H_
#define BEATS_H_

#include <string>
#include <iostream>

class Beats {
public:
	Beats();
	virtual ~Beats();

	const std::string& getBeats() const;
	const std::string& getTagName() const;

	void setBeats(const std::string& beats);

	void print();

private:
	std::string beats;

	std::string tagName = "beats";
};

#endif /* BEATS_H_ */

/*
 * Pitch.h
 *
 *  Created on: Dec 16, 2014
 *      Author: Rafael De Smet
 */

#ifndef PITCH_H_
#define PITCH_H_

#include <string>
#include <iostream>
#include "Step.h"
#include "Octave.h"

class Pitch {
public:
	Pitch();
	virtual ~Pitch();

	Step step;
	Octave octave;

	const std::string& getTagName() const;

	void print();

private:
	std::string tagName = "pitch";
//	const std::string tagName = "pitch";
};

#endif /* PITCH_H_ */

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

class Pitch {
public:
	Pitch();
	virtual ~Pitch();

	const std::string& getOctave() const;
	const std::string& getStep() const;
	const std::string& getTagName() const;

	void setOctave(const std::string& octave);
	void setStep(const std::string& step);

	void print();

private:
	std::string step;
	std::string octave;

	const std::string tagName = "pitch";
};

#endif /* PITCH_H_ */

/*
 * Octave.h
 *
 *  Created on: Dec 17, 2014
 *      Author: Rafael De Smet
 */

#ifndef OCTAVE_H_
#define OCTAVE_H_

#include <string>
#include <iostream>

class Octave {
public:
	Octave();
	virtual ~Octave();

	const std::string& getOctave() const;
	const std::string& getTagName() const;

	void setOctave(const std::string& octave);

	void print();

private:
	std::string octave;

	std::string tagName = "octave";
//	const std::string tagName = "octave";
};

#endif /* OCTAVE_H_ */

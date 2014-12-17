/*
 * Note.h
 *
 *  Created on: Dec 16, 2014
 *      Author: Rafael De Smet
 */

#ifndef NOTE_H_
#define NOTE_H_

#include <string>
#include <iostream>
#include "Pitch.h"
#include "Duration.h"
#include "Voice.h"
#include "Type.h"
#include "Stem.h"

class Note {
public:
	Note();
	virtual ~Note();

	Pitch pitch;
	Duration duration;
	Voice voice;
	Type type;
	Stem stem;

	const std::string& getDefaultX() const;
	const std::string& getDefaultY() const;
	const std::string& getTagName() const;
	bool isRest() const;

	void setDefaultX(const std::string& defaultX);
	void setDefaultY(const std::string& defaultY);
	void setRest(bool rest);

	void print();

private:
	std::string defaultX;
	std::string defaultY;
	bool rest;

//	float defaultX;
//	float defaultY;

	const std::string tagName = "note";
};

#endif /* NOTE_H_ */

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

class Note {
public:
	Note();
	virtual ~Note();

	Pitch pitch;

	const std::string& getDefaultX() const;
	const std::string& getDefaultY() const;
	const std::string& getDuration() const;
	const std::string& getStem() const;
	const std::string& getTagName() const;
	const std::string& getType() const;
	const std::string& getVoice() const;
	bool isRest() const;

	void setDefaultX(const std::string& defaultX);
	void setDefaultY(const std::string& defaultY);
	void setDuration(const std::string& duration);
	void setStem(const std::string& stem);
	void setType(const std::string& type);
	void setVoice(const std::string& voice);
	void setRest(bool rest);

	void print();

private:
	std::string defaultX;
	std::string defaultY;
	std::string duration;
	std::string voice;
	std::string type;		// Type of note, e.g. quarter, whole, half, eight
	std::string stem;
	bool rest;

//	float defaultX;
//	float defaultY;
//	int duration;
//	int type;

	const std::string tagName = "note";
};

#endif /* NOTE_H_ */

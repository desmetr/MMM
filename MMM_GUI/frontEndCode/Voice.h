/*
 * Voice.h
 *
 *  Created on: Dec 17, 2014
 *      Author: Rafael De Smet
 */

#ifndef VOICE_H_
#define VOICE_H_

#include <string>
#include <iostream>

class Voice {
public:
	Voice();
	virtual ~Voice();

	const std::string& getTagName() const;
	const std::string& getVoice() const;

	void setVoice(const std::string& voice);

	void print();

private:
	std::string voice;

	std::string tagName = "voice";
//	const std::string tagName = "voice";
};

#endif /* VOICE_H_ */

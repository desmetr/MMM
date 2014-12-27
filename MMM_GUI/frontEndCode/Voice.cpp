/*
 * Voice.cpp
 *
 *  Created on: Dec 17, 2014
 *      Author: Rafael De Smet
 */

#include "Voice.h"

using namespace std;

Voice::Voice() {
}

Voice::~Voice() {
}

const string& Voice::getTagName() const 	{	return tagName;	}
const string& Voice::getVoice() const 		{	return voice;	}

void Voice::setVoice(const string& voice) 	{	this->voice = voice;	}

void Voice::print() {
	cout << "\t\t\tVoice:" << endl;
	cout << "\t\t\t\tvoice: " << voice << endl;
}

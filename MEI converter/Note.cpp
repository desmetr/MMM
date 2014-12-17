/*
 * Note.cpp
 *
 *  Created on: Dec 16, 2014
 *      Author: Rafael De Smet
 */

#include "Note.h"

using namespace std;

Note::Note()
: rest(false)
{
}

Note::~Note() {
}

const string& Note::getDefaultX() const 	{	return defaultX;	}
const string& Note::getDefaultY() const 	{	return defaultY;	}
const string& Note::getDuration() const 	{	return duration;	}
const string& Note::getStem() const 		{	return stem;		}
const string& Note::getTagName() const 		{	return tagName;		}
const string& Note::getType() const 		{	return type;		}
const string& Note::getVoice() const 		{	return voice;		}
bool Note::isRest() const 					{	return rest;		}

void Note::setDefaultX(const string& defaultX)	{	this->defaultX = defaultX;	}
void Note::setDefaultY(const string& defaultY)	{	this->defaultY = defaultY;	}
void Note::setDuration(const string& duration)	{	this->duration = duration;	}
void Note::setStem(const string& stem)			{	this->stem = stem;			}
void Note::setType(const string& type)			{	this->type = type;			}
void Note::setVoice(const string& voice)		{	this->voice = voice;		}
void Note::setRest(bool rest) 					{	this->rest = rest;			}

void Note::print() {
	cout << "Note:" << endl;
	if (!rest)	{
		cout << "\tdefaultX: " << defaultX << endl;
		cout << "\tdefaultY: " << defaultY << endl;
		pitch.print();
	}
	if (rest)	{
		cout << "This is a rest." << endl;
	}
	cout << "\tduration: " << duration << endl;
	cout << "\tvoice: " << voice << endl;
	cout << "\ttype: " << type << endl;
	if (!rest)	{
		cout << "\tstem: " << stem << endl;
	}
}

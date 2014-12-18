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
const string& Note::getTagName() const 		{	return tagName;		}
bool Note::isRest() const 					{	return rest;		}

void Note::setDefaultX(const string& defaultX)	{	this->defaultX = defaultX;	}
void Note::setDefaultY(const string& defaultY)	{	this->defaultY = defaultY;	}
void Note::setRest(bool rest) 					{	this->rest = rest;			}

void Note::print() {
	cout << "\t\tNote:" << endl;
	if (rest)	{
		cout << "\t\t\tThis is a rest." << endl;
	}
	else	{
		cout << "\t\t\tdefaultX: " << defaultX << endl;
		cout << "\t\t\tdefaultY: " << defaultY << endl;
		pitch.print();
	}
	duration.print();
	voice.print();
	type.print();
	if (!rest)	{
		stem.print();
	}
}

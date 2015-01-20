/*
 * Beats.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: Rafael De Smet
 */

#include "Beats.h"

using namespace std;

Beats::Beats() {
}

Beats::~Beats() {
}

const string& Beats::getBeats() const 		{	return beats;	}
const string& Beats::getTagName() const 	{	return tagName;	}

void Beats::setBeats(const string& beats) 	{	this->beats = beats;	}

void Beats::print() {
	cout << "\t\t\t\tBeats:" << endl;
	cout << "\t\t\t\t\tbeats: " << beats << endl;
}

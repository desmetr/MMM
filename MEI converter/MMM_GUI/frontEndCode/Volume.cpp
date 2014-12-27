/*
 * Volume.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: Rafael De Smet
 */

#include "Volume.h"

using namespace std;

Volume::Volume() {
}

Volume::~Volume() {
}

const string& Volume::getTagName() const 	{	return tagName;	}
const string& Volume::getVolume() const 	{	return volume;	}

void Volume::setVolume(const string& volume) {	this->volume = volume;	}

void Volume::print() {
	cout << "\t\t\tVolume: " << endl;
	cout << "\t\t\t\tvolume: " << volume << endl;
}

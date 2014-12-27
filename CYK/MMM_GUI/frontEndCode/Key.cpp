/*
 * Key.cpp
 *
 *  Created on: Dec 16, 2014
 *      Author: Rafael De Smet
 */

#include "Key.h"

using namespace std;

Key::Key() {
}

Key::~Key() {
}

const string& Key::getTagName() const 	{	return tagName;	}

void Key::print() {
	cout << "\t\t\tKey:" << endl;
	fifths.print();
	mode.print();
}

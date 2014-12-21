/*
 * Formatter.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: bp
 */

#include "Formatter.h"

Formatter::Formatter(const string& inputString)
: s1(inputString), s2(){
	// TODO Auto-generated constructor stub
	applyTransformation();
}

Formatter::~Formatter() {
	// TODO Auto-generated destructor stub
}

string Formatter::getFormatedVersion() const{
	return s2;
}

///////////
//private//
//////////

//the actual algorithm
void Formatter::applyTransformation(){
	//loop over all the chars of the input string s1
	//and create a string s2 that has ',' on the right places

	bool inString{false};//check if we had a '"'
	bool addKomma{false};//if we had '>'we have to add a ',' to s2
	int brackets{0};

	for (auto& ch : s1){
		switch (ch){
		case '<':
			brackets++;
			break;
		case '>':
			brackets--;
			addKomma = true;
			break;
		case '"':
			if (inString){
				s2 += ',';
				inString = false;
			}
			else inString = true;
			break;
		default:
			if ( inString ){
				s2 += ',';
			}
		}
		s2 += ch;
		if (addKomma){
			addKomma = false;
			s2 += ',';
		}
		else if ( brackets == 0){
			s2 += ',';
		}
	}

	s2.pop_back();//remove the last',' which we don't need

}

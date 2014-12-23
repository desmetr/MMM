/*
 * Formatter.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: bp
 */

#include "Formatter.h"

using std::endl;
using std::cout;

Formatter::Formatter(string fileName)
: s1(""), s2(){

	OpenFileAndremoveSpaces(fileName);//result in s1
	applyTransformation();//reads s1 and puts result in s2

	cout << s2 << endl;
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

void Formatter::OpenFileAndremoveSpaces(string fileName){
	std::ifstream file(fileName);
	string line;

	bool inBrackets{false};
	while ( std::getline(file, line)){
		for (auto& ch : line){
			switch (ch){
			case ' ':
				if (inBrackets) s1+=ch;
				break;
			case '\t':
				break;
			case '<':
				s1 += ch;
				inBrackets = true;
				break;
			case '>':
				s1 += ch;
				inBrackets = false;
				break;
			default:
				s1 += ch;
			}
		}
	}
}
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

}

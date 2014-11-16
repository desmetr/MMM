//============================================================================
// Name        : PDA.cpp
// Author      : Rafael De Smet
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <stdexcept>
#include "PDA.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc == 2)	{
		char* fileName = argv[1];
		cout << "Opening and parsing " << fileName << endl;
		PDA pda;
		pda.parseXML(fileName);
	}
	else	{
		cerr << "Error, no file specified." << endl;
	}

	return 0;
}

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
#include <typeinfo>
#include "PDA.h"
#include "Utilities.h"

using namespace std;

int main(int argc, char* argv[]) {
	PDA pda;
	if (argc == 2)	{
		char* fileName = argv[1];
		cout << "Opening and parsing " << fileName << endl;
		pda.parseXML(fileName);
	}
	else	{
		cerr << "Error, no file specified." << endl;
	}
	
	pda.print();

	return 0;
}

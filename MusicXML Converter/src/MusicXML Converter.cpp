//============================================================================
// Name        : Converter.cpp
// Author      : Rafael De Smet
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "MusicXMLParser.h"
//#include "MusicXMLMaps.h"

using namespace std;

int main(int argc, char* argv[]) {
	MusicXMLParser parser;
	if (argc == 2)	{
		cout << "Opening and parsing " << argv[1] << endl;
		parser.parse(argv[1]);
	}
	else	{
		cerr << "Error, no file specified." << endl;
	}

	parser.print();

	return 0;
}

//============================================================================
// Name        : MusicXMLConverter.cpp
// Author      : Rafael De Smet
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "MusicXMLParser.h"
#include "MusicXMLGenerator.h"
#include "CSVGenerator.h"
//#include "MusicXMLMaps.h"

using namespace std;

int main(int argc, char* argv[]) {
	MusicXMLParser musicXMLParser;

	if (argc == 2)	{
		cout << "Opening and parsing " << argv[1] << endl;
		musicXMLParser.parse(argv[1]);
	}
	else	{
		cerr << "Error, no file specified." << endl;
	}

//	musicXMLParser.print();

//	cout << "Generating a MusicXML file..." << endl;
//	MusicXMLGenerator musicXMLGenerator(musicXMLParser.getPartList(), musicXMLParser.getPart());
//	musicXMLGenerator.generateMusicXML(argv[1]);

	cout << "Generating a CSV file..." << endl;
	CSVGenerator CSVGenerator_(musicXMLParser.getPartList(), musicXMLParser.getPart());
	CSVGenerator_.generateCSV(argv[1]);

	return 0;
}

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

	return 0;
}

//	MusicXMLMaps musicXML;
//	for (const auto& mapElem : musicXML.getAttributes())	{
//		cout << mapElem.first << "\t->\t" << mapElem.second << endl;
//		if (mapElem.first == "divisions")	{
//			cout << endl << mapElem.first << "\t->\t" << mapElem.second;
//		}
//		if (mapElem.first == "key")	{
//			cout << endl;
//			for (const auto& elem : musicXML.getKey())	{
//				cout << elem.first << "\t->\t" << elem.second << endl;
//			}
//		}
//		if (mapElem.first == "time")	{
//			cout << endl;
//			for (const auto& elem : musicXML.getTime())	{
//				cout << elem.first << "\t->\t" << elem.second << endl;
//			}
//		}
//		if (mapElem.first == "clef")	{
//			cout << endl;
//			for (const auto& elem : musicXML.getClef())	{
//				cout << elem.first << "\t->\t" << elem.second << endl;
//			}
//		}
//	}

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
#include "MEIParser.h"
#include "MEIGenerator.h"

using namespace std;

int main(int argc, char* argv[]) {
	MEIParser a;

	MusicXMLParser p;
	try{
		p.parse("testOctave.xml");
		MEIGenerator g(p.getPartList(), p.getPart());
		g.generateXML("MEITEST.xml");


	}
	catch(exception& e){
		cout << e.what() << endl;
	}

	return 0;
}

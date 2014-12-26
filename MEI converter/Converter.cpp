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
#include "MusicXMLGenerator.h"

using namespace std;

int main(int argc, char* argv[]) {

	MEIParser meip;
	MusicXMLParser mxlp;


	if(argc >= 2){
		try{
			meip.parse(argv[1]);
			meip.mapData();
			MusicXMLGenerator mxlg(meip.getPartList(),meip.getPart());
			mxlg.generateMusicXML();

		}
		catch(exception& e){
			cout << e.what() << endl;
		}
	}
	cout << "Exitted normally." << endl;
	return 0;
}

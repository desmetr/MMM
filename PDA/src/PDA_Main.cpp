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
#include <fstream> 
#include <stdlib.h>
#include "PDA.h"
#include "Utilities.h"

using namespace std;

void generateDotFile(PDA& pda, char* fileNameDot)	{
	ofstream stream;
	strcat(fileNameDot, ".dot");
	stream.open(fileNameDot);
	stream << pda;
	stream.close();
	
	string command = "chmod 777 ";
	command.append(fileNameDot);
	system(command.c_str());
	
	command = "dot -Tpng ";
	command.append(fileNameDot);
	command.append(" -O");
	system(command.c_str());
}

int main(int argc, char* argv[]) {
	PDA pda;
	string fileNameXML = Utilities::charPtrToString(argv[1]);
	fileNameXML += ".xml";
	if (argc == 2)	{
		cout << "Opening and parsing " << fileNameXML << endl;
		pda.parseXML(Utilities::stringToCharPtr(fileNameXML));
	}
	else	{
		cerr << "Error, no file specified." << endl;
	}
	
	pda.print();
	generateDotFile(pda, argv[1]);
	
	return 0;
}

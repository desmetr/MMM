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

int main(int argc, char* argv[]) {
	PDA pda;
	char* fileName = argv[1];
	strcat(fileName, ".xml");
	if (argc == 2)	{
//		char* fileName = argv[1];
//		fileName += ".xml";
		cout << "Opening and parsing " << fileName << endl;
		pda.parseXML(fileName);
	}
	else	{
		cerr << "Error, no file specified." << endl;
	}
	
	pda.print();
	
	ofstream stream;
	fileName = argv[1];
	strcat(fileName, ".dot");
	stream.open(fileName);
	stream << pda;
	stream.close();
	
	string command = "chmod 777 ";
	command.append(fileName);
	system(command.c_str());
	
	command = "dot -Tpng ";;
	command.append(fileName);
	command.append(" -O");
	system(command.c_str());
	
	return 0;
}

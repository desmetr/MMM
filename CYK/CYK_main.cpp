/*
 * CYK_main.cpp
 *
 *  Created on: Nov 16, 2014
 *      Author: jago
 */
#include <iostream>

#include "CFG/CFG.h"
#include "CYK.h"

using namespace std;

int main(int argc, char* argv[]){
	if(argc > 2){

		char* fileName = argv[1];
		cout << "Opening and parsing: " << fileName << endl;
		CFG newCFG(fileName);
		//cout << newCFG << endl;
		CYK newCYK(newCFG);


		for(int i = 2; i < argc; i++){
			cout << "Testing string: "<< argv[i] << endl;
			if(newCYK.testString(argv[i])){
				cout << "[OK] String " << argv[i] << " is in the language" << endl;
			}
			else{
				cout << "[XX] String " << argv[i] << " is not in the language" << endl;
			}
			//newCYK.visualRepresentation();
		}

	}
	else{
		cout << "error, no file or no strings specified." << endl;
		cout << "Usage: ./CYK filename_of_xml.xml string_to_test1 string_to_test2 ...." << endl;

	}

	return(0);
}



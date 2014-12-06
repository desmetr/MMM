/*
 * main.cpp
 *
 *  Created on: Nov 13, 2014
 *      Author: uauser
 */
#include "CFG.h"
#include "../CNF/CNF.h"

int main(int argc, char* argv[]){
	if(argc == 2){
		char* fileName = argv[1];
		std::cout << "Opening and parsing: " << fileName << std::endl;
		CFG newCFG(fileName);
		std::cout << newCFG << std::endl;
		newCFG.getBody('X');
		newCFG.getBody('Y');

		if ( newCFG.getToCNF() ){//apply cnf to cfg
			CNF cnf(newCFG);
			CFG cleanedCFG = cnf.run();
			std::cout << cleanedCFG << std::endl;
		}
	}
	else{
		std::cout << "error, no file specified." << std::endl;
		std::cout << "Usage: ./CFG filename_of_xml.xml" << std::endl;
	}
}


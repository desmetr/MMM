/*
 * main.cpp
 *
 *  Created on: Nov 13, 2014
 *      Author: uauser
 */
#include "CFG.h"

int main(int argc, char* argv[]){
	if(argc == 2){
		char* fileName = argv[1];
		std::cout << "Opening and parsing: " << fileName << std::endl;
		CFG newCFG(fileName);
		std::cout << newCFG;
	}
	else{
		std::cout << "error, no file specified." << std::endl;
		std::cout << "Usage: ./CFG filename_of_xml.xml" << std::endl;
	}
}


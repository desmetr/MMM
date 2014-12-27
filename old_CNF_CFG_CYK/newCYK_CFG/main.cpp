/*
 * main.cpp
 *
 *  Created on: Dec 11, 2014
 *      Author: jago
 */
#include "CFG.h"
#include "CYK.h"

int main(int argc, char* argv[]){
	if(argc < 3){
		std::cout << "Usage: ./CFG XML_FILE TEST_STRINGS_SEPERATED_BY_SPACES" << std::endl;
	}
	else{
		CFG a(argv[1]);
		std::cout << a << std::endl;
		CYK b(a);
		for(unsigned int i = 2; i < argc; i ++){
			if(b.testString(argv[i])){
				std::cout<<argv[i]<<" [Y]"<<std::endl;
			}
			else{
				std::cout <<argv[i]<<" [N]"<<std::endl;
			}
		}

	}
	std::cout<<"GOODBYE"<<std::endl;
	return 0;
}




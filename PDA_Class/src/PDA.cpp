/*
 * PDA.cpp
 *
 *  Created on: Nov 13, 2014
 *      Author: uauser
 */

#include "PDA.h"

PDA::PDA() {
	// TODO Auto-generated constructor stub

}

PDA::~PDA() {
	// TODO Auto-generated destructor stub
}

const std::stack<std::string>& PDA::getPdaStack() const {
	return PDAStack;
}

void PDA::setPdaStack(const std::stack<std::string>& pdaStack) {
	PDAStack = pdaStack;
}

/*
 * PDA.h
 *
 *  Created on: Nov 13, 2014
 *      Author: Rafael De Smet
 */

#ifndef PDA_H_
#define PDA_H_

#include <stack>
#include <string>
#include <set>
#include <sstream> 
#include <typeinfo>
#include "tinyxml.h"
#include "tinystr.h"
#include "State.h"
#include "Utilities.h"
#include "Transition.h"
#include "ValidateException.h"

enum SuccessEnum {FAILURE, SUCCESS};

class PDA {
public:
	PDA();
	virtual ~PDA();
	
	std::vector<State> states;

	const std::stack<std::string>& getPdaStack() const;
	void setPdaStack(const std::stack<std::string>& pdaStack);

	SuccessEnum parseXML(const char* fileName);
	void convertToEmptyStack();
	bool validateString(std::string);
	
	void print();
	
private:
	std::stack<std::string> PDAStack;
	std::set<char> inputAlphabet;
	std::set<char> stackAlphabet;
	std::string startStackSymbol;
	
	std::string algorithm;
};

std::ostream& operator<< (std::ostream& out, PDA& pda);

#endif /* PDA_H_ */

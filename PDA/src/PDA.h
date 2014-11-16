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
#include "tinyxml.h"
#include "tinystr.h"
#include "State.h"

enum SuccessEnum {FAILURE, SUCCESS};

class PDA {
public:
	PDA();
	virtual ~PDA();

	const std::stack<std::string>& getPdaStack() const;
	void setPdaStack(const std::stack<std::string>& pdaStack);

	SuccessEnum parseXML(char* fileName);

	void print();
	
private:
	std::stack<std::string> PDAStack;
	std::vector<State> states;
	std::set<char> inputAlphabet;
	std::set<char> stackAlphabet;
	std::string startStackSymbol;

};

#endif /* PDA_H_ */

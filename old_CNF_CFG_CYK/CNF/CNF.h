/*
 * CNF.h
 *
 *  Created on: Nov 21, 2014
 *      Author: bp
 */

#ifndef CNF_H_
#define CNF_H_

#include "./../CFG/CFG.h"
#include <vector>
#include <string>
#include <algorithm>

class CNF {
public:
	CNF(CFG cfg);
	virtual ~CNF();

	CFG run();

private:
	void cleanUp();
	void removeEpsylon();
	void removeUnitProductions();
	void removeUselessSymbols();

	void terminalsToVariables();
	void breakBodies();

	CFG oldCFG;
	CFG newCFG;
	std::vector<char> allChar;

	bool charInVec(std::vector<char> vec, char ch);
	using stringVec = std::vector<std::string>;
	using charVec   = std::vector<char>;

	stringVec createEpsylonProd(charVec epsylonVar, std::string prod);//is a part of the algorithm to remove epsylon transitions
	//																  it creates all the newprodcutions
	void createEpsylonProd2(std::string s, std::vector<int> nullables, std::vector<std::string>& vec);//don't change, is called recursively

	std::vector<char> createGeneratingSymbols();
	void createReachableSymbols(const charVec& genVec, charVec& reachableVar, charVec& reachableTerm);

	char createVarName();
	void split(std::string& str, charVec& leftSide, stringVec& rightSide);
};

#endif /* CNF_H_ */

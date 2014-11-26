/*
 * CYK.h
 *
 *  Created on: Nov 16, 2014
 *      Author: jago
 */

#ifndef CYK_H_
#define CYK_H_
#include "CFG/CFG.h"
#include <set>
using namespace std;

class CYK{

public:

	//set up a new class with a CFG as grammar.
	CYK(CFG& newGrammar);

	//returns true when the string is in the language of the CFG.
	bool testString(string newTest);

	int findIndex(char var);

	//for debug purposes.
	void visualRepresentation();



private:
	CFG grammar;
	string test;
	//ugly, but so be it.
	vector< vector< set<char> > > table;

	//find the productions rules that generate XY
	set<char> getHeadVar(const char X, const char Y);
	set<char> getHeadTerm(const char X);

	//keep the productions here temporarily;
	multimap<char, string> tempMap;

	//generates a table for the CYK algorithm to work with.
	void generateTable(unsigned int stringSize);




};




#endif /* CYK_H_ */

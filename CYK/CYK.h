/*
 * CYK.h
 *
 *  Created on: Nov 16, 2014
 *      Author: jago
 */

#ifndef CYK_H_
#define CYK_H_
#include "CFG/CFG.h"
using namespace std;

class CYK{

public:

	//set up a new class with a CFG as grammar.
	CYK(CFG& newGrammar);

	//returns true when the string is in the language of the CFG.
	bool testString(string newTest);

	//for debug purposes.
	void visualRepresentation();



private:
	CFG grammar;
	string test;
	//ugly, but so be it.
	vector< vector< vector<bool> > > table;

	//generates a table for the CYK algorithm to work with.
	void generateTable(unsigned int stringSize, unsigned int symbolSize);




};




#endif /* CYK_H_ */

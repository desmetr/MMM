/*
 * CYK.h
 *
 *  Created on: Dec 13, 2014
 *      Author: jago
 */

#ifndef CYK_H_
#define CYK_H_

#include "CFG.h"
#include <set>

using std::set;
using std::vector;
using CFGPointer = std::shared_ptr<CFG>;
using mapPointer = std::shared_ptr<std::multimap<variable*,vector<basic*> > >;

class CYK{
public:
	//set up a new CYK module with CFG as grammar.
	CYK(CFG& _grammar);

	//Returns true if string is in language
	bool testString(string& newTest);

	//visual representation of the table for debug.
	void visualRepresentation();
private:

	//grammar we are testing on.
	CFGPointer grammar;
	//the CYK table
	vector<vector<set<basic*> > > table;
	//generates a fitting CYK table
	void generateTable(unsigned int stringSize);
	//temporary copy of the productions map.
	mapPointer tempMap;
	//find the variables that generates the string
	set<variable*> findHeadVariable(const string testContent);
	string variablesToString(variable* a, variable* b);

	int termSize(string& toCount);


};


#endif /* CYK_H_ */

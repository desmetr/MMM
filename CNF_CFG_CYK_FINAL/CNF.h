/*
 * CNF.h
 *
 *  Created on: Nov 21, 2014
 *      Author: bp
 */

#ifndef CNF_H_
#define CNF_H_

#include "CFG.h"
#include "basics.h"

#include <vector>
#include <string>
#include <algorithm>



using std::vector;
using std::multimap;
using std::string;

using varptr = std::shared_ptr<variable>;
using rule = std::pair< variable*,vector<basic*> >;
using mapPointer = std::shared_ptr<std::multimap<variable*,vector<basic*> > >;


class CNF {
public:
	CNF(CFG* CFG);
	virtual ~CNF();

	CFG* run();

private:
	void cleanUp();
	void removeEpsylon();
	vector<vector<basic*>> createEpsilonProd(const vector<basic*>& prod, const vector<variable*>& nullables );
	void createEpsilonProd2(vector<basic*> prod, vector<int> indexNullables, vector<vector<basic*>>& _return);
	void removeUnitProductions();
	void removeUselessSymbols();

	void terminalsToVariables();
	void breakBodies();

	//nieuw
	CFG* cfg;

	string createName( const vector<string>& existingNames, string termName);
	variable* findReplacement(terminal* term, const vector< std::pair<terminal*, variable*> >& terminalReplacers);

};

#endif /* CNF_H_ */

/*
 * CFG.h
 *
 *  Created on: Dec 11, 2014
 *      Author: jago
 */

#ifndef CFG_H_
#define CFG_H_

#include "basics.h"

#include <list>
#include <memory>
#include <map>
#include "tinyxml2.h"
#include <stdexcept>
#include <iostream>
#include <vector>

using std::list;
using std::vector;
using std::multimap;
using varptr = std::shared_ptr<variable>;
using std::string;
using mapPointer = std::shared_ptr<std::multimap<variable*,vector<basic*> > >;

class CNF;
class CFG{
public:
	//constructors.
	CFG(){};
	CFG(string fileName); //parse XML cfg .

	//getters
	list<terminal> getTerminals() const;
	list<variable> getVariables() const;
	variable* getStartVariable() const;
	multimap<variable*,vector<basic*> > getProductions() const;
	vector< vector<basic*> > getProductions(variable* var)const;
	mapPointer getProductionsPointer() const;


	//setters
	void setTerminals(const list<terminal>& _terminals);
	void setVariables(const list<variable>& _variables);
	void setStartVariable(/*const*/ variable* _startVariable);
	void setProductions(const multimap<variable*,vector<basic*> > _productions);

	friend std::ostream& operator<<(std::ostream& out, CFG& object);
	friend CNF;

private:
	//basic cfg components.
	list<terminal> terminals;
	list<variable> variables;
	variable* startVariable;
	multimap<variable*,vector<basic*> > productions;

	//parser functions
	void parse(string fileName);
	list<terminal> parseTerminals(string parsedTerminals);
	list<variable> parseVariables(string parsedVariables);
	void parseProductions(tinyxml2::XMLElement* productionNode);

	//internal retrieval functions [used by parser]
	variable* findVariable(string name);
	terminal* findTerminal(string name);
	vector<basic*> createBody(string body);

};




#endif /* CFG_H_ */

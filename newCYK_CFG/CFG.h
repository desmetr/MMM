/*
 * CFG.h
 *
 *  Created on: Dec 11, 2014
 *      Author: jago
 */

#ifndef CFG_H_
#define CFG_H_

#include "basics.h"

#include <vector>
#include <memory>
#include <map>
#include "tinyxml2.h"
#include <exception>
#include <iostream>

using std::vector;
using std::multimap;
using varptr = std::shared_ptr<variable>;
using std::string;
using mapPointer = std::shared_ptr<std::multimap<variable*,vector<basic*> > >;


class CFG{
public:
	//constructors.
	CFG(){};
	CFG(string fileName); //parse XML cfg .

	//getters
	vector<terminal> getTerminals() const;
	vector<variable> getVariables() const;
	varptr getStartVariable() const;
	multimap<variable*,vector<basic*> > getProductions() const;
	mapPointer getProductionsPointer() const;


	//setters
	void setTerminals(const vector<terminal>& _terminals);
	void setVariables(const vector<variable>& _variables);
	void setStartVariable(const varptr _startVariable);
	void setProductions(const multimap<variable*,vector<basic*> > _productions);

	friend std::ostream& operator<<(std::ostream& out, CFG& object);



private:
	//basic cfg components.
	vector<terminal> terminals;
	vector<variable> variables;
	varptr startVariable;
	multimap<variable*,vector<basic*> > productions;

	//parser functions
	void parse(string fileName);
	vector<terminal> parseTerminals(string parsedTerminals);
	vector<variable> parseVariables(string parsedVariables);
	void parseProductions(tinyxml2::XMLElement* productionNode);

	//internal retrieval functions [used by parser]
	variable* findVariable(string name);
	terminal* findTerminal(string name);
	vector<basic*> createBody(string body);

};




#endif /* CFG_H_ */

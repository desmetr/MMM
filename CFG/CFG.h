/*
 * CFG.h
 *
 *  Created on: Nov 13, 2014
 *      Author: uauser
 */

#ifndef CFG_H_
#define CFG_H_

#include <iostream>
#include <vector>
#include <map>
#include "tinyxml2.h"

class CFG{
public:

	//Create CFG from XML file using tinyXML
	CFG(std::string fileName);

	const std::multimap<char, std::string>& getProductions() const;
	void setProductions(const std::multimap<char, std::string>& productions);
	char getStartVariable() const;
	void setStartVariable(char startVariable);
	const std::vector<char>& getTerminals() const;
	void setTerminals(const std::vector<char>& terminals);
	const std::vector<char>& getVariables() const;
	void setVariables(const std::vector<char>& variables);

private:

	//basic CFG elements
	std::multimap<char, std::string> productions;
	std::vector<char> terminals;
	std::vector<char> variables;
	char startVariable;
};






#endif /* CFG_H_ */

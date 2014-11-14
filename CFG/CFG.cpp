/*
 * CFG.cpp
 *
 *  Created on: Nov 13, 2014
 *      Author: uauser
 */
#include "CFG.h"

const std::multimap<char, std::string>& CFG::getProductions() const {
	return productions;
}

void CFG::setProductions(const std::multimap<char, std::string>& productions) {
	this->productions = productions;
}

char CFG::getStartVariable() const {
	return startVariable;
}

void CFG::setStartVariable(char startVariable) {
	this->startVariable = startVariable;
}

const std::vector<char>& CFG::getTerminals() const {
	return terminals;
}

void CFG::setTerminals(const std::vector<char>& terminals) {
	this->terminals = terminals;
}

const std::vector<char>& CFG::getVariables() const {
	return variables;
}

void CFG::setVariables(const std::vector<char>& variables) {
	this->variables = variables;
}

CFG::CFG(std::string fileName){

	std::vector<char> tempTerminals;
	std::vector<char> tempVariables;
	char tempStartVar;

	//set up the document, load and parse it.
	tinyxml2::XMLDocument input;
	input.LoadFile(fileName.c_str());

	//check whether the specified file could actually be opened.
	if(input.ErrorID() != 0){
		std::cout << "The specified file could not be found, aborting..." << std::endl;
		return;
	}

	tinyxml2::XMLNode* root = input.FirstChild();

	std::string h = "CFG";

	if(root->Value() != h){
		std::cout << "The document does not contain a CFG root element, aborting" << std::endl;
		return;
	}

	//load the terminals from XML
	/////////////////////////////

	tinyxml2::XMLElement* termNode = root->FirstChildElement( "TERMINALS" );

	if(termNode != NULL){
		std::string terminalString = termNode->GetText();
		std::cout << "Terminals: ";
		for(unsigned int i = 0; i < terminalString.size(); i++){
			tempTerminals.push_back( terminalString[i] );
			std::cout << terminalString[i];

		}
		std::cout << std::endl;
	}

	else{
		std::cout << "No terminals section found in XML, aborting" << std::endl;
		return;
	}

	//load the variables from XML
	/////////////////////////////

	tinyxml2::XMLElement* varNode = root->FirstChildElement( "VARIABLES" );

	if(varNode != NULL){
		std::string variableString = varNode->GetText();
		std::cout << "Variables: ";
		for(unsigned int i = 0; i < variableString.size(); i++){
			tempVariables.push_back( variableString[i] );
			std::cout << variableString[i];

		}
		std::cout << std::endl;
	}

	else{
		std::cout << "No variable section found in XML, aborting" << std::endl;
		return;
	}

	//load the start variable from XML
	/////////////////////////////

	tinyxml2::XMLElement* ssNode = root->FirstChildElement( "STARTVAR" );

	if(ssNode != NULL){
		std::string ssString = ssNode->GetText();
		std::cout << "Start Symbol: ";

			tempStartVar = ssString[0];
			std::cout << ssString[0];


		std::cout << std::endl;
	}

	else{
		std::cout << "start symbol section found in XML, aborting" << std::endl;
		return;
	}

	//load and construct the productions map.
	/////////////////////////////






}






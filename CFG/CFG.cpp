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

	std::vector<std::pair<char, std::string> > foundRules;
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
		for(unsigned int i = 0; i < terminalString.size(); i++){
			tempTerminals.push_back( terminalString[i] );
		}
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
		for(unsigned int i = 0; i < variableString.size(); i++){
			tempVariables.push_back( variableString[i] );
		}
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
			tempStartVar = ssString[0];
	}

	else{
		std::cout << "start symbol section found in XML, aborting" << std::endl;
		return;
	}

	//load and construct the productions map.
	/////////////////////////////

	tinyxml2::XMLElement* prNode = root->FirstChildElement( "PRODUCTIONS" );
	if(prNode != NULL){

		//try to locate and parse all rules via the parseRules function.
		foundRules = parseRules(prNode);

	}
	else{

		std::cout << "No productions section found in XML, aborting" << std::endl;
		return;

	}

	//If we ended up here, all data should be parsed
	//Initialize all data members and display any info we need to.
	//////////////////////////////////////////////////////////////

	//Make sure the start variable is in the parsed variables and initialize the member.

	if(std::find(tempVariables.begin(),tempVariables.end(),tempStartVar) != tempVariables.end()){

		setStartVariable(tempStartVar);

	}
	else{
		std::cout << "The specified start variable is not in the variable list, aborting..." << std::endl;
		return;
	}

	//don't know if I should do checks on the rules and stuff, not doing that for now.
	setVariables ( tempVariables );
	setTerminals ( tempTerminals );

	std::multimap<char, std::string> tempProductions;

	for( std::pair<char,std::string>& rule : foundRules ){
		tempProductions.insert(rule);
	}

	setProductions(tempProductions);

}

std::vector<std::string> CFG::getBody(const char head) {
	//returns the body of all rules for a certain variable;
	//if there is no rule with the variable as head, it'll return the empty vector!

	std::cout << "Productions for " << head <<" => ";

	std::vector<std::string> foundProductions;
	if(productions.count(head) == 0){

		std::cout << "Warning: variable " << head <<" has no production bodies, returning empty." << std::endl;
		return foundProductions;

	}
	else{

		std::pair< std::multimap< char, std::string >::iterator, std::multimap< char, std::string >::iterator> range;
		range = productions.equal_range(head);

		for(std::multimap<char,std::string>::iterator it = range.first; it != range.second; ++it){

			if(it->first == head){

				foundProductions.push_back(it->second);
				std::cout << it->second << "  |  ";
			}

		}

	}
	std::cout << std::endl;
	return(foundProductions);



}

std::vector<std::pair<char, std::string> > CFG::parseRules(tinyxml2::XMLElement* prNode) {
	std::vector<std::pair<char, std::string> > returnRules;

	//look for first "HEAD" tag
	tinyxml2::XMLElement* prChildNode = prNode->FirstChildElement( "HEAD" );

	//there can be multiple of these so loop over them as long as we encounter them.
	while(prChildNode != NULL){

		//create variables to hold production info
		std::string headVar;
		std::string ruleBody;

		//find the attribute containing the HEAD variable.
		const tinyxml2::XMLAttribute* headVarAttr = prChildNode->FirstAttribute();

		if( headVarAttr != NULL){
			//extract which variable is in the head
			headVar = headVarAttr->Value();
			//try to locate the body of the production
			tinyxml2::XMLElement* prBodyNode = prChildNode->FirstChildElement( "BODY" );

			if(prBodyNode != NULL){
				//extract the body from the body node
				ruleBody = prBodyNode->GetText();
				//add a new rule with HEAD 'headVar' and body 'ruleBody' to the return Rules
				returnRules.push_back( std::pair<char, std::string>( headVar[0] , ruleBody) );

			}

			else{

				std::cout << "warning: rule with no body encountered, ignoring..." << std::endl;


			}

		}
		else{

			std::cout << "Warning: Parser encountered a rule with no head variable, ignoring." << std::endl;
		}
		prChildNode = prChildNode->NextSiblingElement();
	}

	return returnRules;

}

std::ostream& operator<<(std::ostream& out, CFG& object) {
	out<<"___________________________________"<<std::endl;
	//write terminals to console
	out<< "TERMINALS: " << std::endl;
	for(char& t : object.terminals){
		out << t;
	}
	out<< std::endl;

	//write variables to console
	out<< "VARIABLES: " << std::endl;
	for(char& v : object.variables){
		out << v;
	}
	out<< std::endl;

	//write start var to console
	out << "START VAR: " << object.startVariable << std::endl;

	//write transitions to console
	out << "PRODUCTIONS: " << std::endl;
	for(std::multimap<char,std::string>::iterator it = object.productions.begin(); it != object.productions.end(); ++it){
		out << "\t";
		out << it->first << " -> " << it->second << std::endl;
	}
	out<<"=================================="<<std::endl;


	return out;

}



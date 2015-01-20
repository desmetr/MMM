/*
 * CFG.cpp
 *
 *  Created on: Dec 11, 2014
 *      Author: jago
 */
#include "CFG.h"

CFG::CFG(string fileName){
	parse(fileName);
}

void CFG::setTerminals(const list<terminal>& _terminals) {
	terminals = _terminals;
}

void CFG::setVariables(const list<variable>& _variables) {
	variables = _variables;
}

void CFG::setStartVariable(/*const*/ variable* _startVariable) {
	startVariable = _startVariable;
}

void CFG::setProductions(const multimap<variable*, vector<basic*> > _productions) {
	productions = _productions;
}

list<terminal> CFG::getTerminals() const{
	return terminals;
}
list<variable> CFG::getVariables() const{
	return variables;
}
variable* CFG::getStartVariable() const{
	return startVariable;
}
multimap<variable*,vector<basic*> > CFG::getProductions() const{
	return productions;
}

vector< vector<basic*> > CFG::getProductions(variable* var)const{
	vector< vector<basic*> > prod;
	for (auto& product : productions){
		if (product.first == var){
			prod.push_back(product.second);
		}
	}
	return prod;
}

void CFG::parse(string fileName){
	//create temporary holders for parsed data.
	list<terminal> tempTerminals;
	list<variable> tempVariables;
	variable tempStartVariable;

	//set up the xml document and load it.
	tinyxml2::XMLDocument input;
	input.LoadFile(fileName.c_str());

	//check whether the file was opened correctly.
	if(input.ErrorID() != 0){
		throw std::runtime_error("The file " + fileName + " could not be found, aborting.");
		return;
	}

	//get the root of the document and check if it exists.
	tinyxml2::XMLNode* root = input.FirstChild();
	string xmlType = "CFG";
	if(root->Value() != xmlType){
		throw std::runtime_error("The file " + fileName + " does not have a CFG root element, aborting.");
		return;
	}

	//load the terminals from XML
	/////////////////////////////

	tinyxml2::XMLElement* terminalNode = root->FirstChildElement( "TERMINALS" );

	if(terminalNode != NULL){
		std::string terminalString = terminalNode->GetText();
		terminals = parseTerminals(terminalString);
	}
	else{
		throw std::runtime_error("No terminal section found in " + fileName + ", aborting.");
		return;
	}

	//load the variables from XML
	/////////////////////////////

	tinyxml2::XMLElement* variableNode = root->FirstChildElement( "VARIABLES" );

	if(variableNode != NULL){
		std::string variableString = variableNode->GetText();
		variables = parseVariables(variableString);
	}
	else{
		throw std::runtime_error("No variable section found in " + fileName + ", aborting.");
		return;
	}

	//load the start variable from XML
	/////////////////////////////

	tinyxml2::XMLElement* startVariableNode = root->FirstChildElement( "STARTVAR" );

	if(startVariableNode != NULL){
		bool found = false;
		std::string ssString = startVariableNode->GetText();
		for(auto& v : variables){
			if( v.getContent() == ssString){
				startVariable = &v;
				found = true;
				break;
			}
		}
		if(found == false){
			throw std::runtime_error("The start variable \"" + ssString + "\" was not found in the variable list of " + fileName + ", aborting.");
		}
	}
	else{
		throw std::runtime_error("No startVariable section found in " + fileName + ", aborting.");
		return;
	}

	//load the productions
	//////////////////////

	tinyxml2::XMLElement* productionNode = root->FirstChildElement("PRODUCTIONS");
	if(productionNode != NULL){
		parseProductions(productionNode);
	}
	else{
		throw std::runtime_error("No productions section in " + fileName + ", aborting.");
	}

}

list<terminal> CFG::parseTerminals(string parsedTerminals){

	list<terminal> foundTerminals;
	string terminalContent = "";

	for(unsigned int i = 0; i < parsedTerminals.size(); i++){

		if( parsedTerminals[i] != ','){
			terminalContent.push_back(parsedTerminals[i]);
		}
		else{
			foundTerminals.push_back( terminal(terminalContent) );
			terminalContent.clear();
		}
	}

	if(terminalContent != ""){
		foundTerminals.push_back( terminal(terminalContent) );
	}

	return foundTerminals;
}

list<variable> CFG::parseVariables(string parsedVariables){

	list<variable> foundVariables;
	string variableContent = "";

	for(unsigned int i = 0; i < parsedVariables.size(); i++){

		if( parsedVariables[i] != ','){
			variableContent.push_back(parsedVariables[i]);
		}
		else{
			foundVariables.push_back( variable(variableContent) );
			variableContent.clear();
		}
	}

	if(variableContent != ""){
		foundVariables.push_back( variable(variableContent) );
	}

	return foundVariables;
}

void CFG::parseProductions(tinyxml2::XMLElement* productionNode){

	//get the first productions head
	tinyxml2::XMLElement* headNode = productionNode->FirstChildElement( "HEAD" );

	while(headNode != NULL){
		string variableName;

		const tinyxml2::XMLAttribute* headNodeAttr = headNode->FirstAttribute();

		if( headNodeAttr != NULL){

			variable* head = findVariable( headNodeAttr->Value() );

			tinyxml2::XMLElement* bodyNode = headNode->FirstChildElement( "BODY" );

			if(bodyNode != NULL){
				string body;

				//allow for empty bodies(epsilon).
				if(bodyNode->GetText() != NULL){
					body = bodyNode->GetText();
				}
				else{
					body = "";
				}

				vector<basic*> productionBody = createBody(body);
				std::pair<variable*,vector<basic*> > newProduction(head,productionBody);
				productions.insert( newProduction );
			}

		}
		headNode = headNode->NextSiblingElement();
	}

}

variable* CFG::findVariable(string name){
	for(std::list<variable>::iterator it = variables.begin(); it != variables.end();it++){
		if(it->getContent() == name) return &(*it);
	}
	return NULL;
}

terminal* CFG::findTerminal(string name){
	for(std::list<terminal>::iterator it = terminals.begin(); it != terminals.end();it++){
		if(it->getContent() == name) return &(*it);
	}
	return NULL;
}

vector<basic*> CFG::createBody(string body){
	vector<basic*> productionBody;

	string bodyComponent;
	for(unsigned int i = 0; i < body.size(); i++ ){

		if(body[i] != ','){
			bodyComponent.push_back(body[i]);
		}
		else{
			basic* componentPtr = findTerminal(bodyComponent);
			if( componentPtr == NULL){
				componentPtr = findVariable(bodyComponent);
			}
			if(componentPtr != NULL){
				productionBody.push_back(componentPtr);
			}
			else{
				//std::cout << bodyComponent << std::endl;
				throw std::runtime_error("Error: Variable or terminal in production body not found, aborting.");
			}
			bodyComponent.clear();
		}

	}

	if(bodyComponent != ""){
		basic* componentPtr = findTerminal(bodyComponent);
		if( componentPtr == NULL){
			componentPtr = findVariable(bodyComponent);
		}
		if(componentPtr != NULL){
			productionBody.push_back(componentPtr);
		}
		else{
			//std::cout << bodyComponent << std::endl;
			throw std::runtime_error("Error: Variable or terminal in production body not found, aborting.");
		}
	}

	return productionBody;
}

std::ostream& operator<<(std::ostream& out, CFG& object) {
	using std::endl;
	out<<"___________________________________"<<endl;
	//write terminals to console
	out<<"| Terminals: {";
	for(auto& t : object.terminals){
		out<<t.getContent()<<",";
	}
	out<<"}"<<endl;

	//write variables
	out<<"| Variables: {";
	for(auto& v : object.variables){
		out<<v.getContent()<<",";
	}
	out<<"}"<<endl;

	//Start symbol
	out<<"| Start Symbol: " << object.startVariable->getContent() << std::endl;

	//productions
	out<<"| Productions:"<<std::endl;
	for(std::multimap<variable*,vector<basic*> >::iterator it = object.productions.begin(); it!= object.productions.end(); it++){
		out << "| " << it->first->getContent() << " -> ";
		for(auto& b : it->second){
			out << b->getContent() << ",";
		}
		out << std::endl;
	}

	return out;

}

mapPointer CFG::getProductionsPointer() const{
	return std::make_shared<std::multimap<variable*,vector<basic*> > >(productions);
}




































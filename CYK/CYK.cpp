#include "CYK.h"

CYK::CYK(CFG& newGrammar) {
	this->grammar = newGrammar;
}


bool CYK::testString(string newTest) {


	//get the length of the string
	unsigned int stringSize = newTest.size();

	//get the ammount of symbols (terminals + variables)
	unsigned int symbolSize = grammar.getVariables().size();

	//generate the table for the algorithm.
	generateTable(stringSize, symbolSize);

	//get the production map
	multimap<char,string> productions = grammar.getProductions();

	//get the variables
	vector<char> variables = grammar.getVariables();

	//SPECIAL CASE [01] :: Empty string

	/* if we can go from the start symbol to the empty string, then the test is succesful
	The CFG class should allow the empty string to be a production body so we just test on size of string here. */

	if(newTest.size() == 0){

		pair< multimap< char, string >::iterator, multimap< char, string >::iterator> nullRange;
		nullRange = productions.equal_range( grammar.getStartVariable() );

		for(multimap<char,string>::iterator it = nullRange.first; it != nullRange.second; ++it){
			if(it->first == grammar.getStartVariable() && it->second == ""){
				cout << "The empty string is in the language" << endl;
				return true;
			}
		}


	}

	//special case [02] :: first row
	//todo find more elegant solution ;)
	for(unsigned int stringPos = 0; stringPos <= stringSize; stringPos++){
		for(multimap<char,string>::iterator it = productions.begin(); it != productions.end(); ++it){
			for(unsigned int varInd =0; varInd < variables.size(); varInd ++){
				if(it->first == variables[varInd] && it->second.size() == 1 && it->second[0] == newTest[stringPos]){
					cout<<"set table entry to true "<<endl;
					table[stringPos][0][varInd] = true;
				}
			}
		}
	}


}


void CYK::generateTable(unsigned int stringSize, unsigned int symbolSize) {
	//first clear the table of any possible previous stuff.
	table.clear();

	//generate a stringSize x stringSize x symbolSize table.
	//This means that we create a stringSize x stringSize table, in which every cell has symbolSize bools.

	for(unsigned int i = 0; i < stringSize; i++){

		vector<vector<bool> > levelOne;

		for(unsigned int j = 0; j < stringSize; j++){

			vector<bool> levelTwo;

			for(unsigned int k = 0; k < symbolSize; k++){

				levelTwo.push_back(false);

			}

			levelOne.push_back(levelTwo);
		}

		table.push_back(levelOne);

	}

}

void CYK::visualRepresentation(){

	//TURN YOUR HEAD 90 TO THE RIGHT AND GET A VISUAL REPRESENTATION OF THE TABLE
	//FOR DEBUG + WHEN I INEVITABILY FORGET WHAT THE TABLE LOOKS LIKE

	for(unsigned int i = 0; i < table.size(); i++){
		cout<< " X[" << i +1  << "]";
		for(unsigned int j = 0; j < table[i].size(); j++){
			cout<< " [" << j +1 << "] "  << " {";
			for(unsigned int k = 0; k < table[i][j].size(); k++){
				cout << table[i][j][k];
			}
			cout << "} ";
		}
		cout<<endl;
	}

}
/*
 * CYK.cpp
 *
 *  Created on: Nov 16, 2014
 *      Author: jago
 */





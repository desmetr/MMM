#include "CYK.h"

CYK::CYK(CFG& newGrammar) {
	this->grammar = newGrammar;
}

set<char> CYK::getHeadVar(char X, char Y){

	//vector to hold found generating symbols
	set<char> holder;


	for(multimap<char, string>::iterator it = tempMap.begin(); it != tempMap.end(); it ++){
		if(it->second.size() == 2 && it->second[0] == X && it->second[1] == Y){
			holder.insert( it->first );
		}
	}

	return holder;

}

set<char> CYK::getHeadTerm(char X){
	//vector to hold found generating symbols
	set<char> holder;



	//find heads of productions A -> a where a  e T

	for(multimap<char, string>::iterator it = tempMap.begin(); it != tempMap.end(); it ++){
		if(it->second.size() == 1 && it->second[0] == X){
			holder.insert( it->first );
		}
	}



	//return found stuff
	return holder;
}


bool CYK::testString(string newTest) {

	//N = size of string
	unsigned int n = newTest.size();

	//Temporarily put the productions in the temp map.
	tempMap = grammar.getProductions();
//
	//Generate the table.
	generateTable(n);

	/*
	 * Set the first row of the table
	 * This means that for a string baaba
	 * the cells on the first row are filled with
	 * the variables that generate b, second cell the ones that generate a, third cell a again ....
	 */
	for(unsigned int i = 0; i < n; i++){
		set<char> found = getHeadTerm(newTest[i]);
		table[i][i].insert( found.begin(), found.end() );
	}

	/*
	 * Main chunk of the algorithm , here we set the other rows.
	 */
	//for each substring length, starting from 1 because we did 0 above.
	for(unsigned int i = 1; i < n; i++){
		//for each substring start
		for(unsigned int j = 0; j < n-i; j++){
			//for each part of the substring (k in notes)
			for(unsigned int l =0; l < i; l++){
				//find variables which are generating for each part of the substring, if they exist.
				set<char> leftSubsVar = table[j][j+l];
				set<char> rightSubsVar = table[j+l+1][j+i];

				//iterate over the contents of both the cells. creating any possible combination of variables that could generate the substring.
				for(set<char>::iterator lit = leftSubsVar.begin(); lit != leftSubsVar.end(); lit++){
					for(set<char>::iterator rit = rightSubsVar.begin(); rit != rightSubsVar.end(); rit++){
						//We're looking for variables of the form X -> lit,rit
						set<char> found = getHeadVar(*lit,*rit);
						//Insert the variables that generate lit,rit into the cell, if any were found.
						table[j][j+i].insert(found.begin(),found.end());
					}
				}


			}
		}

	}

	/*
	 * A string is part of a language when the start symbol is in the upper left cell (table[0][n-1])
	 * Do the check and return true if the string is part of the language , false if not.
	 */
	for(char v : table[0][n-1]){
		if(v==grammar.getStartVariable()) return true;
	}

	return false;

}


void CYK::generateTable(unsigned int stringSize) {
	//First clear the table.
	table.clear();

	//Initialize the table.
	for(unsigned int i = 0; i < stringSize; ++i){
		table.push_back(vector<set<char> >(stringSize));
	}


	//done!

}

void CYK::visualRepresentation(){

	for(unsigned int i = 0; i < table.size(); i++){
		for(unsigned int j = 0; j < table[i].size(); j++){
			cout << "[" << i << "][" << j << "]:{";
			for(set<char>::iterator it = table[i][j].begin(); it != table[i][j].end(); it++){
				cout << *it;
			}
			cout << "}" << endl;
		}
	}

}


int CYK::findIndex(char var){
	//function is not really needed anymore i think, might remove it later.
	vector<char> variables = grammar.getVariables();
	unsigned int index = 0;
	for(char v : variables){
		if(v == var){
			return index;
		}

		index++;
	}
	return(-1);
}

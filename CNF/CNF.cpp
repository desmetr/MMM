/*
 * CNF.cpp
 *
 *  Created on: Nov 21, 2014
 *      Author: bp
 */

#include "CNF.h"
using std::find;

/////////////////////////////////
// constructors & destructors //
///////////////////////////////
CNF::CNF() : allChar ({'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
	'a','b','c','d','e','f','g','h','i','h','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
	'0','1','2','3','4','5','6','7','8','9'}){
	// TODO Auto-generated constructor stub

}

CNF::CNF(CFG cfg): oldCFG(cfg), allChar ({'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
	'a','b','c','d','e','f','g','h','i','h','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
	'0','1','2','3','4','5','6','7','8','9'}){

}

CNF::~CNF() {
	// TODO Auto-generated destructor stub
}


////////////////////
// The Algorithm //
//////////////////

CFG CNF::run(){
	//executes the whole algorithm and returns the constructed CFG
	//the algorithm:
	// 		1 clean up the grammar
	//		2 Arrange that all bodies of length 2 or more consist of only variables
	//		3 Break bodies of length 3 or more into a cascade of two-variable-bodied productions

	std::cout << "0 CNF::run() - start cnf algorithm" << std::endl;
	cleanUp();
	std::cout << "1 CNF::run() - cleanup done" << std::endl;
	//std::cout << newCFG << std::endl;
	terminalsToVariables();
	std::cout << "2 CNF::run() - terminalsToVariables done" << std::endl;
	std::cout << newCFG << std::endl;
	breakBodies();
	std::cout << "3 CNF::run() - breakBodies done" << std::endl;
	std::cout << newCFG << std::endl;

	return newCFG;
}

void CNF::cleanUp(){
	//cleans up the pushdown automat by:
	// 		1 removing epsylon transitions
	// 		2 removing unit productions
	//		3 removing useless symbols

	newCFG.startVariable = oldCFG.startVariable;
	newCFG.terminals = oldCFG.terminals;
	newCFG.variables = oldCFG.variables;
	removeEpsylon();//past newCFG.productions aan
	std::cout << "1A CNF::cleanUp() - removeEpsylon done" << std::endl;
	//std::cout << newCFG << std::endl;
	removeUnitProductions();//past newCFG.productions aan
	std::cout << "1B CNF::cleanUp() - removeUnitProductions done" << std::endl;
	//std::cout << newCFG << std::endl;
	removeUselessSymbols();//past newCFG.productions, newCFG.variables en newCFG.terminals aan
	std::cout << "1C CNF::cleanUp() - removeUselessSymbols done" << std::endl;
	//std::cout << newCFG << std::endl;
}

void CNF::removeEpsylon(){
	//check for every variable if it has an epsylon transition, if so add it to epsylonVar
	std::vector<char> epsylonVar;
	for (auto iii : oldCFG.variables){//iii is the variable
		std::vector<std::string> vec = oldCFG.getProductions(iii);
		for (auto jjj : vec){		//jjj is the right side of the production rule
			if ( jjj == ""){
				epsylonVar.push_back(iii);
			}
		}
	}

	//now we have know all variables with an epsylon transition
	//we create the productions rules for every variable
	for (auto variable : oldCFG.variables){
		for (auto production : oldCFG.getProductions(variable)){
			std::vector<std::string> newProd = createEpsylonProd( epsylonVar, production);
			for (auto string : newProd){
				std::pair<char,std::string> rule(variable, string);
				if ( rule.second.size()>0 && !newCFG.isInMultimap(rule) ){//if production doesn't allready exist and it isn't the mepty string, add it to the productions
					newCFG.productions.insert(rule);
				}
			}

		}
	}

}

void CNF::removeUnitProductions(){
	std::vector< std::pair<char, char> > vec;

	for (std::multimap<char, std::string>::iterator iii=newCFG.productions.begin(); iii !=newCFG.productions.end(); iii++){
		if (iii->second.size() == 1
				&& find(oldCFG.variables.begin(), oldCFG.variables.end(), iii->second[0])!= oldCFG.variables.end() ){
			std::pair<char, char> rule(iii->first, iii->second[0]);
			newCFG.productions.erase(iii);
			vec.push_back(rule);
		}
	}
	//apply transitivity
	for (int iii = 0 ; iii < vec.size(); iii++){
		for (int jjj = 0; jjj < vec.size(); jjj++){
			if ( vec[iii].second == vec[jjj].first && iii != jjj){
				vec.push_back( {vec[iii].first, vec[jjj].second} );
			}
		}
	}

	//now we have all unit pairs.
	//2 adapt grammar
	for (auto pair : vec){
		std::vector<std::string> prodStrings = newCFG.getProductions(pair.second);
		for (auto str : prodStrings){
			newCFG.productions.insert( {pair.first, str} );
		}
	}

}

void CNF::removeUselessSymbols(){
	//algorithm:
	//		1 get generating symbols
	//		2 get reachable symbols
	//		3 remove productions that contain a useless symbol

	//1
	charVec genVec = createGeneratingSymbols();//only contains variables, we know that all terminals are gen.

	//2
	charVec reachableVar;
	charVec reachableTerm;
	createReachableSymbols(genVec, reachableVar, reachableTerm);//2


	newCFG.terminals = reachableTerm;

	for (std::multimap<char, std::string>::iterator iii=newCFG.productions.begin(); iii !=newCFG.productions.end(); iii++){//3
		if ( find( reachableVar.begin(), reachableVar.end() ,iii->first) == reachableVar.end() ){//left side is a useless symbol
			newCFG.productions.erase(iii);
			break;
		}
		for (auto ch : iii->second){
			if ( find( reachableVar.begin(), reachableVar.end(),iii->first) == reachableVar.end()
					&& find( reachableTerm.begin(), reachableTerm.end(),iii->first) == reachableTerm.end())//right side contains a useless symbol
				newCFG.productions.erase(iii);
		}
	}

	newCFG.terminals = reachableTerm;
	newCFG.variables = reachableVar;

	/*for (std::multimap<char, std::string>::iterator it=newCFG.productions.begin(); it!=newCFG.productions.end(); ){
			if ( !charInVec(reachableVar, it->first) ){
				//std::multimap<char, std::string>::iterator temp = it;
				std::cout << "Production erased: " << it->first <<" "<<it->second<<std::endl;
				newCFG.productions.erase(it);
			}
			else{
				it++;
			}
	}*/
}

void CNF::terminalsToVariables(){
	std::vector<char> terminals;
	std::vector<char> replacements;
	//algorithm:
	//	1 check for every production whose size > 1
	//		if it contains a terminal, we have to replace it by a newly created variable
	//	2 and that variable will have a production to the terminal


	//find the rules that only have a terminal in the second part and add them to the vectors (terminals and replacements)
	int x = 0;
	for (std::multimap<char, std::string>::iterator iii=newCFG.productions.begin(); iii !=newCFG.productions.end(); iii++){
		if (iii->second.size() == 1
				&& charInVec(newCFG.terminals, iii->second[0]) ){
			terminals.push_back(iii->second[0]);
			replacements.push_back(iii->first);
			x++;
		}
	}

	//1
	for (std::multimap<char, std::string>::iterator iii=newCFG.productions.begin(); iii !=newCFG.productions.end(); iii++){//for every production
		if ( iii->second.size() > 1 ){
			for (int jjj = 0; jjj < iii->second.size(); jjj++){//for every char in the right side of the production
				if ( find(newCFG.terminals.begin(), newCFG.terminals.end(), iii->second[jjj]) != newCFG.terminals.end()){////if the char is a terminal
					std::string name;
					for (int kkk=0; kkk<terminals.size(); kkk++){//find the replacement
						if ( terminals[kkk] == iii->second[jjj] ){
							name += replacements[kkk];
							break;
						}
					}
					if( name.size() == 0 ){//if it hasn't a replacement yet
						name += createVarName();
						terminals.push_back( iii->second[jjj] );
						replacements.push_back(name[0]);
					}

					//replace the terminal in the right side of the production by its replacement
					iii->second[jjj] = name[0];
				}
			}
		}
	}
	//2
	for (int iii=x; iii<terminals.size(); iii++){
		std::string tempString;
		tempString += terminals[iii];
		std::pair<char, std::string> rule(replacements[iii], tempString);
		newCFG.productions.insert(rule);
	}
}

void CNF::breakBodies(){
	std::vector<char> leftSide;
	std::vector<std::string> rightSide;
	int x = 0;

	//check if the right side > 2 for every production
	//if so break it up in to productions with right size =2
	//by starting at the end of the production
	for (std::multimap<char, std::string>::iterator iii=newCFG.productions.begin(); iii !=newCFG.productions.end(); iii++){
		if (iii->second.size() == 2 ){
			leftSide.push_back(iii->first);
			rightSide.push_back(iii->second);
			x++;
		}
	}
	for (std::multimap<char, std::string>::iterator iii=newCFG.productions.begin(); iii !=newCFG.productions.end(); iii++){
		while (iii->second.size() > 2 ){
			split( iii->second, leftSide, rightSide);
		}
	}

	for (int iii=x; iii<leftSide.size(); iii++){
		std::pair<char, std::string> rule{leftSide[iii], rightSide[iii]};
		newCFG.productions.insert(rule);
	}
}

bool CNF::charInVec(std::vector<char> vec, char ch){
	if ( find(vec.begin(), vec.end(), ch) != vec.end() ){
		return true;
	}
	return false;
}
using stringVec = std::vector<std::string>;
using charVec = std::vector<char>;

stringVec CNF::createEpsylonProd(charVec epsylonVar, std::string prod){//fout nog niet af
	stringVec newProductions;
	std::vector<int> nullables;//contains the indexes of the nullables

	//find all characters in prod that are nullable
	for (int iii=0; iii<prod.size(); iii++){
		if ( find(epsylonVar.begin(), epsylonVar.end(), prod[iii]) != epsylonVar.end() ){//prod[iii] is nullable
			nullables.push_back(iii);
		}
	}

	//create the new productions
	newProductions.push_back(prod);
	createEpsylonProd2(prod, nullables, newProductions);

	return newProductions;
}

void CNF::createEpsylonProd2(std::string s, std::vector<int> nullables, std::vector<std::string>& vec){
	for (int iii=nullables.size()-1; iii>=0; iii--){
		std::string temp = s;
		temp.erase( temp.begin()+nullables[iii] );
		vec.push_back(temp);
		nullables.pop_back();
		createEpsylonProd2(temp, nullables, vec);
	}
}

charVec CNF::createGeneratingSymbols(){
	charVec generatingVar;
	for (auto var : oldCFG.variables){//all terminals are generating
		std::vector<std::string> prodStrings = newCFG.getProductions( var );
		for (auto prod : prodStrings){
			bool b = true;
			for (char ch : prod){
				if ( find(oldCFG.terminals.begin(), oldCFG.terminals.end(), ch)==oldCFG.terminals.end() ){
					b = false;
				}
			}
			if (b && !charInVec(generatingVar, var)){
				generatingVar.push_back( var );
			}
		}
	}

	bool  expanded = true;
	while ( expanded ){
		expanded = false;
		for (auto var : oldCFG.variables){
			if ( find(generatingVar.begin(), generatingVar.end(), var) == generatingVar.end() ){//if the var isn't allready added
				//check if the var is generating
				std::vector<std::string> prodStrings = newCFG.getProductions( var );
				for (auto s : prodStrings){
					bool b = true;
					//if every char of a prod (of a var) is generating, then the var is generating
					for (char ch: s){
						if ( find(oldCFG.terminals.begin(), oldCFG.terminals.end(), ch) == oldCFG.terminals.end() && find(generatingVar.begin(), generatingVar.end(), ch) == generatingVar.end()){
							//a char is gen if it is a terminal or in newCFG.variables
							//so a char is not gen if isn't a terminal and it isn't in newCFG.variables
							b = false;
							break;
						}
					}
					if (b && !charInVec(generatingVar, var)){
						expanded = true;
						generatingVar.push_back(var);
					}
				}
			}
		}
	}
	return generatingVar;
}

void CNF::createReachableSymbols(const charVec& genVec, charVec& reachableVar, charVec& reachableTerm){
	charVec newVar{oldCFG.startVariable};//the start symbol is reachable
	bool added = true;
	while(added){//expand the set of reachable symbols
		added = false;
		int size = newVar.size();
		for (int iii=0; iii<size; iii++){
			//check for every char of the right side of every production of the reachable variable :
			//		-if it is a terminal
			//			-if we haven't encounterd it yet
			//			=> add it to reachableTerm
			//		-if it isn't a terminal -> it is a variable
			//			-if it is a generating var
			//			-if it isn't allready in reachables
			//			-if it isn't allready in newVar
			//			=> if all of this is true we have found a new reachable var
			stringVec prod = newCFG.getProductions(newVar[iii]);
			for (auto string : prod){
				for (auto ch : string){
					if ( charInVec(oldCFG.terminals, ch) ){
						//terminal
						if (ch == 'Y'){
							for (char ch2 : oldCFG.terminals){
							}
						}
						if ( !charInVec(reachableTerm, ch) ){
							//if we haven't encountered yet
							reachableTerm.push_back(ch);
						}
					}
					else{
						//variable
						if ( charInVec(genVec, ch) && !charInVec(reachableVar, ch) && !charInVec(newVar, ch) ){
							//it's a gen. variable we haven't encountered yet
							newVar.push_back(ch);
							added = true;
						}
					}
				}
				if (!charInVec(reachableVar, newVar[iii]) ){
					reachableVar.push_back(newVar[iii]);
				}

			}
			newVar.erase(newVar.begin(), newVar.begin()+size);//remove all the reachable variable whose production we have checked
		}
	}
}

char CNF::createVarName(){
	char newName;
	for (auto ch : allChar){//get a name for the new variable by looping over all possible names
		if ( !charInVec(newCFG.variables, ch)
				&& !charInVec(newCFG.terminals,ch) ){//if the name isn't used yet
			newName = ch;
			newCFG.variables.push_back(newName);
			break;
		}
		if (ch == '9'){
			std::cout << "There aren't enough characters to create a new name for a variable"<< std::endl;
			exit(1);
		}
	}
	return newName;
}

void CNF::split(std::string& str, charVec& leftSide, stringVec& rightSide){
	char newVar;
	//remove last 2 char of string
	std::string endOfStr = str.substr(str.size()-2, str.size());
	str.erase(str.size()-2, str.size());
	//get replacement
	//std::vector<std::string>::iterator it = find(rightSide.begin(), rightSide.end(), endOfStr);
	int x = -1;
	for (int iii=0; iii<rightSide.size(); iii++){
		if ( rightSide[iii] == endOfStr){
			x = iii;
		}
	}
	if ( x != -1 ){//if there already exists a replacement for to these variables
		newVar += leftSide[x];
	}
	else{
		newVar = createVarName();
		leftSide.push_back(newVar);
		rightSide.push_back(endOfStr);
	}
	str += newVar;
}

/*
 * CNF.cpp
 *
 *  Created on: Nov 21, 2014
 *      Author: bp
 */

#include "CNF.h"
#include <iostream>

using std::find;
using std::cout;
using std::endl;
using Iterator = multimap<variable*,vector<basic*> >::iterator;


template<typename T>
bool isInVec(T* obj, const vector<T*>& vec){
	return find(vec.begin(), vec.end(), obj) != vec.end();
}

///////////////////////////////
// constructor & destructor //
/////////////////////////////
CNF::CNF(CFG* CFG): cfg(CFG){

}

CNF::~CNF() {
	// TODO Auto-generated destructor stub
}


////////////////////
// The Algorithm //
//////////////////

CFG* CNF::run(){
	//executes the whole algorithm and returns the constructed CFG
	//the algorithm:
	// 		1 clean up the grammar
	//		2 Arrange that all bodies of length 2 or more consist of only variables
	//		3 Break bodies of length 3 or more into a cascade of two-variable-bodied productions

	cleanUp();

	terminalsToVariables();

	breakBodies();

    //cout << *cfg << endl;
	return cfg;
}

////////////
//cleanUp//
//////////

void CNF::cleanUp(){
	//cleans up the pushdown automat by:
	// 		1 removing epsylon transitions
	// 		2 removing unit productions
	//		3 removing useless symbols

	removeEpsylon();

	removeUnitProductions();

	removeUselessSymbols();
    //cout << "end of removeUselessSymbols in CNF.cpp"<< endl;

}

void CNF::removeEpsylon(){//nieuw
	//check for every production if it's an epsylon transition, if so add the first part (=the variable) to nullables
	vector<variable*> nullables;

	//basis:
	//if a var has an epsilon transition it is nullable
	for (auto& var : cfg->variables ){
		vector< vector<basic*> > varProductions = cfg->getProductions(&var);
		for (auto prod : varProductions){
			if (prod.size() == 0){
				nullables.push_back( &var );
			}
		}
	}
	//induction
	//if a variable (A) isn't in the nullables yet(B), check if it is nullable
	//	a var is nullable if a prod of the var (C) is completely nullable
	//	(so it must have a production (D) that does not contain an element that isn't a nullable var(E) ) =it must contain a nullable production
	//	if so add it (the var) to the nullables and set added to true (E)
	//if we added a nullable start the induction part again
	bool added{true};
	while (added){
		added = false;
		for (auto& var : cfg->variables ){		//(A)
			if ( !isInVec( &var, nullables) ){ //(B)
				vector< vector<basic*> > varProductions = cfg->getProductions( &var );
				for (auto& prod : varProductions){	//(C)
					bool nullable{true};
					for (auto& prodPart : prod){ //(D)
						if ( prodPart->getType()== "variable"){
							variable* ptr = static_cast<variable*>(prodPart);
							if ( !isInVec( ptr, nullables) ){//(E)
								nullable=false;
								break;
							}
						}
						else{//(E)
							nullable=false;
							break;
						}
					}
					if (nullable){//(E)
						nullables.push_back( &var );
						added = true;
						break;
					}
				}
			}
			if ( added ) break;
		}

	}

	//now we know all nullable variables
	//we create the production rule for every variable of epsylonVar
	for (auto& var: cfg->variables){
		vector< vector<basic*> > varProd = cfg->getProductions(&var);
		vector< vector<basic*> > newlyAdded;
		for (auto& production : varProd){
			vector<vector<basic*>> newProds = createEpsilonProd(production, nullables);

			for (auto& newProd : newProds){
				if ( newProd.size()>0 && find(newlyAdded.begin(), newlyAdded.end(), newProd)==newlyAdded.end() && find(varProd.begin(), varProd.end(), newProd) == varProd.end( )){
					if ( !(newProd.size()==1 && newProd[0]==&var)){//avoid productions of the form A->A
						cfg->productions.insert( {&var, newProd} );
						newlyAdded.push_back( newProd );
					}
				}
			}

		}
	}

	//delete all rules of the form A->epsilon
	for (multimap<variable*,vector<basic*> >::iterator it = cfg->productions.begin(); it!=cfg->productions.end(); ++it){
		if (it->second.size() == 0){
			cfg->productions.erase(it);
		}
	}
}

vector<vector<basic*>> CNF::createEpsilonProd(const vector<basic*>& prod, const vector<variable*>& nullables ){
	vector<vector<basic*>> _return;

	vector<int> indexesNullables;
	//find the indexes of all the variables (of the right side of the prod) that are nullable
	for (int iii=0; iii<prod.size(); iii++){
		if (prod[iii]->getType() == "variable"){
			variable* tempPtr = static_cast<variable*>(prod[iii]);
			if ( isInVec(tempPtr, nullables) ){
				indexesNullables.push_back(iii);
			}
		}
	}

	//make all the possible combinations
	if (indexesNullables.size() > 0){
		createEpsilonProd2( prod, indexesNullables, _return);
	}

	return _return;
}

void CNF::createEpsilonProd2(vector<basic*> prod, vector<int> indexNullables, vector<vector<basic*>>& _return){
	for (int iii=indexNullables.size()-1; iii>=0; iii--){
		vector<basic*> temp = prod;
		temp.erase( temp.begin()+indexNullables[iii]);
		_return.push_back(temp);
		indexNullables.pop_back();
		createEpsilonProd2(temp, indexNullables, _return);
	}
}

void CNF::removeUnitProductions(){//nieuw
	vector< std::pair<variable*, variable*> > unitProductions;

	//find the unit productions

	//-basis
	// add all pairs of the sort (A,A)
	for (auto& var : cfg->variables){
		unitProductions.emplace_back( &var, &var );
	}
	//-induction
	// if the second part of a production (A) has size = 1 (B)
	// if the element of that production is a variable 	  (C)
	// apply the transitivity (D)
	for (Iterator it = cfg->productions.begin(); it != cfg->productions.end(); ++it){//(A)
		if ( it->second.size() == 1 && it->second.at(0)->getType()=="variable"){//(B) & (C)
			//we found a unit production
			std::pair<variable*, variable*> foundUnitProd{ it->first, static_cast<variable*> (it->second.at(0))};

			for (auto& unitProd : unitProductions){// (D)
				//transitivity

				if ( unitProd.first != unitProd.second ){
					if ( foundUnitProd.first == unitProd.second ){
						std::pair<variable*, variable*> transitifUnitPair{ unitProd.first, foundUnitProd.second};
						auto iter = find(unitProductions.begin(), unitProductions.end(), transitifUnitPair);
						if ( iter == unitProductions.end() ) {
							unitProductions.push_back(transitifUnitPair);
						}
					}
					else if ( foundUnitProd.second == unitProd.first){
						std::pair<variable*, variable*> transitifUnitPair{ foundUnitProd.first, unitProd.second};
						auto iter = find(unitProductions.begin(), unitProductions.end(), transitifUnitPair);
						if ( iter == unitProductions.end() ) {
							unitProductions.push_back(transitifUnitPair);
						}
					}
				}

				//end transivity
			}

			unitProductions.push_back(foundUnitProd);
			//end new unit production
		}
	}

	//now we have all unit productions, we can make the new grammar
	multimap<variable*,vector<basic*> > newProductions;
	for (auto& unit : unitProductions){
		vector< vector<basic*> > varProd = cfg->getProductions(unit.second);
		for (auto& pr : varProd){
			if ( pr[0]->getType()=="terminal" || pr.size()!=1 ){//if it isn't a unit production
				newProductions.insert({unit.first, pr});
			}
		}
	}
	cfg->productions = newProductions;

}

void CNF::removeUselessSymbols(){//nieuw
	//algorithm:
	//		1 get generating symbols
	//		2 get reachable symbols
	//		3 remove productions that contain a useless symbol

	//get generating symbols
	//-basis
	// all terminals are generating
	vector<basic*> generatingSymbols;
	for (auto& term : cfg->terminals){
		generatingSymbols.push_back(&term);
	}
	//-induction
	// if a variable (A) has a production (B) with only generating symbols (C), it is generating
	bool added{true};
	while (added){
		added = false;
		for (auto& var : cfg->variables){//(A)
			basic* tempPtr = &var;
			if ( !isInVec( tempPtr, generatingSymbols) ){
				vector< vector<basic*> > varProductions = cfg->getProductions( &var );
				for (auto& prod : varProductions){//(B)
					bool generating{true};
					for (auto& basicEl : prod){//(C)
						if ( !isInVec( basicEl, generatingSymbols) ){
							generating = false;
							break;
						}
					}
					if ( generating ){
						generatingSymbols.push_back(&var);
						added = true;
						break;
					}
				}
				if (added) break;
			}
		}
	}

	//Remove non-generating symbols from the productions
	removeFromProductions( generatingSymbols );


	//get reachable symbols
	//-basis
	// the start variable is reachable
	vector<basic*> reachables{ &(*cfg->startVariable) };
	//-induction
	// if a basic element is in a production of a generating variable
	vector<variable*> newVars{ &(*cfg->startVariable) };
	while ( newVars.size()>0 ){
		int size = newVars.size();
		for (auto& var : newVars){
			vector< vector<basic*> > varProductions = cfg->getProductions( var );
			for (auto& production : varProductions){
				for (auto& prodEl : production){
					if ( isInVec(prodEl, generatingSymbols) && !isInVec(prodEl, reachables)){
						if ( prodEl->getType()=="terminal" ){//if it's a terminal
							reachables.push_back(prodEl);
						}
						else {//if it's a variable
							variable* ptr = static_cast<variable*>(prodEl);
							if ( !isInVec(ptr, newVars) ){
								newVars.push_back(ptr);
								reachables.push_back(ptr);
							}
						}
					}
				}
				//cout << endl;
			}
		}
		newVars.erase(newVars.begin(), newVars.begin()+size);
	}


	//Remove non-reachable symbols from the productions
	removeFromProductions( reachables );


	//remove useless terminals, (they are useless if they are not reachable)
	for (auto it = cfg->terminals.begin(); it != cfg->terminals.end();){
		basic* tempPtr = &(*it);
		if ( !isInVec( tempPtr, reachables) ){
			cfg->terminals.erase(it);
			it = cfg->terminals.begin();
		}
		else ++it;
	}
	//remove useless variables (they are useless if they are not generating or not reachable)
	for (auto it = cfg->variables.begin(); it!=cfg->variables.end();){
		basic* tempPtr = &(*it);
		if ( !isInVec( tempPtr, reachables) || !isInVec( tempPtr, generatingSymbols) ){
			cfg->variables.erase(it);
			it = cfg->variables.begin();
		}
		else ++it;
	}

}


void CNF::removeFromProductions(const vector<basic*>& usefulVec ){
	for (auto it=cfg->productions.begin(); it!=cfg->productions.end(); ++it){
		bool toDelete(false);
		basic* tempFirst = it->first;

		//check if the production contains a non gen symbol
		if (!isInVec( tempFirst, usefulVec) ){
			toDelete=true;
		} else {
			for (auto& prodEl : it->second){
				basic* tempSecond = prodEl;
				if ( !isInVec( tempSecond, usefulVec) ){
					toDelete = true;
					break;
				}
			}

		}

		//if the production contains a non generating symbol, delete it
		if ( toDelete ){
			cfg->productions.erase(it);
		}
	}
}

/////////////////////////
//terminalsToVariables//
///////////////////////
void CNF::terminalsToVariables(){//nieuw
	string noLiterals = "terminal";
	vector< std::pair<terminal*, variable*> > terminalReplacers;

	//get all existing names
	vector<string> allNames;
	for (auto var : cfg->variables){
		allNames.push_back(var.getContent());
	}
	for (auto term : cfg->terminals){
		allNames.push_back(term.getContent());
	}

	//get all variables of the type A->a
	for (auto& var : cfg->variables){
		vector< vector<basic*> > varProd = cfg->getProductions( &var );
		if ( varProd.size() == 1 && varProd.at(0).size() == 1){

			terminal* termPtr = static_cast<terminal*> (varProd.at(0).at(0));

			std::pair<terminal*, variable*> pair{ termPtr, &var};
			terminalReplacers.push_back( pair );
		}

	}

	//make the terminalReplacers
	//check for every part of the right side of the production if it's a terminal
	//if so we have to replace it with a variable
	//	-so first we check if we already have a variable that has a production to that term
	//	-if this isn't the case we make a new variable

	for (auto& prod : cfg->productions){
		if( prod.second.size()>1){
			for (unsigned int iii = 0; iii < prod.second.size(); ++iii){
				if ( prod.second[iii]->getType() == "terminal"){
					terminal* termPtr = static_cast<terminal*> (prod.second[iii]);
					variable* replacingVar = findReplacement( termPtr, terminalReplacers);

					if ( !replacingVar ){

						string name = createName( allNames, termPtr->getContent() );

						cfg->variables.emplace_back( name );

						replacingVar = &(cfg->variables.back());

						std::pair<terminal*, variable*> pair{ termPtr, replacingVar};
						terminalReplacers.push_back(pair);

						vector<basic*> vec{termPtr};
						std::pair<variable*, vector<basic*>> newProduction{replacingVar, vec};
						cfg->productions.insert(newProduction);

					}
					prod.second.erase( prod.second.begin()+iii );
					prod.second.insert( prod.second.begin()+iii, replacingVar);
				}
			}
		}
	}
}

string CNF::createName( const vector<string>& existingNames, string termName){//nieuw
	int iPostFix = 1;
	string sPostFix = std::to_string(iPostFix);

	//Add the postfix to the name
	string name = termName + sPostFix;

	while ( find(existingNames.begin(), existingNames.end(), name) != existingNames.end() ){
		iPostFix++;
		sPostFix = std::to_string(iPostFix);
		name = termName + sPostFix;
	}
	return name;
}

variable* CNF::findReplacement(terminal* term, const vector< std::pair<terminal*, variable*> >& terminalReplacers){
	for (auto it = terminalReplacers.begin(); it != terminalReplacers.end(); ++it){
		if ( it->first == term){
			return it->second;
		}
	}
	return nullptr;
}

////////////////
//breakBodies//
//////////////

void CNF::breakBodies(){
	vector<string> allNames;
	for (auto var : cfg->variables){
		allNames.push_back(var.getContent());
	}
	for (auto term : cfg->terminals){
		allNames.push_back(term.getContent());
	}

	//check if the right side > 2 for every production
	//if so break it up in to productions with right size =2
	//by starting at the end of the production
	for (auto it=cfg->productions.begin(); it!=cfg->productions.end(); ++it){
		while (it->second.size() > 2){


			vector<basic*> lastTwo;
			lastTwo.push_back( it->second.at(it->second.size()-2) );
			lastTwo.push_back( it->second.at(it->second.size()-1) );

			bool replaced{false};
			for (auto& prod : cfg->productions){
				//look in the cfg production  if the prod already exist
				if (prod.second.size() == 2 && prod.second.at(0)==lastTwo[0] && prod.second.at(1)==lastTwo[1]){
					replaced=true;
					it->second.erase( it->second.end()-2, it->second.end() );//erase last two
					it->second.push_back(prod.first);//add the production we have found
					break;
				}
			}
			if ( !replaced ){
				string newVarName = createName(allNames, lastTwo.at(0)->getContent() );
				cfg->variables.push_back(newVarName);
				allNames.push_back(newVarName);
				std::pair<variable*,vector<basic*>> newProduction{ &cfg->variables.back(), lastTwo};
				cfg->productions.insert(newProduction);
			}


		}
	}
}

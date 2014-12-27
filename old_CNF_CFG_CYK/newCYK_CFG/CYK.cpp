#include "CYK.h"

CYK::CYK(CFG& _grammar){
	//set grammar
	this->grammar = std::make_shared<CFG>(_grammar);

	//set productions
	this->tempMap = _grammar.getProductionsPointer();


}

void CYK::generateTable(unsigned int stringSize){
	for(unsigned int i = 0; i < stringSize; ++i){
		table.push_back(vector<set<basic* > >(stringSize));
	}
	//table generated.
}

bool CYK::testString(string _test){
	//clear the table;
	table.clear();

	//get the test string size.
	unsigned int n = _test.size();
	//first generate a table based on test string size.
	generateTable(n);


	//set the first row of the table.
	//The first row is filled with the productions that generate the terminals that are directly under the cell.
	for(unsigned int i =0 ; i < n; i++){
		string character{_test[i]};
		set<variable*> found = findHeadVariable(character);
		table[i][i].insert( found.begin(),found.end() );
	}
	//the main chunk of the algorithm, set all the other rows.

	//for each substring length (starting from one , because the first row was handled above.
	for(unsigned int i = 1; i < n; i++ ){
		//for each start of the substring:
		for(unsigned int j = 0; j < n-i; j++){
			//for each split point in the substring (k in notes)
			for(unsigned int l = 0; l < i; l++){
				//find the variables which are generating for each part of the substring, if they exist.
				set<basic*> leftVariables = table[j][j+l];
				set<basic*> rightVariables = table[j+l+1][j+i];

				//iterate over the contents of the cells
				//by doing so we create evey possible combination of variables that could generate the substring.
				for(set<basic*>::iterator lit = leftVariables.begin(); lit != leftVariables.end(); lit ++){
					for(set<basic*>::iterator rit = rightVariables.begin(); rit != rightVariables.end(); rit ++){
						//look for variables of the form X -> lit,rit
						string totalContent = (*lit)->getContent() + (*rit)->getContent();
						set<variable*> found = findHeadVariable(totalContent);
						table[j][j+i].insert(found.begin(),found.end());
					}
				}
			}
		}

	}
	for(auto v : table[0][n-1]){
		if(v->getContent()==grammar->getStartVariable()->getContent()) return true;
	}
	return false;

}

set<variable*> CYK::findHeadVariable(const string testContent){
	set<variable*> foundVariables;

	for(std::multimap<variable*,vector<basic*> >::iterator it = tempMap->begin(); it != tempMap->end(); it++){
		string productionContent;
		for(auto v : it->second){
			productionContent.append( v->getContent() );
		}
		if(productionContent == testContent){
			foundVariables.insert(it->first);
		}
	}
	//std::cout<<"ALLRIGHT" << std::endl;
	return foundVariables;

}


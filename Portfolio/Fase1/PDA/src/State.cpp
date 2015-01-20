/* * State.cpp
 *
 *  Created on: Nov 13, 2014
 *      Author: Rafael De Smet
 */

#include "State.h"

using namespace std;

State::State() {
}

State::State(string theStateName, string theType) {
	stateName = theStateName;
	type = theType;
}

State::~State() {
}

const string State::getStateName() const 								{	return stateName;	}
const string State::getType() const										{	return type;		}

void State::setStateName(const string stateName) 						{	this->stateName = stateName;		}
void State::setTransitions(const vector<Transition>& transitions) 		{	this->transitions = transitions;	}
void State::setType(string theType)										{	this->type = theType;				}

string State::toString() {
	string outputString = "";
	outputString += "(";
	outputString += stateName;
	outputString += ", ";
	outputString += type;
	outputString += ")\t";
	
	if (this->transitions.size() > 0){
		for (auto& transition : this->transitions)	{
			outputString += "";
			outputString += transition.toString();
		}
	}
	
	return outputString;
}

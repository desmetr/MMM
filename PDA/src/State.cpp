/* * State.cpp
 *
 *  Created on: Nov 13, 2014
 *      Author: Rafael De Smet
 */

#include "State.h"

using namespace std;

State::State() {
}

State::State(char theStateName) {
	stateName = theStateName;
}

State::~State() {
}

const char& State::getStateName() const 								{	return stateName;	}
const std::vector<Transition>& State::getTransitions() const 			{	return transitions;	}
bool State::isAcceptState() const 										{	return acceptState;	}
bool State::isBeginState() const 										{	return beginState;	}

void State::setStateName(const char& stateName) 						{	this->stateName = stateName;		}
void State::setTransitions(const std::vector<Transition>& transitions) 	{	this->transitions = transitions;	}
void State::setAcceptState(bool acceptState) 							{	this->acceptState = acceptState;	}
void State::setBeginState(bool beginState) 								{	this->beginState = beginState;		}

std::string State::toString() {
	string outputString = "";

	for (const auto& transition : this->transitions)	{
		outputString += stateName + ", ";
		outputString += transition.toString();
	}

	return outputString;
}

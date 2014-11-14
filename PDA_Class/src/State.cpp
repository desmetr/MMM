/*
 * State.cpp
 *
 *  Created on: Nov 13, 2014
 *      Author: uauser
 */

#include "State.h"

using namespace std;

State::State() {
	// TODO Auto-generated constructor stub

}

State::~State() {
	// TODO Auto-generated destructor stub
}

const std::string& State::getStateName() const {
	return stateName;
}

void State::setStateName(const std::string& stateName) {
	this->stateName = stateName;
}

const std::vector<Transition>& State::getTransitions() const {
	return transitions;
}

void State::setTransitions(const std::vector<Transition>& transitions) {
	this->transitions = transitions;
}

std::string State::toString() {
	string outputString = "";

	for (const auto& transition : this->transitions)	{
		outputString += stateName + ", ";
		outputString += transition.toString();
	}

	return outputString;
}

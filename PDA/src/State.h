/*
 * State.h
 *
 *  Created on: Nov 13, 2014
 *      Author: Rafael De Smet
 */

#ifndef STATE_H_
#define STATE_H_

#include <vector>
#include <string>
#include <iostream>
#include "Transition.h"

class State {
public:
	State();
	State(std::string theStateName, std::string theType);
	virtual ~State();
	
	std::vector<Transition> transitions;

	const std::string getStateName() const;
	const std::string getType() const;

	void setStateName(const std::string stateName);
	void setTransitions(const std::vector<Transition>& transitions);
	void setType(const std::string theType);

	std::string toString();

private:
	std::string stateName;
	std::string type;
};

#endif /* STATE_H_ */

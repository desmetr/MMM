/*
 * State.h
 *
 *  Created on: Nov 13, 2014
 *      Author: uauser
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
	virtual ~State();

	const std::string& getStateName() const;
	void setStateName(const std::string& stateName);
	const std::vector<Transition>& getTransitions() const;
	void setTransitions(const std::vector<Transition>& transitions);

	std::string toString();

private:
	std::string stateName;
	std::vector<Transition> transitions;
};

#endif /* STATE_H_ */

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
	State(char theStateName);
	virtual ~State();

	const char& getStateName() const;
	const std::vector<Transition>& getTransitions() const;
	bool isAcceptState() const;
	bool isBeginState() const;

	void setStateName(const char& stateName);
	void setTransitions(const std::vector<Transition>& transitions);
	void setAcceptState(bool acceptState);
	void setBeginState(bool beginState);

	std::string toString();

private:
	char stateName;
	std::vector<Transition> transitions;
	bool beginState;
	bool acceptState;
};

#endif /* STATE_H_ */

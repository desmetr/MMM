/*
 * Transition.h
 *
 *  Created on: Nov 13, 2014
 *      Author: Rafael De Smet
 */

#ifndef TRANSITION_H_
#define TRANSITION_H_

#include <string>
#include <iostream>

class Transition {
public:
	Transition();
	virtual ~Transition();
	
	const std::string& getInputSymbol() const;
	const std::string& getStackSymbolToPop() const;
	const std::string& getStackSymbolToPush() const;
	const std::string& getBeginState() const;
	const std::string& getEndState() const;
	
	void setInputSymbol(std::string& inputSymbol);
	void setStackSymbolToPop(std::string& stackSymbolToPop);
	void setStackSymbolToPush(std::string& stackSymbolToPush);
	void setBeginState(std::string beginState);
	void setEndState(std::string& endState);

	// I used a toString method instead of a print method, because the output of this method will be used in the State class.
	std::string toString();

private:
	std::string inputSymbol;
	std::string stackSymbolToPop;
	std::string stackSymbolToPush;
	std::string beginState;
	std::string endState;
};

#endif /* TRANSITION_H_ */

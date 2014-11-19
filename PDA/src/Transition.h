/*
 * Transition.h
 *
 *  Created on: Nov 13, 2014
 *      Author: Rafael De Smet
 */

#ifndef TRANSITION_H_
#define TRANSITION_H_

#include <string>

class Transition {
public:
	Transition();
	virtual ~Transition();
	
	const std::string& getInputSymbol() const;
	const std::string& getStackSymbolToPop() const;
	const std::string& getStackSymbolToPush() const;
	const std::string& getBeginState() const;
	const std::string& getEndState() const;
	
	void setInputSymbol(const std::string& inputSymbol);
	void setStackSymbolToPop(const std::string& stackSymbolToPop);
	void setStackSymbolToPush(const std::string& stackSymbolToPush);
	void setBeginState(const std::string& beginState);
	void setEndState(const std::string& endState);

	// I used a toString method instead of a print method, because the output of this method will be used in the State class.
	std::string toString() const;

private:
	std::string inputSymbol;
	std::string stackSymbolToPop;
	std::string stackSymbolToPush;
	std::string beginState;
	std::string endState;
};

#endif /* TRANSITION_H_ */

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
	void setInputSymbol(const std::string& inputSymbol);
	const std::string& getStackSymbolToPop() const;
	void setStackSymbolToPop(const std::string& stackSymbolToPop);
	const std::string& getStackSymbolToPush() const;
	void setStackSymbolToPush(const std::string& stackSymbolToPush);

	// I used a toString method instead of a print method,
	// because the output of this method will be used in the State class.
	std::string toString() const;

private:
	std::string inputSymbol;
	std::string stackSymbolToPop;
	std::string stackSymbolToPush;
};

#endif /* TRANSITION_H_ */

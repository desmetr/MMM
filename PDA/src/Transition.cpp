/*
 * Transition.cpp
 *
 *  Created on: Nov 13, 2014
 *      Author: Rafael De Smet
 */

#include "Transition.h"

using namespace std;

Transition::Transition() {
	// TODO Auto-generated constructor stub

}

Transition::~Transition() {
	// TODO Auto-generated destructor stub
}

const std::string& Transition::getInputSymbol() const {
	return inputSymbol;
}

void Transition::setInputSymbol(const std::string& inputSymbol) {
	this->inputSymbol = inputSymbol;
}

const std::string& Transition::getStackSymbolToPop() const {
	return stackSymbolToPop;
}

void Transition::setStackSymbolToPop(const std::string& stackSymbolToPop) {
	this->stackSymbolToPop = stackSymbolToPop;
}

const std::string& Transition::getStackSymbolToPush() const {
	return stackSymbolToPush;
}

void Transition::setStackSymbolToPush(const std::string& stackSymbolToPush) {
	this->stackSymbolToPush = stackSymbolToPush;
}

std::string Transition::toString() const	{
	string outputString = "";

	outputString += inputSymbol + ", " + stackSymbolToPop + "/" + stackSymbolToPush;

	return outputString;
}

/*
 * Transition.cpp
 *
 *  Created on: Nov 13, 2014
 *      Author: Rafael De Smet
 */

#include "Transition.h"

using namespace std;

Transition::Transition() {
}

Transition::~Transition() {
}

const string& Transition::getInputSymbol() const							{	return inputSymbol;			}
const string& Transition::getStackSymbolToPop() const 						{	return stackSymbolToPop;	}
const string& Transition::getStackSymbolToPush() const 						{	return stackSymbolToPush;	}
const string& Transition::getBeginState() const								{	return beginState;			}
const string& Transition::getEndState() const								{	return endState;			}

void Transition::setInputSymbol(const string& inputSymbol) 					{	this->inputSymbol = inputSymbol;			}
void Transition::setStackSymbolToPop(const string& stackSymbolToPop) 		{	this->stackSymbolToPop = stackSymbolToPop;	}
void Transition::setStackSymbolToPush(const string& stackSymbolToPush) 		{	this->stackSymbolToPush = stackSymbolToPush;}
void Transition::setBeginState(const string& beginState)					{	this->beginState = beginState;				}
void Transition::setEndState(const string& endState)						{	this->endState = endState;					}

/*string Transition::toString() const	{
	string outputString = "";

	outputString += inputSymbol + ", " + stackSymbolToPop + "/" + stackSymbolToPush;

	return outputString;
}*/

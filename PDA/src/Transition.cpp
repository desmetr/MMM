/*
 * Transition.cpp
 *
 *  Created on: Nov 13, 2014
 *      Author: Rafael De Smet
 */

#include "Transition.h"

using namespace std;

Transition::Transition() {
	inputSymbol = "";
	stackSymbolToPop = "";
	stackSymbolToPush = "";
	endState = "";
}

Transition::Transition(int beginState) {
	this->beginState = beginState;
	inputSymbol = "";
	stackSymbolToPop = "";
	stackSymbolToPush = "";
	endState = "";
}

Transition::~Transition() {
}

const int Transition::getBeginState() const									{	return beginState;			}
const string& Transition::getInputSymbol() const							{	return inputSymbol;			}
const string& Transition::getStackSymbolToPop() const 						{	return stackSymbolToPop;	}
const string& Transition::getStackSymbolToPush() const 						{	return stackSymbolToPush;	}
const string& Transition::getEndState() const								{	return endState;			}

void Transition::setInputSymbol(string& inputSymbol) 						{	this->inputSymbol = inputSymbol;			}
void Transition::setStackSymbolToPop(string& stackSymbolToPop) 				{	this->stackSymbolToPop = stackSymbolToPop;	}
void Transition::setStackSymbolToPush(string& stackSymbolToPush) 			{	this->stackSymbolToPush = stackSymbolToPush;}
void Transition::setEndState(string& endState)								{	this->endState = endState;					}

string Transition::toString()	{
	string outputString = "[";
	outputString += inputSymbol + ", " + stackSymbolToPop + "/" + stackSymbolToPush;
	outputString += ", " + endState + "] ";
	
	return outputString;
}

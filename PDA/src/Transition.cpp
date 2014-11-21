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
	beginState = "";
	endState = "";
}

Transition::~Transition() {
}

const string& Transition::getInputSymbol() const							{	return inputSymbol;			}
const string& Transition::getStackSymbolToPop() const 						{	return stackSymbolToPop;	}
const string& Transition::getStackSymbolToPush() const 						{	return stackSymbolToPush;	}
const string& Transition::getBeginState() const								{	return beginState;			}
const string& Transition::getEndState() const								{	return endState;			}

void Transition::setInputSymbol(string& inputSymbol) 					{	this->inputSymbol = inputSymbol;			}
void Transition::setStackSymbolToPop(string& stackSymbolToPop) 		{	this->stackSymbolToPop = stackSymbolToPop;	}
void Transition::setStackSymbolToPush(string& stackSymbolToPush) 		{	this->stackSymbolToPush = stackSymbolToPush;}
void Transition::setBeginState(string beginState)					{	this->beginState = beginState;				}
void Transition::setEndState(string& endState)						{	this->endState = endState;					}

string Transition::toString()	{
	string outputString = "dhsjfdhs,fgfkfddjskfj";

//	outputString += inputSymbol + ", " + stackSymbolToPop + "/" + stackSymbolToPush;

	return outputString;
}

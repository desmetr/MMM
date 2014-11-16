/*
 * PDA.cpp
 *
 *  Created on: Nov 13, 2014
 *      Author: Rafael De Smet
 */

#include "PDA.h"

using namespace std;

PDA::PDA() {
}

PDA::~PDA() {
}

const std::stack<std::string>& PDA::getPdaStack() const 		{	return PDAStack;		}

void PDA::setPdaStack(const std::stack<std::string>& pdaStack) 	{	PDAStack = pdaStack;	}

SuccessEnum PDA::parseXML(char* fileName) {
	TiXmlDocument doc;
	TiXmlElement* root;
	try	{
		// Set up the document, load and parse it.
		if (!doc.LoadFile(fileName))	{
			cerr << doc.ErrorDesc() << endl;
			return FAILURE;
		}

		root = doc.FirstChildElement();
		if (root == NULL)	{
			cerr << "Faile to load file: No root element." << endl;
			doc.Clear();
			return FAILURE;
		}
	}
	catch (exception& e)	{
		cout << e.what() << endl;
	}

	unsigned int numberOfStates;
	unsigned int numberOfInputChars;
	unsigned int numberOfStackChars;
	unsigned int numberOfAcceptStates;

	try	{
		for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())	{
			string elemName = elem->Value();
			if (elemName == "STATES")	{
				string statesString = elem->GetText();
				numberOfStates = statesString.size();
	
				for (unsigned int i = 0; i < numberOfStates; i++)	{
					State localState(statesString[i]);
					states.push_back(localState);
				}
			}
			if (elemName == "INPUT_ALPHABET")	{
				string inputAlphabetString = elem->GetText();
				numberOfInputChars = inputAlphabetString.size();
	
				for (unsigned int i = 0; i < numberOfInputChars; i++)	{
					inputAlphabet.insert(inputAlphabetString[i]);
				}
			}
			if (elemName == "STACK_ALPHABET")	{
				string stackAlphabetString = elem->GetText();
				numberOfStackChars = stackAlphabetString.size();
	
				for (unsigned int i = 0; i < numberOfStackChars; i++)	{
					stackAlphabet.insert(stackAlphabetString[i]);
				}
			}
			if (elemName == "START_STATE")	{
				const char* startState = elem->GetText();
				states[atoi(startState)].setBeginState(true);
			}
			if (elemName == "START_STACK_SYMBOL")	{
				startStackSymbol = elem->GetText();
			}
			if (elemName == "ACCEPT_STATES")	{
				string acceptStatesString = elem->GetText();
				numberOfAcceptStates = acceptStatesString.size();
	
				for (unsigned int i = 0; i < numberOfAcceptStates; i++)	{
					char acceptStateChar = acceptStatesString[i];
					int acceptStateInt;
					stringstream stream(acceptStateChar);
					stream >> acceptStateInt;
					states[acceptStateInt].setAcceptState(true);
				}
				for (const auto& state : states)	{
					cout << state.isAcceptState() << " ";
				}
				 cout << endl;
			}
		}
	}
	catch (exception& e)	{
		cout << e.what() << endl;
	}
}

void PDA::print()	{
	try	{
//		cout << "Printing a PDA." << endl;
//		cout << "States: ";
//		for (unsigned int i = 0; i < states.size(); i++)	{
//			cout << states[i].toString() << " ";
//		}
//		cout << endl;
//		
//		cout << "Input alphabet: ";
//		for (const auto& inputSymbol : inputAlphabet)	{
//			cout << inputSymbol << " ";
//		}
//		cout << endl;
//		
//		cout << "Stack alphabet: ";
//		for (const auto& stackSymbol : stackAlphabet)	{
//			cout << stackSymbol << " ";
//		}
//		cout << endl;
//		
//		cout << "Start state: ";
//		for (unsigned int i = 0; i < states.size(); i++)	{
//			if (states[i].isBeginState())
//				cout << states[i].toString() << " ";
//		}
//		cout << endl;
//		
//		cout << "Start stack symbol: ";
//		cout << startStackSymbol << endl;
		
		cout << "Accept states: ";
		for (unsigned int i = 0; i < states.size(); i++)	{
			if (states[i].isAcceptState())
				cout << states[i].toString() << " ";
		}
		cout << endl;
	}
	catch (exception& e)	{
		cout << e.what() << endl;
	}
}
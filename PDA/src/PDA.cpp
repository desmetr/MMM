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
		// Start parsing the general information of the PDA.
		for (TiXmlElement* elem = root->FirstChildElement(); elem != nullptr; elem = elem->NextSiblingElement())	{
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
				PDAStack.push(startStackSymbol);
			}
			if (elemName == "ACCEPT_STATES")	{
				string acceptStatesString = elem->GetText();
				numberOfAcceptStates = acceptStatesString.size();
				
				for (unsigned int i = 0; i < numberOfAcceptStates; i++)	{
					char* acceptStateChar = &acceptStatesString[i];
					int acceptStateInt = atoi(acceptStateChar);
					states[acceptStateInt].setAcceptState(true);
				}
			}
			
			unsigned int currentState = 0;
			
			// Start parsing the transitions. This is a level deeper, so we need another for loop.
			const char* numberOfTransitionChar = elem->Attribute("numberOfTransition");
			int numberOfTransition = atoi(numberOfTransitionChar);
			for (TiXmlElement* transElem = elem->FirstChildElement(); transElem != nullptr; transElem = transElem->NextSiblingElement())	{
				string transElemName = transElem->Value();
				if (transElemName == "BEGIN_STATE")	{
					string beginStateString = transElem->GetText();
					currentState = atoi(beginStateString.c_str());
					states[currentState].getTransitions()[numberOfTransition].setBeginState(beginStateString);
				}
				if (transElemName == "INPUT")	{
					states[currentState].getTransitions()[numberOfTransition].setInputSymbol(transElem->GetText());
				}
				if (transElemName == "STACK_SYMBOL_TO_POP")	{
					//cout << typeid(transElem->GetText()).name() << endl;
					states[currentState].getTransitions()[numberOfTransition].setStackSymbolToPop(transElem->GetText());
				}
				if (transElemName == "STACK_SYMBOL_TO_PUSH")	{
					states[currentState].getTransitions()[numberOfTransition].setStackSymbolToPush(transElem->GetText());
				}
				if (transElemName == "END_STATE")	{
					string endStateString = transElem->GetText();
					states[currentState].getTransitions()[numberOfTransition].setEndState(endStateString);
				}
			}
		}
		
		doc.Clear();
		return SUCCESS;
	}
	catch (exception& e)	{
		cout << e.what() << endl;
		return FAILURE;
	}
}

void PDA::print()	{
	try	{
		cout << "Printing the PDA." << endl;
		cout << "-----------------" << endl;
		cout << "\tStates: ";
		for (unsigned int i = 0; i < states.size(); i++)	{
			cout << "\t" << states[i].toString() << " ";
		}
		cout << endl;
		
		cout << "\tInput alphabet: ";
		for (const auto& inputSymbol : inputAlphabet)	{
			cout << "\t" << inputSymbol << " ";
		}
		cout << endl;
		
		cout << "\tStack alphabet: ";
		for (const auto& stackSymbol : stackAlphabet)	{
			cout << "\t" << stackSymbol << " ";
		}
		cout << endl;
		
		cout << "\tStart state: ";
		for (unsigned int i = 0; i < states.size(); i++)	{
			if (states[i].isBeginState())
				cout << "\t" << states[i].toString() << " ";
		}
		cout << endl;
		
		cout << "\tStart stack symbol: ";
		cout << "\t" << startStackSymbol << endl;
		
		cout << "\tAccept states: ";
		for (unsigned int i = 0; i < states.size(); i++)	{
			if (states[i].isAcceptState())
				cout << "\t" << states[i].toString() << " ";
		}
		cout << endl << endl;
		
		/*cout << "Printing the transitions of the PDA" << endl;
		cout << "-----------------------------------" << endl;
		
		cout << "\tBegin state: ";
		for (unsigned int i = 0; i < states.size(); i++)	{
			for (unsigned int j = 0; j < states[i].getTransitions().size(); j++)	{
				cout << "\t" << states[i].getTransitions()[j].getBeginState() << endl;
			}
		}
		cout << endl;
		
		cout << "\tInput to consume: ";
		for (unsigned int i = 0; i < states.size(); i++)	{
			for (unsigned int j = 0; j < states[i].getTransitions().size(); j++)	{
				cout << "\t" << states[i].getTransitions()[j].getInputSymbol() << endl;
			}
		}
		cout << endl;
		
		cout << "\tStack symbol to pop: ";
		for (unsigned int i = 0; i < states.size(); i++)	{
			for (unsigned int j = 0; j < states[i].getTransitions().size(); j++)	{
				cout << "\t" << states[i].getTransitions()[j].getStackSymbolToPop() << endl;
			}
		}
		cout << endl;
		
		cout << "\tStack symbol to push: ";
		for (unsigned int i = 0; i < states.size(); i++)	{
			for (unsigned int j = 0; j < states[i].getTransitions().size(); j++)	{
				cout << "\t" << states[i].getTransitions()[j].getStackSymbolToPush() << endl;
			}
		}
		cout << endl;
		
		cout << "\tEnd state: ";
		for (unsigned int i = 0; i < states.size(); i++)	{
			for (unsigned int j = 0; j < states[i].getTransitions().size(); j++)	{
				cout << "\t" << states[i].getTransitions()[j].getEndState() << endl;
			}
		}
		cout << endl;*/
		
	}
	catch (exception& e)	{
		cout << e.what() << endl;
	}
}
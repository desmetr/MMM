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

void PDA::convertToEmptyStack()	{
	// First we create two additional states. These will be the start state and the last state of the new PDA.
	State newStartState("q", "start");	// The new start state will get the name p to show the difference between the original states and the new ones.
	State newFinalState("p", "normal");	// The new final state will get the name q, for the same reasons as above.
										// And it will be a normal state, because in a PDA that accepts with an empty stack, there is no accept state.

	for (auto& state : states)	{
		if (state.getType() == "start")	{
			Transition newStartTransition("e", "Y", startStackSymbol + "Y", state.getStateName());

			stackAlphabet.insert('Y');
			startStackSymbol = "Y";
			newStartState.transitions.push_back(newStartTransition);
			newStartState.endStates.insert(state.getStateName());

			state.setType("normal");
		}
	}

	states.insert(states.begin(), newStartState);	// Add the new start state to the beginning of the states vector.
	states.push_back(newFinalState);				// Push back the new final state to the end of the states vector.

	for (auto& state : states)	{
		if (state.getType() == "accept")	{
			Transition newFinalTransition("e", "any", "e", newFinalState.getStateName());	// TODO any in stack alphabet?
			state.transitions.push_back(newFinalTransition);
			state.endStates.insert(newFinalState.getStateName());
		}
	}

	Transition lastStateTransition("e", "any", "e", newFinalState.getStateName());
	states.back().transitions.push_back(lastStateTransition);
	states.back().endStates.insert(newFinalState.getStateName());
}

/*bool PDA::validateString(string inputString)	{
	bool result = true;
	try	{
		for (const auto& character : inputString)	{
			cout << "current character: " << character << endl;
			for (auto& state : states)	{
				for (auto& transition : state.transitions)	{
					cout << transition.toString() << endl;
					if (state.getType() == "start")	{
						if (transition.getInputSymbol().compare(Utilities::charToString(character)) == 0)	{
							cout << "\t" << transition.toString() << endl;
							continue;
						}
					}
					else if (state.getType() == "normal")	{
						if (transition.getInputSymbol().compare(Utilities::charToString(character)) == 0)	{
							cout << "\t" << transition.toString() << endl;
							continue;
						}
					}
					else if (state.getType() == "accept")	{
						if (transition.getInputSymbol().compare(Utilities::charToString(character)) == 0)	{
							cout << "\t" << transition.toString() << endl;
							continue;
						}
					}
					else	{
						result = false;
					}
				}
			}
		}
	}
	catch (ValidateException& e){

		result = false;
	}
	return result;
}
*/
SuccessEnum PDA::parseXML(const char* fileName) {
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
			cerr << "Failed to load file: No root element." << endl;
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

			if (elemName == "meta-data"){
				for (TiXmlElement* metaDataElem = elem->FirstChildElement(); metaDataElem != nullptr; metaDataElem = metaDataElem->NextSiblingElement())	{
					string metaDataElemName = metaDataElem->Value();
					if (metaDataElemName == "input-alphabet")	{
						string inputAlphabetString = metaDataElem->GetText();
						numberOfInputChars = inputAlphabetString.size();

						for (unsigned int i = 0; i < numberOfInputChars; i++)	{
							inputAlphabet.insert(inputAlphabetString[i]);
						}
					}
					if (metaDataElemName == "stack-alphabet")	{
						string stackAlphabetString = metaDataElem->GetText();
						numberOfStackChars = stackAlphabetString.size();

						for (unsigned int i = 0; i < numberOfStackChars; i++)	{
							stackAlphabet.insert(stackAlphabetString[i]);
						}
					}
					if (metaDataElemName == "start-stack-symbol")	{
						startStackSymbol = metaDataElem->GetText();
						PDAStack.push(startStackSymbol);
					}
				}
			}

			if (elemName == "states")	{
				const char* numberOfStatesString = elem->Attribute("numberOfStates");
				const int numberOfStates = Utilities::constCharToInt(numberOfStatesString);

				for (TiXmlElement* stateElem = elem->FirstChildElement(); stateElem != nullptr; stateElem = stateElem->NextSiblingElement())	{
					string stateElemName = stateElem->Value();

					if (stateElemName == "state")	{
						const char* numberOfStateString = stateElem->Attribute("number");
						const int numberOfState = Utilities::constCharToInt(numberOfStateString);
						const char* type = stateElem->Attribute("type");

						State newState(numberOfStateString, type);

						for (TiXmlElement* transElem = stateElem->FirstChildElement(); transElem != nullptr; transElem = transElem->NextSiblingElement())	{
							string transElemName = transElem->Value();

							if (transElemName == "transition")	{
								Transition newTransition(numberOfState);

								const char* numberOfTransString = transElem->Attribute("number");
								int numberOfTrans = Utilities::constCharToInt(numberOfTransString);

								for (TiXmlElement* transInfoElem = transElem->FirstChildElement(); transInfoElem != nullptr; transInfoElem = transInfoElem->NextSiblingElement())	{
									string transInfoElemName = transInfoElem->Value();
									if (transInfoElemName == "input")	{
										string inputString = transInfoElem->GetText();
										newTransition.setInputSymbol(inputString);
									}
									if (transInfoElemName == "stack-symbol-to-pop")	{
										string stackSymbolToPopString = transInfoElem->GetText();
										newTransition.setStackSymbolToPop(stackSymbolToPopString);
									}
									if (transInfoElemName == "stack-symbol-to-push")	{
										string stackSymbolToPushString = transInfoElem->GetText();
										newTransition.setStackSymbolToPush(stackSymbolToPushString);
									}
									if (transInfoElemName == "end-state")	{
										string endStateString = transInfoElem->GetText();
										newTransition.setEndState(endStateString);
										newState.endStates.insert(endStateString);
									}
								}
								newState.transitions.push_back(newTransition);
							}
						}
						states.push_back(newState);
					}
				}
			}
			if (elemName == "algorithm")	{
				string algorithm = elem->GetText();
				if (algorithm == "empty")	{
					convertToEmptyStack();
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
		cout << "Meta-data:" << endl;
		cout << "\tInput alphabet:\t";
		for (const auto& inputSymbol : inputAlphabet)	{
			cout << inputSymbol << " ";
		}
		cout << endl;

		cout << "\tStack alphabet:\t";
		for (const auto& stackSymbol : stackAlphabet)	{
			cout << stackSymbol << " ";
		}
		cout << endl;

		cout << "\tStart stack symbol:";
		cout << " " << startStackSymbol << endl;

		cout << "\nStates:\n";
		for (auto& state : states)	{
			cout << "\t" << state.toString() << endl;
		}
		cout << endl;
	}
	catch (exception& e)	{
		cout << e.what() << endl;
	}
}

ostream& operator<< (ostream& out, PDA& pda)	{
	out << "digraph PDA {" << endl;
	out << "\trankdir=LR;" << endl;

	for (const auto& state : pda.states)	{
		if (state.getType() == "accept")	{
			out << "\t" << state.getStateName() << " [shape=doublecircle];" << endl;
		}
		else	{
			out << "\t" << state.getStateName() << " [shape=circle];" << endl;
		}

		string localLabel = "";
 		for (const auto& endState : state.endStates)	{
			out << "\t" << state.getStateName() << " -> " << endState << "[label=\"";
			for (const auto& transition : state.transitions)	{
				if (transition.getEndState().compare(endState) == 0)	{
					localLabel += transition.getInputSymbol() + ", " + transition.getStackSymbolToPop() + "/" + transition.getStackSymbolToPush() + "\\n";
				}
			}
			unsigned int found = localLabel.find_last_of("\\n");
			string outString = localLabel.substr(0, found - 1) + "\"]";
			out << outString << endl;
			localLabel = "";
			outString = "";
		}
	}
	out << "}";
	return out;
}

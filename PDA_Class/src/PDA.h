/*
 * PDA.h
 *
 *  Created on: Nov 13, 2014
 *      Author: uauser
 */

#ifndef PDA_H_
#define PDA_H_

#include <stack>
#include <string>

class PDA {
public:
	PDA();
	virtual ~PDA();
	const std::stack<std::string>& getPdaStack() const;
	void setPdaStack(const std::stack<std::string>& pdaStack);

private:
	std::stack<std::string> PDAStack;

};

#endif /* PDA_H_ */

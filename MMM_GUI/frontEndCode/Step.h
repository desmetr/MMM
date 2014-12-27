/*
 * Step.h
 *
 *  Created on: Dec 17, 2014
 *      Author: Rafael De Smet
 */

#ifndef STEP_H_
#define STEP_H_

#include <string>
#include <iostream>

class Step {
public:
	Step();
	virtual ~Step();

	const std::string& getStep() const;
	const std::string& getTagName() const;

	void setStep(const std::string& step);

	void print();

private:
	std::string step;

	std::string tagName = "step";
//	const std::string tagName = "step";
};

#endif /* STEP_H_ */

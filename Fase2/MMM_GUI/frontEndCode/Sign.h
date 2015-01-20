/*
 * Sign.h
 *
 *  Created on: Dec 18, 2014
 *      Author: Rafael De Smet
 */

#ifndef SIGN_H_
#define SIGN_H_

#include <string>
#include <iostream>

class Sign {
public:
	Sign();
	virtual ~Sign();

	const std::string& getSign() const;
	const std::string& getTagName() const;

	void setSign(const std::string& sign);

	void print();

private:
	std::string sign;

	std::string tagName = "sign";
};

#endif /* SIGN_H_ */

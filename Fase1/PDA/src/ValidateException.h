/*
 * ValidateException.h
 *
 *  Created on: Nov 26, 2014
 *      Author: Rafael De Smet
 */

#ifndef VALIDATEEXCEPTION_H_
#define VALIDATEEXCEPTION_H_

#include <stdexcept>

class ValidateException : public std::exception {
public:
	ValidateException();
	~ValidateException();
	
	enum exceptionCodes	{
		code1,
		code2,
		code3
	};
};

#endif /* VALIDATEEXCEPTION_H_ */
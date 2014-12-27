/*
 * Formatter.h
 *
 *  Created on: Dec 21, 2014
 *      Author: bp
 */

#ifndef NEWCYK_CFG_FORMATTER_H_
#define NEWCYK_CFG_FORMATTER_H_

#include <string>
#include <exception>

using std::string;

class Formatter {
public:
	Formatter(const string& inputString);
	virtual ~Formatter();

	string getFormatedVersion() const;
private:
	string s1;//input version
	string s2;//result


	//transforms "<music><iets a="...">...</iets></music>"
	//into : "<music>,<iets a=",.,.,.,">,.,.,.,</iets>,</music>"
	void applyTransformation();
};

#endif /* NEWCYK_CFG_FORMATTER_H_ */

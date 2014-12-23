/*
 * Formatter.h
 *
 *  Created on: Dec 21, 2014
 *      Author: bp
 */

#ifndef NEWCYK_CFG_FORMATTER_H_
#define NEWCYK_CFG_FORMATTER_H_

#include <exception>
#include <iostream>
#include <fstream>
#include <string>
using std::string;

class Formatter {
public:
	Formatter(string fileName);
	virtual ~Formatter();

	string getFormatedVersion() const;
private:
	string s1;//input version
	string s2;//result

	void OpenFileAndremoveSpaces(string fileName);
	//transforms "<music><iets a="...">...</iets></music>"
	//into : "<music>,<iets a=",.,.,.,">,.,.,.,</iets>,</music>"
	void applyTransformation();
};

#endif /* NEWCYK_CFG_FORMATTER_H_ */

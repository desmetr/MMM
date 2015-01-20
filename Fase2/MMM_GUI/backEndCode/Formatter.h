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
	/*>
	 * opens  a file and removes blanks
	 * puts the result of that operation in s1
	 *
	 * then transforms s1 that looks like"<music><iets a="...">...</iets></music>"
	 * into : "<music>,<iets a=",.,.,.,">,.,.,.,</iets>,</music>" and saves it in s2
	 */

	virtual ~Formatter();

	string getFormatedVersion() const;
	/*
	 * returns s2
	 */
private:
	string s1;//temporary version
	string s2;//result

	void OpenFileAndremoveSpaces(string fileName);

	void applyTransformation();
	//transforms "<music><iets a="...">...</iets></music>"
	//into : "<music>,<iets a=",.,.,.,">,.,.,.,</iets>,</music>"
};

#endif /* NEWCYK_CFG_FORMATTER_H_ */

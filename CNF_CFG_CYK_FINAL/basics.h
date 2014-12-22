/*
 * basics.h
 *
 *  Created on: Dec 11, 2014
 *      Author: jago
 */

#ifndef BASICS_H_
#define BASICS_H_

#include <string>

class basic{
public:
	std::string getContent() const;
	std::string getType() const;
	void setContent(const std::string _content);

protected:
	std::string content;
	std::string type;
};

class terminal : public basic{
public:
	terminal(){};
	terminal(std::string _content);
};

class variable : public basic{
public:
	variable(){};
	variable(std::string _content);

};

#endif /* BASICS_H_ */

/*
 * basics.cpp
 *
 *  Created on: Dec 11, 2014
 *      Author: jago
 */
#include "basics.h"

std::string basic::getContent() const{
	return content;
}

void basic::setContent(std::string _content){
	content = _content;
}

terminal::terminal(std::string _content){
	this->content = _content;
	this->type = "terminal";
}

variable::variable(std::string _content){
	this->content = _content;
	this->type = "variable";
}

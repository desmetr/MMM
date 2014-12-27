/*
 * Mode.h
 *
 *  Created on: Dec 18, 2014
 *      Author: Rafael De Smet
 */

#ifndef MODE_H_
#define MODE_H_

#include <string>
#include <iostream>

class Mode {
public:
	Mode();
	virtual ~Mode();

	const std::string& getMode() const;
	const std::string& getTagName() const;

	void setMode(const std::string& mode);

	void print();

private:
	std::string mode;

	std::string tagName = "mode";
};

#endif /* MODE_H_ */

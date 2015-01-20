/*
 * Volume.h
 *
 *  Created on: Dec 18, 2014
 *      Author: Rafael De Smet
 */

#ifndef VOLUME_H_
#define VOLUME_H_

#include <string>
#include <iostream>

class Volume {
public:
	Volume();
	virtual ~Volume();

	const std::string& getTagName() const;
	const std::string& getVolume() const;

	void setVolume(const std::string& volume);

	void print();

private:
	std::string volume;

	std::string tagName = "volume";
//	const std::string tagName = "volume";
};

#endif /* VOLUME_H_ */

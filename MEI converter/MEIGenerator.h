/*
 * MEIGenerator.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: jago
 */

#ifndef MEIGENERATOR_CPP_
#define MEIGENERATOR_CPP_

#include "PartList.h"
#include "Part.h"
#include "MEIDataContainers.h"
#include <iostream>
#include <string>
#include <map>

using std::cout;
using std::endl;
using std::stoi;
using std::to_string;


class MEIGenerator{
public:
	MEIGenerator();
	MEIGenerator(const PartList& partList,const Part& part);

	bool generateXML();

	void setMaps();

	void debugOut();
private:
	//MEI containers.
	scoreDefData scoreDef;
	vector<measureData> measures;

	//map the data
	std::map<string,int> typeMap;
};



#endif /* MEIGENERATOR_CPP_ */

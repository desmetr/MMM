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
#include "tinyxml2.h"

using std::cout;
using std::endl;
using std::stoi;
using std::to_string;


class MEIGenerator{
public:
	MEIGenerator();
	MEIGenerator(const PartList& partList,const Part& part);

	void generateXML(string fileName);

	void setMaps();

	void debugOut();
private:
	void generateHead(tinyxml2::XMLDocument& doc,tinyxml2::XMLElement* meiRoot);
	//MEI containers.
	scoreDefData scoreDef;
	vector<measureData> measures;

	//map the data
	std::map<string,int> typeMap;
	std::map<char,char> noteMap;
};



#endif /* MEIGENERATOR_CPP_ */

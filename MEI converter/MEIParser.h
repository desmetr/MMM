#ifndef MEIPARSER_H_
#define MEIPARSER_H_

#include <iostream>
#include "tinyxml2.h"
#include <stdexcept>
#include <string>
//#include "PartList.h"
//#include "Part.h"
#include "MEIDataContainers.h"


/*
* This class parses an MEI file and puts the parsed data in objects
* the object data can then be used to generate a MusicXML file.
 */

enum succesEnum{FAILURE,SUCCES};

using std::string;
using std::cout;
using std::endl;
using std::stoi;

class MEIParser{
public:
	MEIParser();
	virtual ~MEIParser();

	succesEnum parse(string fileName);

	void debugOut();

private:
	//al mijn data gaat in jouw klasses gemapt worden uiteindelijk , maar dat is voor als de parser af is.
//	PartList partList;
//	Part part;

	//checks if an XMLElement* is NULL , throws an exception if it is , because it indicates a parser or XML error
	void checkElement(tinyxml2::XMLElement* el);

	//hold scoreDef data
	scoreDefData scoreDefContainer;

	//parses a scoredef element to the scoreDefContainer.
	void parseScoreDef(tinyxml2::XMLElement* elpointer);


};





#endif



#ifndef MEIPARSER_H_
#define MEIPARSER_H_

#include <iostream>
#include "tinyxml2.h"
#include <stdexcept>
#include <string>
#include "PartList.h"
#include "Part.h"
#include "MEIDataContainers.h"
#include <map>


/*
* This class parses an MEI file and puts the parsed data in objects
* the object data can then be used to generate a MusicXML file.
 */


using std::string;
using std::cout;
using std::endl;
using std::stoi;
using std::to_string;

class MEIParser{
public:
	MEIParser();
	virtual ~MEIParser();

	void parse(string fileName);
	//maps the intermediate data structures onto proper musicXML based dataStructures (used by MusicXML parser.)
	void mapData();
	void debugOut();

	PartList getPartList() const;
	Part getPart() const;

private:
	//al mijn data gaat in jouw klasses gemapt worden uiteindelijk , maar dat is voor als de parser af is.
	PartList partList;
	Part part;

	//checks if an XMLElement* is NULL , throws an exception if it is , because it indicates a parser or XML error
	void checkElement(tinyxml2::XMLElement* el);

	//hold scoreDef data
	scoreDefData scoreDefContainer;
	vector<measureData> measures;

	//parses a scoredef element to the scoreDefContainer.
	void parseScoreDef(tinyxml2::XMLElement* elpointer);

	//parses a section element to measureData container(s);
	void parseSection(tinyxml2::XMLElement* section);

	int generateNoteY(char name, int octave);
	double generateNoteX();
	string generateNoteType(int number);

	//used for note location generation. Yes this is weird.
	bool firstMeasure = true;
	double x = 0.0;
	std::map<char,double> noteMap;
	std::map<char,string> noteNameMap;
	std::map<int,string> typeMap;



};





#endif



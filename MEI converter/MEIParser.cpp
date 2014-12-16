#include "MEIParser.h"

MEIParser::MEIParser(){};
MEIParser::~MEIParser(){};

void MEIParser::checkElement(tinyxml2::XMLElement* el){
	if(el == NULL) throw std::runtime_error("Parser could not find a necessary XML element, check you files for errors.");
}

succesEnum MEIParser::parse(string fileName){
	tinyxml2::XMLDocument meiFile;

	//load the MEI xml file.
	meiFile.LoadFile(fileName.c_str());
	//check if file opened correctly.
	if(meiFile.ErrorID() != 0){
		throw std::runtime_error("File could not be opened.");
	}

	//No prob -> continue -> get root
	tinyxml2::XMLElement* meiRoot = meiFile.FirstChildElement();
	//check if root correct
	checkElement(meiRoot);

	//check MEI contents of root
	string diepeZucht = "mei";
	if(meiRoot->Value() != diepeZucht) throw std::runtime_error("Root tag is not mei - wrong file?");

	//next up is the meiHead tag (normally) which we don't save anywhere, ignoring! -> immediately request music data.
	tinyxml2::XMLElement* dataWalker = meiRoot->FirstChildElement("music")->FirstChildElement("body")->FirstChildElement("mdiv")->FirstChildElement("score");
	//check whether this element is ok
	checkElement(dataWalker);

	//get the data from the scoreDef element.
	tinyxml2::XMLElement* scoreDef = dataWalker->FirstChildElement("scoreDef");
	parseScoreDef(scoreDef);



	return SUCCES;


}

void MEIParser::parseScoreDef(tinyxml2::XMLElement* elpointer){
	//IGNORE ALL STOI ERRORS- ECLIPSE , NOT CODE ERROR!!!

	//check whether the element is ok
	checkElement(elpointer);

	//now actually get the data
	string dataHolder; //this variable temporarily holds parsed data. Useful for checks.

	//meter.count

	dataHolder = elpointer->Attribute("meter.count");
	if(dataHolder == "") throw std::runtime_error("No meter.count attribute in elpointer tag, aborting.");
	scoreDefContainer.MAAT_BOVEN_VAR = stoi(dataHolder); //IGNORE THE STOI WARNINGS, IT'S PART OF THE C++11 STANDARD BUT ECLIPSE IS SLOW ON LEARNING NEW STUFF.

	//meter.unit
	dataHolder = elpointer->Attribute("meter.unit");
	if(dataHolder == "") throw std::runtime_error("no meter.unit in elpointer tag, aborting.");
	scoreDefContainer.MAAT_ONDER_VAR = stoi(dataHolder);

	//key.mode
	dataHolder = elpointer->Attribute("key.mode");
	if(dataHolder == "") throw std::runtime_error("no key.mode in elpointer tag, aborting.");
	scoreDefContainer.SCHAAL_VAR = dataHolder;

	//"WE HAVE TO GO DEEPER!" -> parse the staffDef (aka a part 'definition' in music xml);
	//get the staffDef
	tinyxml2::XMLElement* stafDef = elpointer->FirstChildElement("staffGrp")->FirstChildElement("staffDef");
	checkElement(stafDef); // check if it is not null

	//par number
	dataHolder = stafDef->Attribute("n");
	if(dataHolder =="") throw std::runtime_error("no 'n' attribute in staffDef tag, aborting");
	scoreDefContainer.STAFF_NUMBER_VAR = stoi(dataHolder);

	//part id
	dataHolder = stafDef->Attribute("xml:id");
	if(dataHolder =="") throw std::runtime_error("no 'xml:id' attribute in staffDef tag, aborting");
	scoreDefContainer.PART_ID_VAR = dataHolder;

	//part name
	dataHolder = stafDef->Attribute("label");
	if(dataHolder =="") throw std::runtime_error("no 'label' attribute in staffDef tag, aborting");
	scoreDefContainer.PART_NAME_VAR = dataHolder;

	//get the line on which the key sits.
	dataHolder = stafDef->Attribute("clef.line");
	if(dataHolder =="") throw std::runtime_error("no 'clef.line' attribute in staffDef tag, aborting");
	scoreDefContainer.CLEF_LINE_VAR = stoi(dataHolder);

	//get the type of key sign
	dataHolder = stafDef->Attribute("clef.shape");
	if(dataHolder =="") throw std::runtime_error("no 'clef.type' attribute in staffDef tag, aborting");
	scoreDefContainer.CLEF_TYPE_VAR = dataHolder;
}

void MEIParser::debugOut(){
	cout << "[MAATSOORT]: " << scoreDefContainer.MAAT_BOVEN_VAR << "/" << scoreDefContainer.MAAT_ONDER_VAR << endl;
	cout << "[SCHAAL]: " << scoreDefContainer.SCHAAL_VAR << endl;
	cout << "[PART]: " << scoreDefContainer.STAFF_NUMBER_VAR << endl;
	cout << "\t [ID]: " << scoreDefContainer.PART_ID_VAR << endl;
	cout << "\t [LABEL]: " << scoreDefContainer.PART_NAME_VAR << endl;
	cout << "\t [SLEUTEL-LIJN]: " << scoreDefContainer.CLEF_LINE_VAR<< endl;
	cout << "\t [SLEUTEL-TYPE]: " << scoreDefContainer.CLEF_TYPE_VAR << endl;
}

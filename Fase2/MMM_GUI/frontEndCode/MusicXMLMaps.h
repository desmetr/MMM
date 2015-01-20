/*
 * MusicXMLMaps.h
 *
 *  Created on: Dec 14, 2014
 *      Author: Rafael De Smet
 */

#ifndef MUSICXMLMAPS_H_
#define MUSICXMLMAPS_H_

#include <map>
#include <iostream>
#include <string>

class MusicXMLMaps {
public:
	MusicXMLMaps();
	virtual ~MusicXMLMaps();

	std::map<std::string, std::string>& getAttributes() ;
	std::map<std::string, std::string>& getBarline() ;
	std::map<std::string, std::string>& getClef() ;
	std::map<std::string, std::string>& getCredit() ;
	std::map<std::string, std::string>& getDefaults() ;
	std::map<std::string, std::string>& getKey() ;
	std::map<std::string, std::string>& getMeasure() ;
	std::map<std::string, std::string>& getMidiInstrument() ;
	std::map<std::string, std::string>& getNote() ;
	std::map<std::string, std::string>& getPageLayout() ;
	std::map<std::string, std::string>& getPageMarginsEven() ;
	std::map<std::string, std::string>& getPageMarginsOdd() ;
	std::map<std::string, std::string>& getPart() ;
	std::map<std::string, std::string>& getPartList() ;
	std::map<std::string, std::string>& getPitch() ;
	std::map<std::string, std::string>& getPrint() ;
	std::map<std::string, std::string>& getScaling() ;
	std::map<std::string, std::string>& getScoreInstrument() ;
	std::map<std::string, std::string>& getScorePart() ;
	std::map<std::string, std::string>& getSystemLayout() ;
	std::map<std::string, std::string>& getSystemMargins() ;
	std::map<std::string, std::string>& getTime() ;

	std::map<int, std::map<std::string, std::string> >& getAllMaps();

	void fillDefaults();
	void fillScaling();
	void fillPageLayout();
	void fillPageMarginsEven();
	void fillPageMarginsOdd();

	void fillCredit();

	void fillPartList();
	void fillScorePart();
	void fillScoreInstrument();
	void fillMidiInstrument();

	void fillPart();
	void fillMeasure();
	void fillPrint();
	void fillSystemLayout();
	void fillSystemMargins();
	void fillAttributes();
	void fillKey();
	void fillTime();
	void fillClef();
	void fillNote();
	void fillPitch();
	void fillBarLine();

	void fillAllMaps();

	enum maps {defaults_, scaling_, page_layout_, page_margins_even_, page_margins_odd_, credit_, part_list_, score_part_, score_instrument_, midi_instrument_, part_, measure_, print_,
				system_layout_, system_margins_, attributes_, key_, time_, clef_, note_, pitch_, barline_	};

private:
	std::map<std::string, std::string> defaults;
	std::map<std::string, std::string> scaling;
	std::map<std::string, std::string> page_layout;
	std::map<std::string, std::string> page_margins_even;
	std::map<std::string, std::string> page_margins_odd;

	std::map<std::string, std::string> credit;

	std::map<std::string, std::string> part_list;
	std::map<std::string, std::string> score_part;
	std::map<std::string, std::string> score_instrument;
	std::map<std::string, std::string> midi_instrument;

	std::map<std::string, std::string> part;
	std::map<std::string, std::string> measure;
	std::map<std::string, std::string> print;
	std::map<std::string, std::string> system_layout;
	std::map<std::string, std::string> system_margins;
	std::map<std::string, std::string> attributes;
	std::map<std::string, std::string> key;
	std::map<std::string, std::string> time;
	std::map<std::string, std::string> clef;
	std::map<std::string, std::string> note;
	std::map<std::string, std::string> pitch;
	std::map<std::string, std::string> barline;

	std::map<int, std::map<std::string, std::string>> allMaps;
};

#endif /* MUSICXMLMAPS_H_ */

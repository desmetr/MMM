/*
 * MusicXMLMaps.cpp
 *
 *  Created on: Dec 14, 2014
 *      Author: Rafael De Smet
 */

#include "MusicXMLMaps.h"

using namespace std;

MusicXMLMaps::MusicXMLMaps() {
	fillDefaults();
	fillScaling();
	fillPageLayout();
	fillPageMarginsEven();
	fillPageMarginsOdd();
	fillCredit();
	fillPartList();
	fillScorePart();
	fillScoreInstrument();
	fillMidiInstrument();
	fillPart();
	fillMeasure();
	fillPrint();
	fillSystemLayout();
	fillSystemMargins();
	fillAttributes();
	fillKey();
	fillTime();
	fillClef();
	fillNote();
	fillPitch();
	fillBarLine();

	fillAllMaps();
}

MusicXMLMaps::~MusicXMLMaps() {
}

map<string, string>& MusicXMLMaps::getAttributes() 			{	return attributes;			}
map<string, string>& MusicXMLMaps::getBarline()  			{	return barline;				}
map<string, string>& MusicXMLMaps::getClef()  				{	return clef;				}
map<string, string>& MusicXMLMaps::getCredit()  			{	return credit;				}
map<string, string>& MusicXMLMaps::getDefaults()  			{	return defaults;			}
map<string, string>& MusicXMLMaps::getKey()  				{	return key;					}
map<string, string>& MusicXMLMaps::getMeasure()  			{	return measure;				}
map<string, string>& MusicXMLMaps::getMidiInstrument()  	{	return midi_instrument;		}
map<string, string>& MusicXMLMaps::getNote()  				{	return note;				}
map<string, string>& MusicXMLMaps::getPageLayout()  		{	return page_layout;			}
map<string, string>& MusicXMLMaps::getPageMarginsEven()  	{	return page_margins_even;	}
map<string, string>& MusicXMLMaps::getPageMarginsOdd()  	{	return page_margins_odd;	}
map<string, string>& MusicXMLMaps::getPart()  				{	return part;				}
map<string, string>& MusicXMLMaps::getPartList()  			{	return part_list;			}
map<string, string>& MusicXMLMaps::getPitch()  				{	return pitch;				}
map<string, string>& MusicXMLMaps::getPrint()  				{	return print;				}
map<string, string>& MusicXMLMaps::getScaling()  			{	return scaling;				}
map<string, string>& MusicXMLMaps::getScoreInstrument()  	{	return score_instrument;	}
map<string, string>& MusicXMLMaps::getScorePart()  			{	return score_part;			}
map<string, string>& MusicXMLMaps::getSystemLayout()  		{	return system_layout;		}
map<string, string>& MusicXMLMaps::getSystemMargins()  		{	return system_margins;		}
map<string, string>& MusicXMLMaps::getTime() 				{	return time;				}

map<int, map<string, string> >& MusicXMLMaps::getAllMaps() 	{	return allMaps;				}

void MusicXMLMaps::fillDefaults() {
	defaults.insert(make_pair("scaling", "MEI scaling"));
	defaults.insert(make_pair("page-layout", "MEI page-layout"));
}

void MusicXMLMaps::fillScaling() {
	scaling.insert(make_pair("millimeters", "MEI millimeters"));
	scaling.insert(make_pair("tenths", "MEI tenths"));
}

void MusicXMLMaps::fillPageLayout() {
	page_layout.insert(make_pair("page-height", "MEI page-height"));
	page_layout.insert(make_pair("page-width", "MEI page-width"));
	page_layout.insert(make_pair("page_margins type=\"even\"", "MEI page-margins type=\"even\""));
	page_layout.insert(make_pair("page_margins type=\"odd\"", "MEI page-margins type=\"odd\""));
}

void MusicXMLMaps::fillPageMarginsEven() {
	page_margins_even.insert(make_pair("left-margin", "MEI left-margin"));
	page_margins_even.insert(make_pair("right-margin", "MEI right-margin"));
	page_margins_even.insert(make_pair("top-margin", "MEI top-margin"));
	page_margins_even.insert(make_pair("bottom-margin", "MEI bottom-margin"));
}

void MusicXMLMaps::fillPageMarginsOdd() {
	page_margins_odd.insert(make_pair("left-margin", "MEI left-margin"));
	page_margins_odd.insert(make_pair("right-margin", "MEI right-margin"));
	page_margins_odd.insert(make_pair("top-margin", "MEI top-margin"));
	page_margins_odd.insert(make_pair("bottom-margin", "MEI bottom-margin"));
}

void MusicXMLMaps::fillCredit() {
	credit.insert(make_pair("credit-words", "MEI credit-words"));
}

void MusicXMLMaps::fillPartList() {
	part_list.insert(make_pair("part-group", "MEI part-group"));
	part_list.insert(make_pair("score-part", "MEI score-part"));
}

void MusicXMLMaps::fillScorePart() {
	score_part.insert(make_pair("part-name", "MEI part-name"));
	score_part.insert(make_pair("part-abbreviation", "MEI part-abbreviation"));
	score_part.insert(make_pair("score-instrument", "MEI score-instrument"));
	score_part.insert(make_pair("midi-instrument", "MEI midi-instrument"));
}

void MusicXMLMaps::fillScoreInstrument() {
	score_instrument.insert(make_pair("instrument-name", "MEI instrument-name"));
}

void MusicXMLMaps::fillMidiInstrument() {
	midi_instrument.insert(make_pair("midi-channel", "MEI midi-channel"));
	midi_instrument.insert(make_pair("midi-program", "MEI midi-program"));
	midi_instrument.insert(make_pair("volume", "MEI volume"));
	midi_instrument.insert(make_pair("pan", "MEI pan"));
}

void MusicXMLMaps::fillPart() {
	part.insert(make_pair("measure", "MEI measure"));
}

void MusicXMLMaps::fillMeasure() {
	measure.insert(make_pair("print", "MEI print"));
	measure.insert(make_pair("attributes", "MEI attributes"));
	measure.insert(make_pair("note", "MEI note"));
	measure.insert(make_pair("barline", "MEI barline"));
}

void MusicXMLMaps::fillPrint() {
	print.insert(make_pair("system-layout", "MEI system-layout"));
}

void MusicXMLMaps::fillSystemLayout() {
	system_layout.insert(make_pair("system-margins", "MEI system-margins"));
	system_layout.insert(make_pair("top-system-distance", "MEI top-system-distance"));
}

void MusicXMLMaps::fillSystemMargins() {
	system_margins.insert(make_pair("left-margin", "MEI left-margin"));
	system_margins.insert(make_pair("right-margin", "MEI right-margin"));
}

void MusicXMLMaps::fillAttributes() {
	attributes.insert(make_pair("divisions", "MEI divisions"));
	attributes.insert(make_pair("key", "MEI key"));
	attributes.insert(make_pair("time", "MEI time"));
	attributes.insert(make_pair("clef", "MEI clef"));
}

void MusicXMLMaps::fillKey() {
	key.insert(make_pair("fifths", "MEI fifths"));
	key.insert(make_pair("mode", "MEI mode"));
}

void MusicXMLMaps::fillTime() {
	time.insert(make_pair("beats", "MEI beats"));
	time.insert(make_pair("beats-type", "MEI beats-type"));
}

void MusicXMLMaps::fillClef() {
	clef.insert(make_pair("sign", "MEI sign"));
	clef.insert(make_pair("line", "MEI line"));
}

void MusicXMLMaps::fillNote() {
	note.insert(make_pair("pitch", "MEI pitch"));
	note.insert(make_pair("duration", "MEI duration"));
	note.insert(make_pair("voice", "MEI voice"));
	note.insert(make_pair("type", "MEI type"));
	note.insert(make_pair("stem", "MEI stem"));
}

void MusicXMLMaps::fillPitch() {
	pitch.insert(make_pair("step", "MEI step"));
	pitch.insert(make_pair("octave", "MEI octave"));
}

void MusicXMLMaps::fillBarLine() {
	barline.insert(make_pair("bar-style", "MEI bar_style"));
}

void MusicXMLMaps::fillAllMaps() {
	allMaps.insert(make_pair(0, defaults));
	allMaps.insert(make_pair(1, scaling));
	allMaps.insert(make_pair(2, page_layout));
	allMaps.insert(make_pair(3, page_margins_even));
	allMaps.insert(make_pair(4, page_margins_odd));
	allMaps.insert(make_pair(5, credit));
	allMaps.insert(make_pair(6, part_list));
	allMaps.insert(make_pair(7, score_part));
	allMaps.insert(make_pair(8, score_instrument));
	allMaps.insert(make_pair(9, midi_instrument));
	allMaps.insert(make_pair(10, part));
	allMaps.insert(make_pair(11, measure));
	allMaps.insert(make_pair(12, print));
	allMaps.insert(make_pair(13, system_layout));
	allMaps.insert(make_pair(14, system_margins));
	allMaps.insert(make_pair(15, attributes));
	allMaps.insert(make_pair(16, key));
	allMaps.insert(make_pair(17, time));
	allMaps.insert(make_pair(18, clef));
	allMaps.insert(make_pair(19, note));
	allMaps.insert(make_pair(20, pitch));
	allMaps.insert(make_pair(21, barline));
}

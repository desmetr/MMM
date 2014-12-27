#-------------------------------------------------
#
# Project created by QtCreator 2014-12-25T15:54:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MMM_GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    backEndCode/Formatter.cpp \
    backEndCode/CYK.cpp \
    backEndCode/CNF.cpp \
    backEndCode/CFG.cpp \
    backEndCode/basics.cpp \
    frontEndCode/Attribute.cpp \
    frontEndCode/BarLine.cpp \
    frontEndCode/BarStyle.cpp \
    frontEndCode/Beats.cpp \
    frontEndCode/BeatType.cpp \
    frontEndCode/Clef.cpp \
    frontEndCode/CSVGenerator.cpp \
    frontEndCode/Division.cpp \
    frontEndCode/Duration.cpp \
    frontEndCode/Fifths.cpp \
    frontEndCode/InputOutputManager.cpp \
    frontEndCode/InstrumentName.cpp \
    frontEndCode/Key.cpp \
    frontEndCode/Line.cpp \
    frontEndCode/Measure.cpp \
    frontEndCode/MEIGenerator.cpp \
    frontEndCode/MEIParser.cpp \
    frontEndCode/MidiChannel.cpp \
    frontEndCode/MidiInstrument.cpp \
    frontEndCode/MidiProgram.cpp \
    frontEndCode/Mode.cpp \
    frontEndCode/MusicXMLGenerator.cpp \
    frontEndCode/MusicXMLMaps.cpp \
    frontEndCode/MusicXMLParser.cpp \
    frontEndCode/Note.cpp \
    frontEndCode/Octave.cpp \
    frontEndCode/Pan.cpp \
    frontEndCode/Part.cpp \
    frontEndCode/PartList.cpp \
    frontEndCode/PartName.cpp \
    frontEndCode/Pitch.cpp \
    frontEndCode/ScoreInstrument.cpp \
    frontEndCode/ScorePart.cpp \
    frontEndCode/Sign.cpp \
    frontEndCode/Stem.cpp \
    frontEndCode/Step.cpp \
    frontEndCode/Time.cpp \
    frontEndCode/tinyxml2.cpp \
    frontEndCode/Type.cpp \
    frontEndCode/Utilities.cpp \
    frontEndCode/Voice.cpp \
    frontEndCode/Volume.cpp

HEADERS  += mainwindow.h \
    backEndCode/Formatter.h \
    backEndCode/CYK.h \
    backEndCode/CNF.h \
    backEndCode/CFG.h \
    backEndCode/basics.h \
    frontEndCode/Attribute.h \
    frontEndCode/BarLine.h \
    frontEndCode/BarStyle.h \
    frontEndCode/Beats.h \
    frontEndCode/BeatType.h \
    frontEndCode/Clef.h \
    frontEndCode/CSVGenerator.h \
    frontEndCode/Division.h \
    frontEndCode/Duration.h \
    frontEndCode/Fifths.h \
    frontEndCode/InputOutputManager.h \
    frontEndCode/InstrumentName.h \
    frontEndCode/Key.h \
    frontEndCode/Line.h \
    frontEndCode/Measure.h \
    frontEndCode/MEIDataContainers.h \
    frontEndCode/MEIGenerator.h \
    frontEndCode/MEIParser.h \
    frontEndCode/MidiChannel.h \
    frontEndCode/MidiInstrument.h \
    frontEndCode/MidiProgram.h \
    frontEndCode/Mode.h \
    frontEndCode/MusicXMLGenerator.h \
    frontEndCode/MusicXMLMaps.h \
    frontEndCode/MusicXMLParser.h \
    frontEndCode/Note.h \
    frontEndCode/Octave.h \
    frontEndCode/Pan.h \
    frontEndCode/Part.h \
    frontEndCode/PartList.h \
    frontEndCode/PartName.h \
    frontEndCode/Pitch.h \
    frontEndCode/ScoreInstrument.h \
    frontEndCode/ScorePart.h \
    frontEndCode/Sign.h \
    frontEndCode/Stem.h \
    frontEndCode/Step.h \
    frontEndCode/Time.h \
    frontEndCode/tinyxml2.h \
    frontEndCode/Type.h \
    frontEndCode/Utilities.h \
    frontEndCode/Voice.h \
    frontEndCode/Volume.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    ../workspace/CFGV3/MusicXML_Grammar.xml \
    ../workspace/CFGV3/MEI_Grammar.xml

QMAKE_CXXFLAGS += -std=c++11

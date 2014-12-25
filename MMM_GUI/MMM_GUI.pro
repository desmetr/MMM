#-------------------------------------------------
#
# Project created by QtCreator 2014-12-25T15:54:46
#
#-------------------------------------------------

QT       += core gui

TARGET = MMM_GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    backEndCode/tinyxml2.cpp \
    backEndCode/Formatter.cpp \
    backEndCode/CYK.cpp \
    backEndCode/CNF.cpp \
    backEndCode/CFG.cpp \
    backEndCode/basics.cpp

HEADERS  += mainwindow.h \
    backEndCode/tinyxml2.h \
    backEndCode/Formatter.h \
    backEndCode/CYK.h \
    backEndCode/CNF.h \
    backEndCode/CFG.h \
    backEndCode/basics.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    ../workspace/CFGV3/MusicXML_Grammar.xml \
    ../workspace/CFGV3/MEI_Grammar.xml

QMAKE_CXXFLAGS += -std=c++11

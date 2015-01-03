/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat Jan 3 18:09:21 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *browseButton;
    QLineEdit *browseBox;
    QLabel *label;
    QProgressBar *progressBar;
    QFrame *line;
    QPushButton *MusicXMLButton;
    QPushButton *MEIButton;
    QPushButton *CSVButton;
    QPushButton *MIDIButton;
    QTextEdit *logBox;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *mainWindow)
    {
        if (mainWindow->objectName().isEmpty())
            mainWindow->setObjectName(QString::fromUtf8("mainWindow"));
        mainWindow->resize(797, 371);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mainWindow->sizePolicy().hasHeightForWidth());
        mainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(mainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        browseButton = new QPushButton(centralWidget);
        browseButton->setObjectName(QString::fromUtf8("browseButton"));
        browseButton->setGeometry(QRect(320, 10, 85, 27));
        browseBox = new QLineEdit(centralWidget);
        browseBox->setObjectName(QString::fromUtf8("browseBox"));
        browseBox->setGeometry(QRect(10, 10, 311, 27));
        browseBox->setAcceptDrops(false);
        browseBox->setReadOnly(true);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 120, 151, 16));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(10, 270, 781, 23));
        progressBar->setValue(100);
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(450, 0, 21, 141));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        MusicXMLButton = new QPushButton(centralWidget);
        MusicXMLButton->setObjectName(QString::fromUtf8("MusicXMLButton"));
        MusicXMLButton->setGeometry(QRect(470, 10, 321, 27));
        MusicXMLButton->setCheckable(false);
        MusicXMLButton->setAutoDefault(false);
        MusicXMLButton->setFlat(false);
        MEIButton = new QPushButton(centralWidget);
        MEIButton->setObjectName(QString::fromUtf8("MEIButton"));
        MEIButton->setGeometry(QRect(470, 40, 321, 27));
        CSVButton = new QPushButton(centralWidget);
        CSVButton->setObjectName(QString::fromUtf8("CSVButton"));
        CSVButton->setGeometry(QRect(470, 70, 321, 27));
        MIDIButton = new QPushButton(centralWidget);
        MIDIButton->setObjectName(QString::fromUtf8("MIDIButton"));
        MIDIButton->setGeometry(QRect(470, 100, 321, 27));
        logBox = new QTextEdit(centralWidget);
        logBox->setObjectName(QString::fromUtf8("logBox"));
        logBox->setGeometry(QRect(10, 140, 781, 121));
        logBox->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        logBox->setAutoFormatting(QTextEdit::AutoBulletList);
        logBox->setReadOnly(true);
        mainWindow->setCentralWidget(centralWidget);
        browseButton->raise();
        browseBox->raise();
        label->raise();
        line->raise();
        progressBar->raise();
        MusicXMLButton->raise();
        MEIButton->raise();
        CSVButton->raise();
        MIDIButton->raise();
        logBox->raise();
        menuBar = new QMenuBar(mainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 797, 25));
        mainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(mainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(mainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        mainWindow->setStatusBar(statusBar);

        retranslateUi(mainWindow);

        QMetaObject::connectSlotsByName(mainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *mainWindow)
    {
        mainWindow->setWindowTitle(QApplication::translate("mainWindow", "mainWindow", 0, QApplication::UnicodeUTF8));
        browseButton->setText(QApplication::translate("mainWindow", "Browse...", 0, QApplication::UnicodeUTF8));
        browseBox->setText(QString());
        browseBox->setPlaceholderText(QApplication::translate("mainWindow", "Click the browse button to select a file...", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("mainWindow", "Output Log", 0, QApplication::UnicodeUTF8));
        MusicXMLButton->setText(QApplication::translate("mainWindow", "Convert to MusicXML", 0, QApplication::UnicodeUTF8));
        MEIButton->setText(QApplication::translate("mainWindow", "Convert to MEI", 0, QApplication::UnicodeUTF8));
        CSVButton->setText(QApplication::translate("mainWindow", "Convert to CSV", 0, QApplication::UnicodeUTF8));
        MIDIButton->setText(QApplication::translate("mainWindow", "Convert to CSV to MIDI", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class mainWindow: public Ui_mainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "frontEndCode/tinyxml2.h"
#include <QFile>
#include <string>
#include <iostream>

/* code used in xml validation */
#include "backEndCode/CFG.h"
#include "backEndCode/CNF.h"
#include "backEndCode/CYK.h"

/* code used in format conversion */
#include "backEndCode/Formatter.h"
#include "frontEndCode/MEIParser.h"
#include "frontEndCode/MusicXMLGenerator.h"
#include "frontEndCode/MusicXMLParser.h"
#include "frontEndCode/MEIGenerator.h"
#include "frontEndCode/CSVGenerator.h"

#include <stdexcept>


mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);
    //initally disable all Buttons.
    ui->MEIButton->setEnabled(false);
    ui->MusicXMLButton->setEnabled(false);
    ui->CSVButton->setEnabled(false);
    ui->MIDIButton->setEnabled(false);
}

mainWindow::~mainWindow()
{
    delete ui;
}

void mainWindow::on_browseButton_clicked()
{
    ui->logBox->clear();
    ui->progressBar->setValue(0);
    ui->MEIButton->setEnabled(false);
    ui->MusicXMLButton->setEnabled(false);
    ui->CSVButton->setEnabled(false);
    ui->MIDIButton->setEnabled(false);

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("Files (*.xml)"));
    filePath = fileName;

    /* update log and textBox + progressbar. */
    ui->logBox->insertPlainText("\nSelected file: " + fileName + " for conversion.");
    ui->browseBox->setText(fileName);
    ui->progressBar->setValue(25);

    /* enable or disable buttons based on file content */
    QFile userFile(fileName);

    if(!userFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        ui->logBox->insertPlainText("\nCould not open file "+fileName);
        return;
    }

    /* This part here does a check on which type of
      file is opened. It's a very loose check,
      we rely on the document-determining string to
      be the second string in the file. */

    QString docRoot = userFile.readLine();
    docRoot = userFile.readLine();
    std::string docRoot_s = docRoot.toStdString();
    stripEndl(docRoot_s);

    userFile.close();


    if( !strcmp(docRoot_s.c_str(),"<!DOCTYPE score-partwise PUBLIC \"-//Recordare//DTD MusicXML 2.0 Partwise//EN\" \"http://www.musicxml.org/dtds/partwise.dtd\">") ){
        ui->logBox->insertPlainText("\n[OK] this is a musicXML file.");
        fileType = "MusicXML";
        checkXML();
    }

    else if( !strcmp(docRoot_s.c_str() ,"<mei xmlns=\"http://www.music-encoding.org/ns/mei\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" meiversion=\"2013\">") ){
        ui->logBox->insertPlainText("\n[OK] this is an MEI file.");
        fileType = "MEI";
        checkXML();
    }
    else{
        ui->logBox->insertPlainText("\n[ERROR] Could not detect file format. Please ensure you have selected a musicXML or MEI file.");
        ui->progressBar->setValue(0);
    }

}

void mainWindow::stripEndl(std::string& s){
    std::string out;
    for(unsigned int i = 0; i < s.size(); i++){
        if(s[i] != '\n'){
            out.push_back(s[i]);
        }
        else{
            s = out;
            return;
        }
    }
}

bool mainWindow::checkXML(){
    std::string mxl = "MusicXML";
    std::string mei = "MEI";

    /*
      This is the main M&B - related chain.
      1) Read grammar for XML format
      2) Transform the grammar to CNF
      3) Read the input file, strip whitespace and format
      4) Test the formatted string against the CYK algorithm.
      5) If CYK returns true, it is a correct xml
    */
    if( std::strcmp(mxl.c_str(),fileType.toStdString().c_str()) == 0){
        try{
            CFG mxlGrammar("MusicXML_grammar.xml");
            CNF mxlCNF(&mxlGrammar);
            mxlCNF.run();

            ui->logBox->insertPlainText("\n[OK] Grammar loaded");
            ui->progressBar->setValue(50);

            Formatter xmlFormatter(filePath.toStdString());

            ui->logBox->insertPlainText("\n[OK] preformatted XML input.");
            ui->progressBar->setValue(75);

            CYK mxlCYK(mxlGrammar);
            string formattedString = xmlFormatter.getFormatedVersion();

            ui->logBox->insertPlainText("\n[OK] Validating XML file.");

            if(mxlCYK.testString(formattedString)){
                ui->logBox->insertPlainText("\n[OK] XML File is valid, ready for conversion.");

                /* enable all buttons that do valid conversions for the file. */
                ui->MusicXMLButton->setEnabled(false);
                ui->MEIButton->setEnabled(true);
                ui->CSVButton->setEnabled(true);
                ui->MIDIButton->setEnabled(true);
                ui->progressBar->setValue(100);

            }
            else{

                ui->logBox->insertPlainText("\n[ERROR] Invalid XML File, check the file for errors.");
                ui->progressBar->setValue(0);

            }
        }
        catch(std::exception& e){
            string errMsg = "\n";
            errMsg.append(e.what());
            ui->logBox->insertPlainText(errMsg.c_str());
            ui->progressBar->setValue(0);
            return false;
        }
    }

    if( std::strcmp(mei.c_str(),fileType.toStdString().c_str()) == 0){
        try{
            CFG meiGrammar("meiComplete_grammar.xml");
            CNF meiCNF(&meiGrammar);
            meiCNF.run();

            ui->logBox->insertPlainText("\n[OK] Grammar loaded");
            ui->progressBar->setValue(50);

            Formatter xmlFormatter(filePath.toStdString());

            ui->logBox->insertPlainText("\n[OK] preformatted XML input.");
            ui->progressBar->setValue(75);

            CYK meiCYK(meiGrammar);
            string formattedString = xmlFormatter.getFormatedVersion();

            if(meiCYK.testString(formattedString)){
                ui->logBox->insertPlainText("\n[OK] XML File is valid, ready for conversion.");

                /* enable all buttons that do valid conversions for the file. */
                ui->MusicXMLButton->setEnabled(true);
                ui->MEIButton->setEnabled(false);
                ui->CSVButton->setEnabled(true);
                ui->MIDIButton->setEnabled(true);
                ui->progressBar->setValue(100);
            }
            else{
                ui->logBox->insertPlainText("\n[ERROR] Invalid XML File, check the file for errors.");
                ui->progressBar->setValue(0);
            }
        }
        catch(std::exception& e){
            string errMsg = "\n[ERROR]";
            errMsg.append(e.what());
            ui->logBox->insertPlainText(errMsg.c_str());
            ui->progressBar->setValue(0);
            return false;
        }
    }
    /* If the checks were succesful, the buttons will now be enabled.
      all conversions will be handled from there. */
    return true;
}

void mainWindow::on_MusicXMLButton_clicked()
{

    /* The music XML conversion button was clicked -> flowchart:
      IF MusicXML -> //exception//
      IF MEI -> parse MEI -> use MusicXMLGenerator.
      ELSE -> //Exception//
    */
    std::string mei = "MEI";

    if( std::strcmp(mei.c_str(),fileType.toStdString().c_str()) == 0){
        ui->logBox->clear();
        ui->progressBar->setValue(0);
        ui->logBox->insertPlainText("Starting Conversion...");

        MEIParser meiParser;
        meiParser.parse(filePath.toStdString());
        meiParser.mapData();

        ui->progressBar->setValue(50);
        ui->logBox->insertPlainText("\nXML file parsed.");

        MusicXMLGenerator musicXMLGenerator(meiParser.getPartList(),meiParser.getPart());

        ui->progressBar->setValue(75);

        QString savePath = QFileDialog::getSaveFileName(this,tr("Save Converted File"), "",tr("MusicXML File (*.xml);;All Files (*)"));

        try{
            musicXMLGenerator.generateMusicXML(savePath.toStdString());
        }

        catch(std::exception& e){
            string errMsg = "\n[ERROR]";
            errMsg.append(e.what());
            ui->logBox->insertPlainText(errMsg.c_str());
            ui->progressBar->setValue(0);
        }

        ui->progressBar->setValue(100);
        ui->logBox->insertPlainText("\nConversion complete.");
    }
}

void mainWindow::on_MEIButton_clicked()
{
    std::string mxl = "MusicXML";

    if(std::strcmp(mxl.c_str(),fileType.toStdString().c_str()) == 0){
        ui->logBox->clear();
        ui->progressBar->setValue(0);
        ui->logBox->insertPlainText("Starting Conversion...");

        MusicXMLParser musicXMLParser;
        musicXMLParser.parse(filePath.toStdString());

        ui->progressBar->setValue(50);
        ui->logBox->insertPlainText("\nXML file parsed.");

        MEIGenerator meiGenerator(musicXMLParser.getPartList(),musicXMLParser.getPart());

        ui->progressBar->setValue(75);

        QString savePath = QFileDialog::getSaveFileName(this,tr("Save Converted File"), "",tr("MEI File (*.xml);;All Files (*)"));

        try{
            meiGenerator.generateXML(savePath.toStdString());
        }

        catch(std::exception& e){
            string errMsg = "\n[ERROR]";
            errMsg.append(e.what());
            ui->logBox->insertPlainText(errMsg.c_str());
            ui->progressBar->setValue(0);
        }

        ui->progressBar->setValue(100);
        ui->logBox->insertPlainText("\nConversion complete.");


    }
}

void mainWindow::on_CSVButton_clicked()
{
    std::string mxl = "MusicXML";
    std::string mei = "MEI";

    if(std::strcmp(mxl.c_str(),fileType.toStdString().c_str()) == 0){
        ui->logBox->clear();
        ui->progressBar->setValue(0);
        ui->logBox->insertPlainText("Starting Conversion...");

        MusicXMLParser musicXMLParser;
        musicXMLParser.parse(filePath.toStdString());

        ui->progressBar->setValue(50);
        ui->logBox->insertPlainText("\nXML file parsed.");

        CSVGenerator csvGenerator(musicXMLParser.getPartList(), musicXMLParser.getPart());

        ui->progressBar->setValue(75);

        QString savePath = QFileDialog::getSaveFileName(this,tr("Save Converted File"), "",tr("Comma Seperated Value File (*.csv);;All Files (*)"));

        try{
           csvGenerator.generateCSV(savePath.toStdString());
        }

        catch(std::exception& e){
            string errMsg = "\n[ERROR]";
            errMsg.append(e.what());
            ui->logBox->insertPlainText(errMsg.c_str());
            ui->progressBar->setValue(0);
        }

        ui->progressBar->setValue(100);
        ui->logBox->insertPlainText("\nConversion complete.");
    }

}

void mainWindow::on_MIDIButton_clicked()
{
    cout << "You pressed the MIDI button!" << endl;
}

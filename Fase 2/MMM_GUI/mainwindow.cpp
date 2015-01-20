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
    ui(new Ui::mainWindow),
    savePathMidiFile(""),
    savePathMusicXMLFile(""),
    openTheMidiFile(false),
    openTheMusicXMLFile(false)
{
    ui->setupUi(this);
    //initally disable all Buttons.
    ui->MEIButton->setEnabled(false);
    ui->MusicXMLButton->setEnabled(false);
    ui->CSVButton->setEnabled(false);
    ui->MIDIButton->setEnabled(false);
    ui->MuseScoreButton->setEnabled(false);
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
    ui->MuseScoreButton->setEnabled(false);
    openTheMidiFile = false;
    openTheMusicXMLFile = false;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("Files (*.xml)"));
    filePath = fileName;

    /* update log and textBox + progressbar. */
    ui->logBox->insertPlainText("Selected file " + fileName + " for conversion.");
    ui->browseBox->setText(fileName);
    ui->progressBar->setValue(25);


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
        ui->logBox->insertPlainText("\n[OK] This is a MusicXML file.");
        fileType = "MusicXML";
        checkXML();
    }

    else if( !strcmp(docRoot_s.c_str() ,"<mei xmlns=\"http://www.music-encoding.org/ns/mei\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" meiversion=\"2013\">") ){
        ui->logBox->insertPlainText("\n[OK] This is an MEI file.");
        fileType = "MEI";
        checkXML();
    }
    else{
        ui->logBox->insertPlainText("\n[ERROR] Could not detect file format. Please ensure you have selected a MusicXML or MEI file.");
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

            ui->logBox->insertPlainText("\n[OK] Grammar loaded.");
            ui->progressBar->setValue(50);

            Formatter xmlFormatter(filePath.toStdString());

            ui->logBox->insertPlainText("\n[OK] Preformatted MusicXML input.");
            ui->progressBar->setValue(75);

            CYK mxlCYK(mxlGrammar);
            string formattedString = xmlFormatter.getFormatedVersion();

            ui->logBox->insertPlainText("\n[OK] Validating MusicXML file.");

            if(mxlCYK.testString(formattedString)){
                ui->logBox->insertPlainText("\n[OK] MusicXML file is valid, ready for conversion.");

                /* enable all buttons that do valid conversions for the file. */
                ui->MusicXMLButton->setEnabled(false);
                ui->MEIButton->setEnabled(true);
                ui->CSVButton->setEnabled(true);
                ui->MIDIButton->setEnabled(true);
                ui->progressBar->setValue(100);
                ui->MuseScoreButton->setEnabled(true); //Button enabled, filepath set to mxl file.

            }
            else{

                ui->logBox->insertPlainText("\n[ERROR] Invalid MusicXML file, check the file for errors.");
                ui->progressBar->setValue(0);

            }
            openTheMidiFile = false;
            openTheMusicXMLFile = true;
            savePathMusicXMLFile = filePath; /* the input for museScore is just the file we just opened. */
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

            ui->logBox->insertPlainText("\n[OK] Grammar loaded.");
            ui->progressBar->setValue(50);

            Formatter xmlFormatter(filePath.toStdString());

            ui->logBox->insertPlainText("\n[OK] Preformatted MEI input.");
            ui->progressBar->setValue(75);

            CYK meiCYK(meiGrammar);
            string formattedString = xmlFormatter.getFormatedVersion();

            if(meiCYK.testString(formattedString)){
                ui->logBox->insertPlainText("\n[OK] MEI file is valid, ready for conversion.");

                /* enable all buttons that do valid conversions for the file. */
                ui->MusicXMLButton->setEnabled(true);
                ui->MEIButton->setEnabled(false);
                ui->CSVButton->setEnabled(true);
                ui->MIDIButton->setEnabled(true);
                ui->progressBar->setValue(100);
                ui->MuseScoreButton->setEnabled(false); //disable open in museScore.
            }
            else{
                ui->logBox->insertPlainText("\n[ERROR] Invalid MEI file, check the file for errors.");
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
        ui->logBox->insertPlainText("Parsing the MEI file...");

        MEIParser meiParser;
        meiParser.parse(filePath.toStdString());
        meiParser.mapData();

        ui->progressBar->setValue(50);
        ui->logBox->insertPlainText("\nConverting to a MusicXML file...");

        MusicXMLGenerator musicXMLGenerator(meiParser.getPartList(),meiParser.getPart());

        ui->progressBar->setValue(75);

        savePathMusicXMLFile = QFileDialog::getSaveFileName(this,tr("Save Converted File"), "",tr("MusicXML File (*.xml);;All Files (*)"));

        try{
            musicXMLGenerator.generateMusicXML(savePathMusicXMLFile.toStdString());
        }

        catch(std::exception& e){
            string errMsg = "\n[ERROR]";
            errMsg.append(e.what());
            ui->logBox->insertPlainText(errMsg.c_str());
            ui->progressBar->setValue(0);
        }

        ui->progressBar->setValue(100);
        ui->logBox->insertPlainText("\nConversion complete.");
        ui->MuseScoreButton->setEnabled(true);
        openTheMidiFile = false;
        openTheMusicXMLFile = true;
    }
}

void mainWindow::on_MEIButton_clicked()
{
    std::string mxl = "MusicXML";

    if(std::strcmp(mxl.c_str(),fileType.toStdString().c_str()) == 0){
        ui->logBox->clear();
        ui->progressBar->setValue(0);
        ui->logBox->insertPlainText("Parsing the musicXML file...");

        MusicXMLParser musicXMLParser;
        musicXMLParser.parse(filePath.toStdString());

        ui->progressBar->setValue(50);
        ui->logBox->insertPlainText("\nCoverting to a Mei file...");

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
        ui->logBox->insertPlainText("Parsing the musicXML file...");

        MusicXMLParser musicXMLParser;
        musicXMLParser.parse(filePath.toStdString());


        ui->progressBar->setValue(50);
        ui->logBox->insertPlainText("\nConverting to a CSV file...");

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

    else if (std::strcmp(mei.c_str(),fileType.toStdString().c_str()) == 0)  {
        ui->logBox->clear();
        ui->progressBar->setValue(0);
        ui->logBox->insertPlainText("Parsing the MEI file...");

        MEIParser meiParser;
        meiParser.parse(filePath.toStdString());
        meiParser.mapData();

        ui->progressBar->setValue(50);
        ui->logBox->insertPlainText("\nConverting to a CSV file...");

        CSVGenerator csvGenerator(meiParser.getPartList(), meiParser.getPart());

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
    std::string mxl = "MusicXML";
    std::string mei = "MEI";

    if(std::strcmp(mxl.c_str(),fileType.toStdString().c_str()) == 0){
        ui->logBox->clear();
        ui->progressBar->setValue(0);
        ui->logBox->insertPlainText("Parsing the MusicXML file...");

        MusicXMLParser musicXMLParser;
        musicXMLParser.parse(filePath.toStdString());
        ui->progressBar->setValue(50);
        ui->logBox->insertPlainText("\nConverting to a CSV file...");

        CSVGenerator csvGenerator(musicXMLParser.getPartList(), musicXMLParser.getPart());

        ui->progressBar->setValue(75);

        QString savePathCSVFile = QFileDialog::getSaveFileName(this,tr("Save Converted File"), "",tr("Comma Seperated Value File (*.csv);;All Files (*)"));

        try{
           csvGenerator.generateCSV(savePathCSVFile.toStdString());

           ui->progressBar->setValue(75);
           ui->logBox->insertPlainText("\nConverting to a MIDI file...");

           savePathMidiFile = QFileDialog::getSaveFileName(this,tr("Save Converted File"), "",tr("Midi File (*.midi);;All Files (*.midi)"));

           std::string jarLocation = "../workingDirectory/csv2midi.jar";
           std::string command = "java -jar " + jarLocation + " " + savePathCSVFile.toStdString()+ " " + savePathMidiFile.toStdString();
           std::cout << command << std::endl;
           system(command.c_str());
        }

        catch(std::exception& e){
            string errMsg = "\n[ERROR]";
            errMsg.append(e.what());
            ui->logBox->insertPlainText(errMsg.c_str());
            ui->progressBar->setValue(0);
        }

        ui->progressBar->setValue(100);
        ui->logBox->insertPlainText("\nConversion complete.");
        ui->MuseScoreButton->setEnabled(true);

        openTheMidiFile = true;
        openTheMusicXMLFile = false;
    }

    else if (std::strcmp(mei.c_str(),fileType.toStdString().c_str()) == 0)  {
        ui->logBox->clear();
        ui->progressBar->setValue(0);
        ui->logBox->insertPlainText("Parsing the MEI file...");

        MEIParser meiParser;
        meiParser.parse(filePath.toStdString());
        meiParser.mapData();

        ui->progressBar->setValue(50);
        ui->logBox->insertPlainText("\nConverting to a CSV file...");

        CSVGenerator csvGenerator(meiParser.getPartList(), meiParser.getPart());

        ui->progressBar->setValue(75);

        QString savePathCSVFile = QFileDialog::getSaveFileName(this,tr("Save Converted File"), "",tr("Comma Seperated Value File (*.csv);;All Files (*)"));

        try{
           csvGenerator.generateCSV(savePathCSVFile.toStdString());

           ui->progressBar->setValue(75);
           ui->logBox->insertPlainText("\nConverting to a MIDI file...");

           savePathMidiFile = QFileDialog::getSaveFileName(this,tr("Save Converted File"), "",tr("Midi File (*.midi);;All Files (*.midi)"));


           std::string jarLocation = "../workingDirectory/csv2midi.jar";
           std::string command = "java -jar " + jarLocation + " " + savePathCSVFile.toStdString() + " " + savePathMidiFile.toStdString();
           system(command.c_str());
        }

        catch(std::exception& e){
            string errMsg = "\n[ERROR]";
            errMsg.append(e.what());
            ui->logBox->insertPlainText(errMsg.c_str());
            ui->progressBar->setValue(0);
        }

        ui->progressBar->setValue(100);
        ui->logBox->insertPlainText("\nConversion complete.");
        ui->MuseScoreButton->setEnabled(true);

        openTheMidiFile = true;
        openTheMusicXMLFile = false;
    }
}

void mainWindow::on_MuseScoreButton_clicked()
{
    try {
        /*
          Moved the system call into the statements.
          otherwise museScore can be started with no input. (which is an error).
         */
        std::string command = "musescore ";
        if (openTheMidiFile == true && openTheMusicXMLFile == false)   {
            std::cout << "opening midi file." << std::endl;
            command += savePathMidiFile.toStdString();
            system(command.c_str());
        }
        else if (openTheMidiFile == false && openTheMusicXMLFile == true )    {
            std::cout << "opening mxl file." << std::endl;
            command += savePathMusicXMLFile.toStdString();
            system(command.c_str());
        }
    }
    catch (std::exception& e)   {
        std::cout << e.what() << std::endl;
    }
}

void mainWindow::on_MuseScoreButton_released()
{
    //Keep this in, it makes sure Qt links the button functions
    //in a correct manner.
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "frontEndCode/tinyxml2.h"
#include <QFile>
#include <string>
#include <iostream>
#include "backEndCode/CFG.h"
#include "backEndCode/CNF.h"
#include "backEndCode/CYK.h"
#include "backEndCode/Formatter.h"
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
    ui->progressBar->setValue(0);
    ui->MEIButton->setEnabled(false);
    ui->MusicXMLButton->setEnabled(false);
    ui->CSVButton->setEnabled(false);
    ui->MIDIButton->setEnabled(false);

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("Files (*.*)"));
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

    QString docRoot = userFile.readLine();
    std::string docRoot_s = docRoot.toStdString();
    stripEndl(docRoot_s);

    userFile.close();

    if( !strcmp(docRoot_s.c_str(),"<score-partwise>") ){
        ui->logBox->insertPlainText("\n[OK] this is a musicXML file.");
        fileType = "MusicXML";
        checkXML();
    }

    else if( !strcmp(docRoot_s.c_str() ,"<music>") ){
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

    //first handle off MusicXML
    if( std::strcmp(mxl.c_str(),fileType.toStdString().c_str()) == 0){
        CFG mxlGrammar("MusicXML_Grammar.xml");
        CNF mxlCNF(&mxlGrammar);

        ui->logBox->insertPlainText("\n[OK] Grammar loaded");
        ui->progressBar->setValue(50);

        Formatter xmlFormatter(filePath.toStdString());

        ui->logBox->insertPlainText("\n[OK] preformatted XML input.");
        ui->progressBar->setValue(75);

        CYK mxlCYK(mxlGrammar);
        string formattedString = xmlFormatter.getFormatedVersion();

        if(mxlCYK.testString(formattedString)){
            ui->logBox->insertPlainText("\n[OK] XML File is valid, ready for conversion.");
        }
        else{
            ui->logBox->insertPlainText("\n[ERROR] Invalid XML File, check the file for errors.");
        }

    }

    if( std::strcmp(mei.c_str(),fileType.toStdString().c_str()) == 0){
        try{
            CFG meiGrammar("MEI_Grammar.xml");
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

                /* enable al buttons that do valid conversions for the file. */
                ui->MusicXMLButton->setEnabled(true);
                ui->MEIButton->setEnabled(true);
                ui->CSVButton->setEnabled(true);
                ui->MIDIButton->setEnabled(true);
                ui->progressBar->setValue(100);
            }
            else{
                ui->logBox->insertPlainText("\n[ERROR] Invalid XML File, check the file for errors.");
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
    return true;
}

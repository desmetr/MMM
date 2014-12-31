#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class mainWindow;
}

class mainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit mainWindow(QWidget *parent = 0);
    ~mainWindow();
    QString filePath;
    QString fileType;
    void stripEndl(std::string &s);
    bool checkXML();
    
private slots:
    void on_browseButton_clicked();

    void on_MusicXMLButton_clicked();

    void on_MEIButton_clicked();

    void on_CSVButton_clicked();

private:
    Ui::mainWindow *ui;
};

#endif // MAINWINDOW_H

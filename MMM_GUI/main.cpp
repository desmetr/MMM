#include "mainwindow.h"
#include <QApplication>
#include <QAbstractAnimation>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainWindow w;
    //create a fixed size windows
    w.setFixedHeight(467);
    w.setFixedWidth(852);
    w.setWindowTitle("Music Meets Machines");
    w.show();
    
    return a.exec();
}

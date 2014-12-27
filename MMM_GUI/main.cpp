#include "mainwindow.h"
#include <QApplication>
#include <QAbstractAnimation>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainWindow w;
    //create a fixed size 800,600 window.
    w.setFixedHeight(371);
    w.setFixedWidth(797);
    w.setWindowTitle("Music Meets Machines");
    w.show();
    
    return a.exec();
}

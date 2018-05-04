#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <vector>
#include <place.h>

void connectFileToClass(std::vector<Place *> &placeVector);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}



void updateDataFromFile()
{

}


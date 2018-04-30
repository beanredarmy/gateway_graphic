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
    std::vector<Place*> mPlaceVector;
    connectFileToClass(mPlaceVector);
    qDebug() << mPlaceVector[1]->name();

    return a.exec();
}

void connectFileToClass(std::vector<Place*> &placeVector)
{
    QDir mDir("/home/bean/gatewaydata");
    qDebug() << mDir.exists();
    foreach(QFileInfo mItm, mDir.entryInfoList())
    {
        if(mItm.fileName() != "." && mItm.fileName() != "..")
        {
            Place *newPlace =new Place(mItm.fileName());
            placeVector.push_back(newPlace);
        }
    }
}

void updateDataFromFile()
{

}


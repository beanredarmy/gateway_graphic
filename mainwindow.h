#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include "place.h"
#include "measureindex.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QChart *createLineChart(std::vector<std::vector<DataAndTime>> dateTimeVector, int valueMax, int valueCount) const;        //Tao bieu do duong thang
   // QChart *createSplineChart(DataTable dataTable, int valueMax, int valueCount) const;      //Tao bieu do duong cong
  //  QChart *createScatterChart(DataTable dataTable, int valueMax, int valueCount) const;     //Tao bieu do cham

 //   DataTable generateDataTable(std::vector<std::vector<DataAndTime>> dateTimeVector);

    void addDateMode(QComboBox *cmbBox_dateMode);
    void addPlace(QComboBox *cmbBox_place);
    void connectFileToClass(std::vector<Place*> &placeVector);

private:
    std::vector<Place*> m_PlaceVector;
    Ui::MainWindow *ui;
    int m_listCount;
//    DataTable m_dataTable_temp;     //Bang du lieu nhiet do
//    DataTable m_dataTable_humi;     //Bang du lieu do am
//    DataTable m_dataTable_press;    //Bang du lieu ap suat

};

#endif // MAINWINDOW_H

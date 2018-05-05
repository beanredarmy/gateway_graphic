#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    QChart *createSplineChart(std::vector<std::vector<DataAndTime>> dateTimeVector, int valueMax, int valueCount) const;      //Tao bieu do duong cong
    QChart *createScatterChart(std::vector<std::vector<DataAndTime>> dateTimeVector, int valueMax, int valueCount) const;     //Tao bieu do cham

    void addDateMode(QComboBox *cmbBox_dateMode);
    void addPlace(QComboBox *cmbBox_place);
    void connectFileToClass(std::vector<Place*> &placeVector);

private:
    std::vector<Place*> m_placeVector;
    Ui::MainWindow *ui;
    MeasureIndex *m_tempIndex;
    MeasureIndex *m_humiIndex;
    MeasureIndex *m_pressIndex;

};

#endif // MAINWINDOW_H

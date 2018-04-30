#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>

QT_BEGIN_NAMESPACE
class QComboBox;
class QCheckBox;
class Ui_ThemeWidgetForm;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QChart *createLineChart(DataTable dataTable) const;        //Tao bieu do duong thang
    QChart *createSplineChart(DataTable dataTable) const;      //Tao bieu do duong cong
    QChart *createScatterChart(DataTable dataTable) const;     //Tao bieu do cham

private:
    Ui::MainWindow *ui;
    int m_listCount;
    DataTable m_dataTable_temp;     //Bang du lieu nhiet do
    DataTable m_dataTable_humi;     //Bang du lieu do am
    DataTable m_dataTable_press;    //Bang du lieu ap suat

};

#endif // MAINWINDOW_H

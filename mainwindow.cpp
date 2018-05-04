#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    addDateMode(ui->cmbBox_temp_dateMode);
    addDateMode(ui->cmbBox_humi_dateMode);


    connectFileToClass(m_PlaceVector);
    addPlace(ui->cmbBox_humi_place);
    addPlace(ui->cmbBox_temp_place);


    std::vector<DataAndTime> sample;
    sample.push_back(DataAndTime(1.0,1.0));
    sample.push_back(DataAndTime(2.0,1.5));
    sample.push_back(DataAndTime(3.5,2.5));
    sample.push_back(DataAndTime(4.0,3.0));
    sample.push_back(DataAndTime(3.0,4.5));
    sample.push_back(DataAndTime(3.5,5.5));
    sample.push_back(DataAndTime(7.0,6.0));
    sample.push_back(DataAndTime(6.0,7.5));
    sample.push_back(DataAndTime(8.0,9.5));
    std::vector<DataAndTime> sample2;
    sample2.push_back(DataAndTime(3.0,0.5));
    sample2.push_back(DataAndTime(1.0,2.0));
    sample2.push_back(DataAndTime(5.5,2.2));
    sample2.push_back(DataAndTime(7.0,3.0));
    sample2.push_back(DataAndTime(6.0,4.0));
    sample2.push_back(DataAndTime(4.5,5.0));
    sample2.push_back(DataAndTime(8.0,6.5));
    sample2.push_back(DataAndTime(6.0,7.0));
    sample2.push_back(DataAndTime(8.0,10));
    std::vector<std::vector<DataAndTime>> asample;
    asample.push_back(sample);
    asample.push_back(sample2);


   // Place *vietnam = new Place("Viet Nam");
    //vietnam->setHour_temp(sample);
    QChartView *chartView;
    chartView = new QChartView(createLineChart(asample,10,10));
    chartView->setRenderHint(QPainter::Antialiasing, true);
    ui->gridLayout_graph_temp->addWidget(chartView);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::addDateMode(QComboBox *cmbBox_dateMode)
{
    cmbBox_dateMode->addItem("Giờ");
    cmbBox_dateMode->addItem("Ngày");
    cmbBox_dateMode->addItem("Tháng");
    cmbBox_dateMode->addItem("Năm");
}

void MainWindow::addPlace(QComboBox *cmbBox_place)
{
    for (std::vector<Place*>::iterator it = m_PlaceVector.begin(); it != m_PlaceVector.end(); it++)
    {
        cmbBox_place->addItem((*it)->name());
    }
}

void MainWindow::connectFileToClass(std::vector<Place *> &placeVector)
{
    QDir mDir("/home/bean/gatewaydata");
    foreach(QFileInfo mItm, mDir.entryInfoList())
    {
        if(mItm.fileName() != "." && mItm.fileName() != "..")
        {
            Place *newPlace =new Place(mItm.fileName());
            placeVector.push_back(newPlace);
        }
    }
}

QChart *MainWindow::createLineChart(std::vector<std::vector<DataAndTime>> dateTimeVector, int valueMax, int valueCount) const
{
    //![1]
    QChart *chart = new QChart();
    chart->setTitle("Line chart");
    //![1]

    //![2]
    QString name("Series ");
    int nameIndex = 0;
    for (std::vector<std::vector<DataAndTime>>::iterator it = dateTimeVector.begin(); it != dateTimeVector.end(); it++)  {
        QScatterSeries *series2 = new QScatterSeries(chart);
        series2->setMarkerSize(5.0);
        QLineSeries *series = new QLineSeries(chart);
        for (std::vector<DataAndTime>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++)
        {
            series->append((*it2).second, (*it2).first);
            series2->append((*it2).second, (*it2).first);
        }
        series->setName(name + QString::number(nameIndex));
        series2->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(series);
        chart->addSeries(series2);
    }
    //![2]

    //![3]
    chart->createDefaultAxes();
    chart->axisX()->setRange(0, valueMax);
    chart->axisY()->setRange(0, valueCount);
    //![3]
    //![4]
    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisY())->setLabelFormat("%.1f  ");
    //![4]

    return chart;
}


/* DataTable MainWindow::generateDataTable(std::vector<std::vector<DataAndTime>> dateTimeVector)
{
    DataTable dataTable;

    for (std::vector<std::vector<DataAndTime>>::iterator it = dateTimeVector.begin(); it != dateTimeVector.end(); it++) {
        DataList dataList;
        for (std::vector<DataAndTime>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++) {
            QPointF value((*it2).second, (*it2).first);
            QString label = "Slice ";// + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        dataTable << dataList;
    }

    return dataTable;
}

QChart *MainWindow::createSplineChart(DataTable dataTable, int valueMax, int valueCount) const
{
    QChart *chart = new QChart();
    chart->setTitle("Spline chart");
    QString name("Series ");
    int nameIndex = 0;
    for (const DataList &list : dataTable) {
        QSplineSeries *series = new QSplineSeries(chart);
        for (const Data &data : list)
            series->append(data.first);
        series->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(series);
    }

    chart->createDefaultAxes();
    chart->axisX()->setRange(0, valueMax);
    chart->axisY()->setRange(0, valueCount);
    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisY())->setLabelFormat("%.1f  ");

    return chart;
}

QChart *MainWindow::createScatterChart(DataTable dataTable, int valueMax, int valueCount) const
{
    // scatter chart
    QChart *chart = new QChart();
    chart->setTitle("Scatter chart");
    QString name("Series ");
    int nameIndex = 0;
    for (const DataList &list : dataTable) {
        QScatterSeries *series = new QScatterSeries(chart);
        for (const Data &data : list)
            series->append(data.first);
        series->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(series);
    }

    chart->createDefaultAxes();
    chart->axisX()->setRange(0, valueMax);
    chart->axisY()->setRange(0, valueCount);
    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisY())->setLabelFormat("%.1f  ");

    return chart;
}
*/

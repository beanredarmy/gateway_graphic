#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connectFileToClass(m_placeVector);

    std::vector<DataAndTime> sample;
    sample.push_back(DataAndTime(4.0,1.0));
    sample.push_back(DataAndTime(3.0,1.5));
    sample.push_back(DataAndTime(2.5,2.5));
    sample.push_back(DataAndTime(1.0,3.0));
    sample.push_back(DataAndTime(4.0,4.5));
    sample.push_back(DataAndTime(5.5,5.5));
    sample.push_back(DataAndTime(6.0,6.0));
    sample.push_back(DataAndTime(8.0,7.5));
    sample.push_back(DataAndTime(9.0,9.5));
    std::vector<DataAndTime> sample2;
    sample2.push_back(DataAndTime(6.0,0.5));
    sample2.push_back(DataAndTime(2.0,2.0));
    sample2.push_back(DataAndTime(3.5,2.2));
    sample2.push_back(DataAndTime(4.0,3.0));
    sample2.push_back(DataAndTime(6.0,4.0));
    sample2.push_back(DataAndTime(6.5,5.0));
    sample2.push_back(DataAndTime(8.0,6.5));
    sample2.push_back(DataAndTime(8.0,7.0));
    sample2.push_back(DataAndTime(7.0,10));
    std::vector<std::vector<DataAndTime>> asample;
    asample.push_back(sample);
    asample.push_back(sample2);


    QChartView *chartView;
    chartView = new QChartView(createLineChart(asample,10,10));
    chartView->setRenderHint(QPainter::Antialiasing, true);
    ui->gridLayout_graph->addWidget(chartView);




    createAddTabButton();

    ui->tabWidget->tabBar()->setElideMode(Qt::TextElideMode::ElideRight);
    ui->tabWidget->setStyleSheet("QTabBar::tab { height: 40px; width: 150px; }");
    connect(m_addTabButton, SIGNAL (clicked()),this, SLOT (createTab()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_addTabButton;

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
    for (std::vector<Place*>::iterator it = m_placeVector.begin(); it != m_placeVector.end(); it++)
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

QChart *MainWindow::createSplineChart(std::vector<std::vector<DataAndTime>> dateTimeVector, int valueMax, int valueCount) const
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
        QSplineSeries *series = new QSplineSeries(chart);
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

QChart *MainWindow::createScatterChart(std::vector<std::vector<DataAndTime>> dateTimeVector, int valueMax, int valueCount) const
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
        series2->setMarkerSize(10.0);
        for (std::vector<DataAndTime>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++)
        {
            series2->append((*it2).second, (*it2).first);
        }
        series2->setName(name + QString::number(nameIndex));
        nameIndex++;
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

void MainWindow::createTab()
{
    DetailWidget *detailWidget = new DetailWidget();
    detailWidget->m_order = m_dtWidgetVector.size();
    m_dtWidgetVector.push_back(detailWidget);
    ui->tabWidget->addTab(detailWidget,QString("CHI TIẾT %1").arg(detailWidget->m_order+2));

    detailWidget->pushBtn_exitTab = new QPushButton("x");
    detailWidget->pushBtn_exitTab->setMaximumSize(QSize(20, 20));
    ui->tabWidget->tabBar()->setTabButton(1+m_dtWidgetVector.size(),QTabBar::RightSide, detailWidget->pushBtn_exitTab);
   // connect(detailWidget->pushBtn_exitTab, SIGNAL (clicked()),this, SLOT (removeTab()));
    //Can tiep tuc o day

}

void MainWindow::removeTab(int tabOrder)
{

}


void MainWindow::createAddTabButton()
{
    QWidget* pTabCornerWidget = new QWidget(this);
    m_addTabButton = new QPushButton("+",pTabCornerWidget);
    m_addTabButton->setMaximumSize(QSize(25, 25));

    QHBoxLayout* pHLayout = new QHBoxLayout(pTabCornerWidget);
    pHLayout->addWidget(m_addTabButton);
    ui->tabWidget->setCornerWidget(pTabCornerWidget, Qt::TopRightCorner);
}



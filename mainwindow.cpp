#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connectFileToClass(m_placeVector);

    createAddTabButton();
    ui->tabWidget->setTabsClosable(true);
    ui->tabWidget->tabBar()->setElideMode(Qt::TextElideMode::ElideRight);
    ui->tabWidget->setStyleSheet("QTabBar::tab { height: 40px; width: 150px; }");
    connect(m_addTabButton, SIGNAL (clicked()),this, SLOT (createTab()));
    connect(ui->tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(removeTab(int)));

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
    DetailWidget *detailWidget = new DetailWidget(this);
    //detailWidget->m_order = m_dtWidgetVector.size();
    //m_dtWidgetVector.push_back(detailWidget);
   // ui->tabWidget->addTab(detailWidget,QString("CHI TIẾT %1").arg(detailWidget->m_order+2));
    detailWidget->m_order = ui->tabWidget->count();
    ui->tabWidget->addTab(detailWidget,QString("CHI TIẾT %1").arg(detailWidget->m_order));
    ui->tabWidget->setCurrentIndex(detailWidget->m_order);
}

void MainWindow::removeTab(int tabOrder)
{
    if(tabOrder > 1)
    {
        delete ui->tabWidget->widget(tabOrder);
      //  m_dtWidgetVector.erase(m_dtWidgetVector.begin() + tabOrder-2);
        qDebug() << m_dtWidgetVector.size();
    } else qDebug() << "Khong the dong tab nay";

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



#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QToolButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectFileToClass();
    createAddTabButton();
    furtherSetup();
    ui->tabWidget->removeTab(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Scan all device and add to deviceList
void MainWindow::connectFileToClass()
{
    QDir mDir("/home/bean/gatewaydata");
    DetailWidget::m_deviceList << "Chọn";
    for(int i=0; i<mDir.entryInfoList().count(); ++i )
    {
        if(mDir.entryInfoList()[i].fileName() != "." && mDir.entryInfoList()[i].fileName() != ".."  && mDir.entryInfoList()[i].isDir())
        {
            DetailWidget::m_deviceList << mDir.entryInfoList()[i].fileName();
        }
    }
}

//another setup here
void MainWindow::furtherSetup()
{
    ui->tabWidget->setTabsClosable(true);
    ui->tabWidget->tabBar()->setElideMode(Qt::TextElideMode::ElideRight);
    ui->tabWidget->setStyleSheet("QTabBar::tab { height: 30px}");

    QChartView *chartView = new QChartView(this);
    chartView->setRenderHint(QPainter::Antialiasing, true);
    ui->gridLayout_graph->addWidget(chartView);

    //create a new tab when click to "addtab" button
    connect(m_addTabButton, SIGNAL (clicked()),this, SLOT (createTab()));
    //remove a tab when click to its "close" button
    connect(ui->tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(removeTab(int)));
    //add devices list to comboBox in overview
    ui->cmbBox_ov_device->addItems(DetailWidget::m_deviceList);
    //change overview data when change device in combobox overview
    connect(ui->cmbBox_ov_device,SIGNAL(currentIndexChanged(QString)),this,SLOT(showOverviewData(QString)));
}

void MainWindow::showMessToStatusBar(QString message)
{
    ui->statusBar->showMessage(message,2000);
}

void MainWindow::showOverviewData(QString deviceName)
{
    if(ui->cmbBox_ov_device->currentIndex() != 0)
    {
        //create specific data of today
        SpecificData *todayData = new SpecificData(deviceName,QDate::currentDate());

        Data_Time temporaryData_Table = todayData->getLastValue(0);
        ui->lcdN_ov_curHumiSoil->display(temporaryData_Table.first);
        ui->lcdN_ov_curHumiSoil->setToolTip(QString("T.Gian: %1h%2p").arg(round(temporaryData_Table.second)).arg((int)((temporaryData_Table.second-(int)temporaryData_Table.second)*60)));

        temporaryData_Table = todayData->getLastValue(1);
        ui->lcdN_ov_curHumiEnvi->display(temporaryData_Table.first);
        ui->lcdN_ov_curHumiEnvi->setToolTip(QString("T.Gian: %1h%2p").arg(round(temporaryData_Table.second)).arg((int)((temporaryData_Table.second-(int)temporaryData_Table.second)*60)));

        temporaryData_Table = todayData->getLastValue(2);
        ui->lcdN_ov_curTempSoil->display(temporaryData_Table.first);
        ui->lcdN_ov_curTempSoil->setToolTip(QString("T.Gian: %1h%2p").arg(round(temporaryData_Table.second)).arg((int)((temporaryData_Table.second-(int)temporaryData_Table.second)*60)));

        temporaryData_Table = todayData->getLastValue(3);
        ui->lcdN_ov_curTempEnvi->display(temporaryData_Table.first);
        ui->lcdN_ov_curTempEnvi->setToolTip(QString("T.Gian: %1h%2p").arg(round(temporaryData_Table.second)).arg((int)((temporaryData_Table.second-(int)temporaryData_Table.second)*60)));


        ui->lcdN_ov_aveHumiSoil->display(todayData->getAverageValue(0));
        ui->lcdN_ov_aveHumiEnvi->display(todayData->getAverageValue(1));
        ui->lcdN_ov_aveTempSoil->display(todayData->getAverageValue(2));
        ui->lcdN_ov_aveTempEnvi->display(todayData->getAverageValue(3));

        temporaryData_Table = todayData->getMinValue(0);
        ui->lcdN_ov_minHumiSoil->display(temporaryData_Table.first);
        ui->lcdN_ov_minHumiSoil->setToolTip(QString("T.Gian: %1h%2p").arg(round(temporaryData_Table.second)).arg((int)((temporaryData_Table.second-(int)temporaryData_Table.second)*60)));

        temporaryData_Table = todayData->getMinValue(1);
        ui->lcdN_ov_minHumiEnvi->display(temporaryData_Table.first);
        ui->lcdN_ov_minHumiEnvi->setToolTip(QString("T.Gian: %1h%2p").arg(round(temporaryData_Table.second)).arg((int)((temporaryData_Table.second-(int)temporaryData_Table.second)*60)));

        temporaryData_Table = todayData->getMinValue(2);
        ui->lcdN_ov_minTempSoil->display(temporaryData_Table.first);
        ui->lcdN_ov_minTempSoil->setToolTip(QString("T.Gian: %1h%2p").arg(round(temporaryData_Table.second)).arg((int)((temporaryData_Table.second-(int)temporaryData_Table.second)*60)));

        temporaryData_Table = todayData->getMinValue(3);
        ui->lcdN_ov_minTempEnvi->display(temporaryData_Table.first);
        ui->lcdN_ov_minTempEnvi->setToolTip(QString("T.Gian: %1h%2p").arg(round(temporaryData_Table.second)).arg((int)((temporaryData_Table.second-(int)temporaryData_Table.second)*60)));

        temporaryData_Table = todayData->getMaxValue(0);
        ui->lcdN_ov_maxHumiSoil->display(temporaryData_Table.first);
        ui->lcdN_ov_maxHumiSoil->setToolTip(QString("T.Gian: %1h%2p").arg(round(temporaryData_Table.second)).arg((int)((temporaryData_Table.second-(int)temporaryData_Table.second)*60)));

        temporaryData_Table = todayData->getMaxValue(1);
        ui->lcdN_ov_maxHumiEnvi->display(temporaryData_Table.first);
        ui->lcdN_ov_maxHumiEnvi->setToolTip(QString("T.Gian: %1h%2p").arg(round(temporaryData_Table.second)).arg((int)((temporaryData_Table.second-(int)temporaryData_Table.second)*60)));

        temporaryData_Table = todayData->getMaxValue(2);
        ui->lcdN_ov_maxTempSoil->display(temporaryData_Table.first);
        ui->lcdN_ov_maxTempSoil->setToolTip(QString("T.Gian: %1h%2p").arg(round(temporaryData_Table.second)).arg((int)((temporaryData_Table.second-(int)temporaryData_Table.second)*60)));

        temporaryData_Table = todayData->getMaxValue(3);
        ui->lcdN_ov_maxTempEnvi->display(temporaryData_Table.first);
        ui->lcdN_ov_maxTempEnvi->setToolTip(QString("T.Gian: %1h%2p").arg(round(temporaryData_Table.second)).arg((int)((temporaryData_Table.second-(int)temporaryData_Table.second)*60)));


        //release pointer
        delete todayData;
    } else showMessToStatusBar(QString("Hãy chọn thiết bị"));

}

//Create a tab
void MainWindow::createTab()
{
    //Create a tab and add to tabWidget
    DetailWidget *detailWidget = new DetailWidget(this);
    detailWidget->m_order = ui->tabWidget->count();
    ui->tabWidget->addTab(detailWidget,QString("CHI TIẾT"));
    ui->tabWidget->setCurrentIndex(detailWidget->m_order);
    //change tab title when change value of device combobox
    connect(detailWidget->cmbBox_device, SIGNAL (currentIndexChanged(QString)),this, SLOT (changeTabTitle(QString)));
    connect(detailWidget, SIGNAL(sendMessToStatusBar(QString)), this, SLOT(showMessToStatusBar(QString)));
}

//Change tab's title based on selected device
void MainWindow::changeTabTitle(QString titleName)
{
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),titleName);
}

//Remove a tab
void MainWindow::removeTab(int tabOrder)
{
    if(tabOrder > 1) // Close a tab except 2 first tab
    {
        delete ui->tabWidget->widget(tabOrder);
    } else showMessToStatusBar("Không thể đóng tab này");

}

//Create "Add Tab" Button
void MainWindow::createAddTabButton()
{

       QWidget* pTabCornerWidget = new QWidget(this);
       m_addTabButton = new QPushButton("+",pTabCornerWidget);
       m_addTabButton->setMaximumSize(QSize(20, 20));
       m_addTabButton->setToolTip("Thêm tab");

       QHBoxLayout* pHLayout = new QHBoxLayout(pTabCornerWidget);
       pHLayout->addWidget(m_addTabButton);
       pHLayout->setContentsMargins(2,2,2,2);
       ui->tabWidget->setCornerWidget(pTabCornerWidget, Qt::TopRightCorner);

}



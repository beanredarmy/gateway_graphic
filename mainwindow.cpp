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
    } else ui->statusBar->showMessage("Không thể đóng tab này",2000);

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



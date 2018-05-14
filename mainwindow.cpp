#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connectFileToClass();
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

void MainWindow::connectFileToClass()
{
    QDir mDir("/home/bean/gatewaydata");
    DetailWidget::m_deviceList << "Chọn thiết bị";
    foreach(QFileInfo mItm, mDir.entryInfoList())
    {
        if(mItm.fileName() != "." && mItm.fileName() != "..")
        {
            DetailWidget::m_deviceList << mItm.fileName();
        }
    }
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
    connect(detailWidget->cmbBox_device, SIGNAL (currentIndexChanged(QString)),this, SLOT (changeTabTitle(QString)));
}

void MainWindow::changeTabTitle(QString titleName)
{
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),titleName);
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



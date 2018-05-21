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

    ui->tabWidget->setTabsClosable(true);
    ui->tabWidget->tabBar()->setElideMode(Qt::TextElideMode::ElideRight);
    ui->tabWidget->setStyleSheet("QTabBar::tab { height: 30px}");

    QChartView *chartView = new QChartView(this);
    chartView->setRenderHint(QPainter::Antialiasing, true);
    ui->gridLayout_graph->addWidget(chartView);

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
    DetailWidget::m_deviceList << "Chọn";
    for(int i=0; i<mDir.entryInfoList().count(); ++i )
    {
        if(mDir.entryInfoList()[i].fileName() != "." && mDir.entryInfoList()[i].fileName() != ".."  && mDir.entryInfoList()[i].isDir())
        {
            DetailWidget::m_deviceList << mDir.entryInfoList()[i].fileName();
        }
    }
}

void MainWindow::createTab()
{
    DetailWidget *detailWidget = new DetailWidget(this);
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
        qDebug() << m_dtWidgetVector.size();
    } else ui->statusBar->showMessage("Không thể đóng tab này",2000);

}

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



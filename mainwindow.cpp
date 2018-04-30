#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->cmbBox_temp_dateMode->addItem("Giờ");
    ui->cmbBox_temp_dateMode->addItem("Ngày");
    ui->cmbBox_temp_dateMode->addItem("Tháng");
    ui->cmbBox_temp_dateMode->addItem("Năm");


}

MainWindow::~MainWindow()
{
    delete ui;
}

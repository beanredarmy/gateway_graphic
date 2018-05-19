#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "detailwidget.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void createAddTabButton();
    void connectFileToClass();


public slots:
    void removeTab(int tabOrder);
    void createTab();
    void changeTabTitle(QString titleName);
private:
    std::vector<DetailWidget*> m_dtWidgetVector;
    Ui::MainWindow *ui;
    QPushButton* m_addTabButton;
};

#endif // MAINWINDOW_H

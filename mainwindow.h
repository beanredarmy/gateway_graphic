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
    void furtherSetup();

public slots:
    void showMessToStatusBar(QString message);
    void removeTab(int tabOrder);
    void showOverviewData(QString deviceName);
    void updateOverviewData();
    void createTab();
    void changeTabTitle(QString titleName);
private slots:
    void on_lineEdit_dataPath_editingFinished();


private:
    Ui::MainWindow *ui;
    QPushButton* m_addTabButton;
    QTimer *m_timer;
};

#endif // MAINWINDOW_H

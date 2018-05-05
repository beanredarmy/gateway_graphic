#ifndef DETAILWIDGET_H
#define DETAILWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QFrame>
#include <QLabel>
#include <QLCDNumber>
#include <QGroupBox>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QPushButton>
#include <QApplication>


class DetailWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DetailWidget(QWidget *parent = nullptr);

signals:

public slots:

private:
    void createMenuOption();
    void creatDataArea();

    QLCDNumber *currentValueLCD;


};

#endif // DETAILWIDGET_H

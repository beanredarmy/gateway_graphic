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
    QGridLayout *gridLayout_2;
    QFrame *frame_option;
    QGridLayout *gridLayout_6;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_16;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *cmbBox_index;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_7;
    QComboBox *cmbBox_place;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_13;
    QComboBox *cmbBox_dateMode;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_8;
    QDateTimeEdit *dateEdit_date;
    QPushButton *pushButton_OK;
    QPushButton *pushButton_viewNow;
    QFrame *line;
    QLabel *label_15;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_19;
    QComboBox *cmbBox_place2;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_17;
    QDateTimeEdit *dateEdit_date2;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_20;
    QComboBox *cmbBox_place3;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_18;
    QDateTimeEdit *dateEdit_date3;
    QHBoxLayout *horizontalLayout_17;
    QPushButton *pushBtn_compare;
    QPushButton *pushBtn_notCompare;
    QFrame *line_2;
    QLabel *label_21;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_22;
    QSlider *horizontalSlider;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_14;
    QComboBox *cmbBox_graphMode;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_23;
    QComboBox *cmbBox_theme;
    QSpacerItem *verticalSpacer;
    QFrame *frame_content;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_11;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_9;
    QLCDNumber *lcdNumber_curValue;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_10;
    QLCDNumber *lcdNumber_aveValue;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_11;
    QLCDNumber *lcdNumber_minValue;
    QLabel *label_12;
    QLCDNumber *lcdNumber_maxValue;
    QGridLayout *gridLayout_graph;


};

#endif // DETAILWIDGET_H

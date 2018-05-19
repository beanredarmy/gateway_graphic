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
#include <QCheckBox>
#include <QDebug>
#include <QCategoryAxis>
#include <QtWidgets/QGraphicsTextItem>
#include <QGraphicsLayout>
#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QChartView>
#include <QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtCore/QRandomGenerator>
#include <QtCharts/QBarCategoryAxis>
#include <QtWidgets/QApplication>
#include <QtCharts/QValueAxis>
#include <QDir>
#include "specificdata.h"
#include "callout.h"


class DetailWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DetailWidget(QWidget *parent = nullptr);
    ~DetailWidget();

    void setupWidgets();
    void setupOptions();
    void setupFontChart(QChart *chart) const;
    QChart *createLineChart(std::vector<SpecificData*> specDataVector, int valueMax, int valueCount) const;        //Tao bieu do duong thang

    QChart *createSplineChart(std::vector<std::vector<Data_Time>> dateTimeVector, int valueMax, int valueCount) const;      //Tao bieu do duong cong
    QChart *createScatterChart(std::vector<std::vector<Data_Time>> dateTimeVector, int valueMax, int valueCount) const;     //Tao bieu do cham

signals:

public slots:
    void drawChart();
    void viewFileData();
    void showPresentData();
    void compareData();
    void hideComparison();
    void tooltip(QPointF point, bool state);
    void changeTheme(int index);
private:
    QChartView *m_chartView;
    Callout *m_tooltip;
    QChart::ChartTheme m_charTheme;

public:
    static QStringList  m_deviceList;
    int m_order;

    QGridLayout *gridLayout_2;
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
    QFrame *frame_option;
    QGridLayout *gridLayout_6;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_16;
    QCheckBox *checkBox_humi_soil;
    QCheckBox *checkBox_humi_envi;
    QCheckBox *checkBox_temp_soil;
    QCheckBox *checkBox_temp_envi;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_7;
    QComboBox *cmbBox_device;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_13;
    QComboBox *cmbBox_dateMode;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_8;
    QDateEdit *dateEdit_device1;
    QPushButton *pushButton_OK;
    QHBoxLayout *horizontalLayout_19;
    QPushButton *pushButton_viewNow;
    QPushButton *pushButton_showData;
    QFrame *line;
    QLabel *label_15;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_19;
    QComboBox *cmbBox_device2;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_17;
    QDateEdit *dateEdit_device2;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_20;
    QComboBox *cmbBox_device3;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_18;
    QDateEdit *dateEdit_device3;
    QHBoxLayout *horizontalLayout_17;
    QPushButton *pushBtn_compare;
    QPushButton *pushBtn_notCompare;
    QFrame *line_2;
    QLabel *label_21;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_14;
    QComboBox *cmbBox_graphMode;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_23;
    QComboBox *cmbBox_theme;
    QSpacerItem *verticalSpacer;
};

#endif // DETAILWIDGET_H

#ifndef MEASUREINDEX_H
#define MEASUREINDEX_H
#include <place.h>
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

QT_BEGIN_NAMESPACE
class QComboBox;
class QCheckBox;
class Ui_ThemeWidgetForm;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

//typedef QPair<QPointF, QString> Data;
//typedef QList<Data> DataList;
//typedef QList<DataList> DataTable;

QT_CHARTS_USE_NAMESPACE

enum DateMode{
    HOUR, DAY, MONTH, YEAR
};

enum GraphMode{

};

enum Theme{

};

class MeasureIndex
{
public:
    MeasureIndex();
    ~MeasureIndex();


private:
    Place *m_place;
    DateMode m_datemode;
    QDateTime *m_datetime;

    Place *m_place2;
    Place *m_place3;
    QDateTime *m_datetime2;
    QDateTime *m_datetime3;

    Theme m_theme;
    GraphMode m_graphmode;





};

#endif // MEASUREINDEX_H

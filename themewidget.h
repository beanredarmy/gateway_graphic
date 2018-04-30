#ifndef THEMEWIDGET_H
#define THEMEWIDGET_H

//#include <QWidget>
#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>

QT_BEGIN_NAMESPACE
class QComboBox;
class QCheckBox;
class Ui_ThemeWidgetForm;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;

QT_CHARTS_USE_NAMESPACE

class themewidget : public QWidget
{
    Q_OBJECT
public:
    explicit themewidget(QWidget *parent = 0);
    ~themewidget();
    QChart *createAreaChart() const;
    QChart *createBarChart(int valueCount) const;
    QChart *createPieChart() const;
    QChart *createLineChart() const;
    QChart *createSplineChart() const;
    QChart *createScatterChart() const;
    void connectSignals();
private:
    Ui_ThemeWidgetForm *m_ui;


signals:

public slots:
};

#endif // THEMEWIDGET_H

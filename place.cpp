#include "place.h"

Place::Place()
{

}

Place::Place(const QString &name)
{
    m_name = name;
}

float Place::curTemperature() const
{
    return m_curTemperature;
}

void Place::setCurTemperature(float curTemperature)
{
    m_curTemperature = curTemperature;
}

float Place::curHumidity() const
{
    return m_curHumidity;
}

void Place::setCurHumidity(float curHumidity)
{
    m_curHumidity = curHumidity;
}

float Place::curPressure() const
{
    return m_curPressure;
}

void Place::setCurPressure(float curPressure)
{
    m_curPressure = curPressure;
}

DataTable Place::generateData(std::vector<float> dataFromVector)
{
    DataTable dataTable;

    /*for (int i(0); i < listCount; i++) {
        DataList dataList;
        qreal yValue(0);
        for (int j(0); j < valueCount; j++) {
            yValue = yValue + QRandomGenerator::global()->bounded(valueMax / (qreal) valueCount);
            QPointF value((j + QRandomGenerator::global()->generateDouble()) * ((qreal) m_valueMax / (qreal) valueCount),
                          yValue);
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        dataTable << dataList;
    }
*/
    return dataTable;
}

QString Place::name() const
{
    return m_name;
}

void Place::setName(const QString &name)
{
    m_name = name;
}

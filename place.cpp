#include "place.h"
#include <QChartView>
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



std::vector<DataAndTime> Place::hour_temp() const
{
    return m_hour_temp;
}

void Place::setHour_temp(const std::vector<DataAndTime> &hour_temp)
{
    m_hour_temp = hour_temp;
}


QString Place::name() const
{
    return m_name;
}

void Place::setName(const QString &name)
{
    m_name = name;
}

#ifndef SPECIFICDATA_H
#define SPECIFICDATA_H
#include<QtCore>

typedef QPair<float ,float> Data_Time;

class SpecificData
{
public:
    SpecificData(int dataType, QString deviceName, int timeMode, QDate date);
    SpecificData(QString deviceName, QDate date);
    ~SpecificData();


    QString dataTypeName() const;
    void setDataTypeName(const QString &dataTypeName);

    QString deviceName() const;
    void setDeviceName(const QString &deviceName);

    std::vector<Data_Time> dataTimeVector() const;
    void setDataTimeVector(const std::vector<Data_Time> &dataTimeVector);

    int dataType() const;
    void setDataType(int dataType);

    std::vector<Data_Time> getDataTimeVector(int dataType, int timeMode);
    Data_Time getLastValue(int dataType);
    float getAverageValue(int dataType);
    Data_Time getMinValue(int dataType);
    Data_Time getMaxValue(int dataType);
    static QString m_dataPath;
private:

    int m_dataType;
    QString m_dataTypeName;
    QString m_deviceName;
    int m_timeMode;
    int m_day;
    int m_month;
    int m_year;
    std::vector<Data_Time> m_dataTimeVector;

};

#endif // SPECIFICDATA_H

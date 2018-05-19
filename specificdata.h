#ifndef SPECIFICDATA_H
#define SPECIFICDATA_H
#include<QtCore>

typedef QPair<float ,float> Data_Time;

class SpecificData
{
public:
    SpecificData(int dataType, QString deviceName, std::vector<Data_Time> dataTimeVector);
    ~SpecificData();


    QString dataTypeName() const;
    void setDataTypeName(const QString &dataTypeName);

    QString deviceName() const;
    void setDeviceName(const QString &deviceName);

    std::vector<Data_Time> dataTimeVector() const;
    void setDataTimeVector(const std::vector<Data_Time> &dataTimeVector);

private:
    int m_dataType;
    QString m_dataTypeName;
    QString m_deviceName;
    std::vector<Data_Time> m_dataTimeVector;


};

#endif // SPECIFICDATA_H

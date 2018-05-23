#include "specificdata.h"

SpecificData::SpecificData(int dataType, QString deviceName, int timeMode, QDate date) :
    m_dataType(dataType),
    m_deviceName(deviceName),
    m_timeMode(timeMode),
    m_day(date.day()),
    m_month(date.month()),
    m_year(date.year())
{
    switch (dataType) {
    case 1:
        m_dataTypeName = "Đ.ẩm đất";
        break;
    case 2:
        m_dataTypeName = "Đ.ẩm mt";
        break;
    case 3:
        m_dataTypeName = "N.độ đất";
        break;
    case 4:
        m_dataTypeName = "N.độ mt";
        break;
    default:
        break;
    }

    QString path = "/home/bean/gatewaydata/"+ deviceName + "/" +  QString::number(m_year)+ "/" + QString::number(m_month) +  "/" + QString::number(m_day);
    QFile mFile(path);
     qDebug() << path;
     //Kiem tra file co ton tai ko
    if(mFile.exists())
    {
        qDebug() << "available";
        //Kiem tra file co doc duoc khong
        if(mFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&mFile);
            QString line;
            do
            {
                line = in.readLine();
                qDebug() << line;
            }while(!line.isNull());
            mFile.close();
        }
    }else qDebug() << "not avaiable";


}

SpecificData::~SpecificData()
{
    qDebug() << "huy spec Data" << m_dataTypeName << m_deviceName ;
    m_dataTimeVector.clear();
}



QString SpecificData::dataTypeName() const
{
    return m_dataTypeName;
}

void SpecificData::setDataTypeName(const QString &dataTypeName)
{
    m_dataTypeName = dataTypeName;
}

QString SpecificData::deviceName() const
{
    return m_deviceName;
}

void SpecificData::setDeviceName(const QString &deviceName)
{
    m_deviceName = deviceName;
}

std::vector<Data_Time> SpecificData::dataTimeVector() const
{
    return m_dataTimeVector;
}

void SpecificData::setDataTimeVector(const std::vector<Data_Time> &dataTimeVector)
{
    m_dataTimeVector = dataTimeVector;
}

int SpecificData::dataType() const
{
    return m_dataType;
}

void SpecificData::setDataType(int dataType)
{
    m_dataType = dataType;
}

#include "specificdata.h"

SpecificData::SpecificData(int dataType, QString deviceName, int timeMode, QDate date) :
    m_dataType(dataType),
    m_deviceName(deviceName),
    m_timeMode(timeMode),
    m_day(date.day()),
    m_month(date.month()),
    m_year(date.year())
{
    int startOfData = 0; //to determind where the needed data is stored in line
    switch (dataType) {
    case 1:
        m_dataTypeName = "Đ.ẩm đất";
        startOfData = 10;
        break;
    case 2:
        m_dataTypeName = "Đ.ẩm mt";
        startOfData = 15;
        break;
    case 3:
        m_dataTypeName = "N.độ đất";
        startOfData = 20;
        break;
    case 4:
        m_dataTypeName = "N.độ mt";
        startOfData = 25;
        break;
    default:
        break;
    }

    QString path = "/home/bean/gatewaydata/"+ deviceName + "/" +  QString::number(m_year)+ "/" + QString::number(m_month) +  "/" + QString::number(m_day);
    QFile mFile(path);
    if(mFile.exists()) //If file exist
    {
        qDebug() << "available";

        if(mFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&mFile);
            QString line;
            while(!in.atEnd()) //Read all line in file
            {
                line = in.readLine();
                if(line.at(0).isDigit()) //if line started by a digit (is time, not Max, Min or Average)
                {
                    //add time and data to vector
                    float time = line.mid(0,2).toInt() + (float)line.mid(3,2).toInt()/60;
                    float data = line.mid(startOfData,4).toFloat();
                    m_dataTimeVector.push_back(Data_Time(data,time));
                }
            }
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

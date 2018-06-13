#include "specificdata.h"

QString  SpecificData::m_dataPath;
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
    case 0:
        m_dataTypeName = "Đ.ẩm đất";
        startOfData = 10;
        break;
    case 1:
        m_dataTypeName = "Đ.ẩm mt";
        startOfData = 15;
       break;
    case 2:
        m_dataTypeName = "N.độ đất";
        startOfData = 20;
        break;
    case 3:
        m_dataTypeName = "N.độ mt";
        startOfData = 25;
        break;
    default:
        break;
    }

    switch (timeMode) {
    case 0:
    {
        m_dataTimeVector.clear();
        QString path = m_dataPath + "/" + m_deviceName + "/" +  QString::number(m_year)+ "/" + QString::number(m_month) +  "/" + QString::number(m_day);
        QFile mFile(path);
        if(mFile.exists()) //If file exist
        {
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
        }
    }
        break;
    case 1:
    {
        m_dataTimeVector.clear();
        QString path= m_dataPath + "/" + m_deviceName + "/" +  QString::number(m_year)+ "/" + QString::number(m_month) +  "/" + QString::number(m_day);
        QFile mFile(path);
        if(mFile.exists()) //If file exist
        {
            if(mFile.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QTextStream in(&mFile);
                QString line;

                while(!in.atEnd()) //Read all line in file
                {
                    line = in.readLine();

                    if(line.at(0) == "T" ) //if line started by a digit (is time, not Max, Min or Average)
                    {
                        //add time and data to vector
                        float time = line.mid(2,2).toInt();// + (float)line.mid(3,2).toInt()/60;
                        float data = line.mid(startOfData,4).toFloat();
                        m_dataTimeVector.push_back(Data_Time(data,time));

                }
                mFile.close();
               }
            }
        }
    }
        break;
    case 2:
    {
        m_dataTimeVector.clear();
        for(int i = 0; i < 7; i++)
        {
            QString path = m_dataPath + "/" + m_deviceName + "/" +  QString::number(date.addDays(i).year())+ "/" + QString::number(date.addDays(i).month()) +  "/" + QString::number(date.addDays(i).day());
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
                        if(line.at(0) == "A") //If it is "a"verage
                        {
                            float data = line.mid(startOfData,4).toFloat();
                            m_dataTimeVector.push_back(Data_Time(data,i));
                        }

                    }
                    mFile.close();
                }
            }else qDebug() << "not avaiable";
        }
    }
        break;
    case 3:
    {
        m_dataTimeVector.clear();
        for(int i = 0; i < 31; i++)
        {
            QString path = m_dataPath + "/" + m_deviceName + "/" +  QString::number(m_year)+ "/" + QString::number(m_month) +  "/" + QString::number(i+1);
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
                        if(line.at(0) == "A") //If it is "a"verage
                        {
                            float data = line.mid(startOfData,4).toFloat();
                            m_dataTimeVector.push_back(Data_Time(data,i));
                        }

                    }
                    mFile.close();
                }
            }else qDebug() << "not avaiable";
        }
    }
        break;
    default:
        break;
    }
}


SpecificData::SpecificData(QString deviceName, QDate date):
    m_deviceName(deviceName),
    m_day(date.day()),
    m_month(date.month()),
    m_year(date.year())
{

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

std::vector<Data_Time> SpecificData::getDataTimeVector(int dataType, int timeMode)
{
    std::vector<Data_Time> dataTimeVector;
    int startOfData = 0; //to determind where the needed data is stored in line
    switch (dataType) {
    case 0:
        startOfData = 10;
        break;
    case 1:
        startOfData = 15;
        break;
    case 2:
        startOfData = 20;
        break;
    case 3:
        startOfData = 25;
        break;
    default:
        break;
    }
    QString path = m_dataPath + "/" + m_deviceName + "/" +  QString::number(m_year)+ "/" + QString::number(m_month) +  "/" + QString::number(m_day);
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
                switch (timeMode) {
                case 0:
                    if(line.at(0).isDigit()) //if line started by a digit (is time, not Max, Min or Average)
                    {
                        //add time and data to vector
                        float time = line.mid(0,2).toInt() + (float)line.mid(3,2).toInt()/60;
                        float data = line.mid(startOfData,4).toFloat();
                        dataTimeVector.push_back(Data_Time(data,time));
                    }
                    break;
                case 1:
                    if(line.at(0) == "T" ) //if line started by a digit (is time, not Max, Min or Average)
                    {
                        //add time and data to vector
                        float time = line.mid(2,2).toInt();// + (float)line.mid(3,2).toInt()/60;
                        float data = line.mid(startOfData,4).toFloat();
                        dataTimeVector.push_back(Data_Time(data,time));
                    }
                    break;
                default:
                    break;
                }

            }
            mFile.close();
        }
    }else qDebug() << "not avaiable";
    return dataTimeVector;
}

Data_Time SpecificData::getLastValue(int dataType)
{

    //return the last value added to DataTimeVecotor
    std::vector<Data_Time> dataTimeVector = getDataTimeVector(dataType, 0);
    if(!dataTimeVector.empty())
    {
        return getDataTimeVector(dataType, 0).back();
    } else return Data_Time(0,0);


}

float SpecificData::getAverageValue(int dataType)
{
    float sumValue = 0;
    std::vector<Data_Time> dataTimeVector = getDataTimeVector(dataType, 0);
    if(!dataTimeVector.empty())
    {
        // calculate sum of all data in vector
        for(uint i = 0; i < dataTimeVector.size(); i++)
        {
            sumValue += dataTimeVector.at(i).first;
        }
        // and return avegare
        return sumValue/dataTimeVector.size();
    } else return 0;

}

Data_Time SpecificData::getMinValue(int dataType)
{

     std::vector<Data_Time> dataTimeVector = getDataTimeVector(dataType, 0);
     if(!dataTimeVector.empty())
     {
        //set min value is equal to the first value
        Data_Time minDataTime = dataTimeVector.at(0) ;
        //compare min value with all value in vector
        for(uint i = 0; i < dataTimeVector.size(); i++)
        {
            if(minDataTime.first > dataTimeVector.at(i).first)  minDataTime = dataTimeVector.at(i);
        }
        return minDataTime;
     } else return Data_Time(0,0);

}

Data_Time SpecificData::getMaxValue(int dataType)
{
    std::vector<Data_Time> dataTimeVector = getDataTimeVector(dataType, 0);
    if(!dataTimeVector.empty())
    {
        //set max value is equal to the first value
            Data_Time maxDataTime = dataTimeVector.at(0) ;
             //compare max value with all value in vector
            for(uint i = 0; i < dataTimeVector.size(); i++)
            {
                if(maxDataTime.first < dataTimeVector.at(i).first)  maxDataTime = dataTimeVector.at(i);
            }
            return maxDataTime;
    } else return Data_Time(0,0);

}

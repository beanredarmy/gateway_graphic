#ifndef Place_H
#define Place_H

#include <QString>
#include <vector>

class Place
{
public:
    Place();
    Place(const QString &name);
    ~Place();

    QString name() const;
    void setName(const QString &name);

    float curTemperature() const;
    void setCurTemperature(float curTemperature);

    float curHumidity() const;
    void setCurHumidity(float curHumidity);

    float curPressure() const;
    void setCurPressure(float curPressure);

    void updateCurInfor();  //Cap nhat thong tin hien tai


private:
    QString m_name;
    float m_curTemperature; //Nhiet do hien tai
    float m_curHumidity;    // Do am hien tai
    float m_curPressure;    // Ap suat hien tai

    std::vector<float> m_hour_temp; //Mang chua du lieu nhiet do trong 1 gio (co 60 gia tri)
    std::vector<float> m_hour_humi;
    std::vector<float> m_hour_pres;

    std::vector<float> m_day_temp; //Mang chua du lieu nhiet do trong 1 ngay (co 24*60 = 1440 gia tri)
    std::vector<float> m_day_humi;
    std::vector<float> m_day_pres;

    std::vector<float> m_month_temp; // Mang chua du lieu cac nhiet do trung binh ngay trong 1 thang ( co khoang 30 gia tri tuy thang)
    std::vector<float> m_month_humi;
    std::vector<float> m_month_pres;

    std::vector<float> m_year_temp; // Mang chua du lieu cac nhiet do trung binh ngay trong 1 nam ( co 12 gia tri cac thang)
    std::vector<float> m_year_humi;
    std::vector<float> m_year_pres;




};

#endif // Place_H

#include "detailwidget.h"

QStringList  DetailWidget::m_deviceList;

DetailWidget::DetailWidget(QWidget *parent) : QWidget(parent)
{
    setupWidgets();
    setupOptions();
    connect(pushButton_OK, SIGNAL (clicked()),this, SLOT (drawChart()));
    connect(pushButton_showData, SIGNAL (clicked()),this, SLOT (viewFileData()));
    connect(pushButton_viewNow, SIGNAL (clicked()),this, SLOT (showPresentData()));
    connect(pushBtn_compare, SIGNAL (clicked()),this, SLOT (compareData()));
    connect(pushBtn_notCompare, SIGNAL (clicked()),this, SLOT (hideComparison()));
    connect(cmbBox_device, SIGNAL (currentIndexChanged(QString)),this, SLOT (changeDataDisplay(QString)));
}

DetailWidget::~DetailWidget()
{
    delete gridLayout_2;
    delete frame_option;
    delete frame_content;
    qDebug() << QString("huy %1").arg(m_order);
}

void DetailWidget::setupOptions()
{
    //setup date mode, graph mode and theme available options.
    cmbBox_dateMode->addItems(QStringList() << "Ngày/CT" << "Ngày/TB" << "7 Ngày" << "Tháng");
    cmbBox_graphMode->addItems(QStringList() << "Line" << "Spline" << "Scatter");
    cmbBox_theme->addItems(QStringList() << "Light" << "Dark" << "Blue Cerulean" << "Brown Sand" << "Blue NCS" << "High Contrast" << "Blue Icy" << "Qt");
    //change theme when the value of theme combox box changed
    connect(cmbBox_theme, SIGNAL (currentIndexChanged(int)),this, SLOT (changeTheme(int)));

    //add all available device names to the comboboxes
    cmbBox_device->addItems(m_deviceList);
    cmbBox_device2->addItems(m_deviceList);
    cmbBox_device3->addItems(m_deviceList);
    //set all date edit to current day
    dateEdit_device1->setDate(QDate::currentDate());
    dateEdit_device2->setDate(QDate::currentDate());
    dateEdit_device3->setDate(QDate::currentDate());
}

void DetailWidget::setupFontChart(QChart *chart) const
{
    //change font of all axes
    for(int i=0; i<chart->axes().count(); ++i )
    {
        chart->axes()[i]->setTitleFont(QFont("Calibri", 11, QFont::Bold));
        chart->axes()[i]->setLabelsFont(QFont("Calibri", 11));
    }
    //and change font of legend
    chart->legend()->setFont(QFont("Calibri", 10));
}

QChart *DetailWidget::createLineChart(std::vector<SpecificData *> specDataVector) const
{
    QChart *chart = new QChart();
    chart->setContentsMargins(-25,-25,-25,-25);

    //iterate all specificData
    for (uint i = 0; i < specDataVector.size(); i++)  {
        //create scatter and line serie
        QScatterSeries *series2 = new QScatterSeries(chart);
        series2->setMarkerSize(5.0);
        QLineSeries *series = new QLineSeries(chart);
        //iterate all (date,time) elements of specificData
        for (uint j = 0; j<specDataVector[i]->dataTimeVector().size();j++)
        {
            //add each elements to series
            series->append(specDataVector[i]->dataTimeVector()[j].second, specDataVector[i]->dataTimeVector()[j].first);
            series2->append(specDataVector[i]->dataTimeVector()[j].second, specDataVector[i]->dataTimeVector()[j].first);
        }
        //set name for series based on device name and data type
        series->setName(specDataVector[i]->deviceName() + QString(": ") + specDataVector[i]->dataTypeName());
        //add series to chart
        chart->addSeries(series);
        chart->addSeries(series2);
        //hide legend of scatter serie
        chart->legend()->markers(series2)[0]->setVisible(false);
        //If specData is humidity then connect to slot tooltip of humidity
        if(specDataVector[i]->dataType() == 0 || specDataVector[i]->dataType() == 1) // Neu series cua do am thi ket noi toi tooltip
        {
            connect(series, &QSplineSeries::hovered, this, &DetailWidget::tooltip);
            connect(series2, &QSplineSeries::hovered, this, &DetailWidget::tooltip);
        } else // else if specData is temperature then connect to slot tooltip of temperature
        {
            connect(series, &QSplineSeries::hovered, this, &DetailWidget::tooltip_temp);
            connect(series2, &QSplineSeries::hovered, this, &DetailWidget::tooltip_temp);
        }
    }

    //create axisX and axisY by default
    chart->createDefaultAxes();
    //Set range of axisX based on date mode
    switch (cmbBox_dateMode->currentIndex()) {
    case 0://if mode is day
        chart->axisX()->setRange(0, 24);
        static_cast<QValueAxis *>(chart->axisX())->setTickCount(13);
        break;
    case 1://if mode is day
        chart->axisX()->setRange(0, 24);
        static_cast<QValueAxis *>(chart->axisX())->setTickCount(13);
        break;
    case 2: //if mode is 7 days
        chart->axisX()->setRange(0, 6);
        static_cast<QValueAxis *>(chart->axisX())->setTickCount(7);
        break;
    case 3://if mode is month
        chart->axisX()->setRange(1, 31);
        static_cast<QValueAxis *>(chart->axisX())->setTickCount(11);
        break;
    default:
        break;
    }
    //axisY is a humidity axis (from 0 to 100 %)
    chart->axisY()->setRange(0, 100);
    chart->axisX()->setTitleText("Thời gian (h)");
    chart->axisY()->setTitleText("Độ ẩm (%)");
    //create temperature axis (from 0 to 60 degree)
    QValueAxis *axisTemp = new QValueAxis();
    axisTemp->setRange(0,60);
    axisTemp->setTitleText("Nhiệt độ (độ C)");
    chart->addAxis(axisTemp,Qt::AlignRight);

    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisY())->setLabelFormat("%.1f  ");

    return chart;

}

QChart *DetailWidget::createSplineChart(std::vector<SpecificData *> specDataVector) const
{
    QChart *chart = new QChart();
    chart->setContentsMargins(-25,-25,-25,-25);

    //iterate all specificData
    for (uint i = 0; i < specDataVector.size(); i++)  {
        //create scatter and line serie
        QScatterSeries *series2 = new QScatterSeries(chart);
        series2->setMarkerSize(5.0);
        QSplineSeries *series = new QSplineSeries(chart);
        //iterate all (date,time) elements of specificData
        for (uint j = 0; j<specDataVector[i]->dataTimeVector().size();j++)
        {
            //add each elements to series
            series->append(specDataVector[i]->dataTimeVector()[j].second, specDataVector[i]->dataTimeVector()[j].first);
            series2->append(specDataVector[i]->dataTimeVector()[j].second, specDataVector[i]->dataTimeVector()[j].first);
        }
        //set name for series based on device name and data type
        series->setName(specDataVector[i]->deviceName() + QString(": ") + specDataVector[i]->dataTypeName());
        //add series to chart
        chart->addSeries(series);
        chart->addSeries(series2);
        //hide legend of scatter serie
        chart->legend()->markers(series2)[0]->setVisible(false);
        //If specData is humidity then connect to slot tooltip of humidity
        if(specDataVector[i]->dataType() == 0 || specDataVector[i]->dataType() == 1) // Neu series cua do am thi ket noi toi tooltip
        {
            connect(series, &QSplineSeries::hovered, this, &DetailWidget::tooltip);
            connect(series2, &QSplineSeries::hovered, this, &DetailWidget::tooltip);
        } else // else if specData is temperature then connect to slot tooltip of temperature
        {
            connect(series, &QSplineSeries::hovered, this, &DetailWidget::tooltip_temp);
            connect(series2, &QSplineSeries::hovered, this, &DetailWidget::tooltip_temp);
        }
    }

    //create axisX and axisY by default
    chart->createDefaultAxes();
    //Set range of axisX based on date mode
    switch (cmbBox_dateMode->currentIndex()) {
    case 0://if mode is day
        chart->axisX()->setRange(0, 24);
        static_cast<QValueAxis *>(chart->axisX())->setTickCount(13);
        break;
    case 1://if mode is day
        chart->axisX()->setRange(0, 24);
        static_cast<QValueAxis *>(chart->axisX())->setTickCount(13);
        break;
    case 2: //if mode is 7 days
        chart->axisX()->setRange(0, 6);
        static_cast<QValueAxis *>(chart->axisX())->setTickCount(7);
        break;
    case 3://if mode is month
        chart->axisX()->setRange(1, 31);
        static_cast<QValueAxis *>(chart->axisX())->setTickCount(11);
        break;
    default:
        break;
    }
    //axisY is a humidity axis (from 0 to 100 %)
    chart->axisY()->setRange(0, 100);
    chart->axisX()->setTitleText("Thời gian (h)");
    chart->axisY()->setTitleText("Độ ẩm (%)");
    //create temperature axis (from 0 to 60 degree)
    QValueAxis *axisTemp = new QValueAxis();
    axisTemp->setRange(0,60);
    axisTemp->setTitleText("Nhiệt độ (độ C)");
    chart->addAxis(axisTemp,Qt::AlignRight);

    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisY())->setLabelFormat("%.1f  ");

    return chart;
}

QChart *DetailWidget::createScatterChart(std::vector<SpecificData *> specDataVector) const
{
    QChart *chart = new QChart();
    chart->setContentsMargins(-25,-25,-25,-25);

    //iterate all specificData
    for (uint i = 0; i < specDataVector.size(); i++)  {
        //create scatter and line serie
        QScatterSeries *series2 = new QScatterSeries(chart);
        series2->setMarkerSize(5.0);

        //iterate all (date,time) elements of specificData
        for (uint j = 0; j<specDataVector[i]->dataTimeVector().size();j++)
        {
            //add each elements to series

            series2->append(specDataVector[i]->dataTimeVector()[j].second, specDataVector[i]->dataTimeVector()[j].first);
        }
        //set name for series based on device name and data type

        //add series to chart

        chart->addSeries(series2);
        //hide legend of scatter serie
        chart->legend()->markers(series2)[0]->setVisible(false);
        //If specData is humidity then connect to slot tooltip of humidity
        if(specDataVector[i]->dataType() == 0 || specDataVector[i]->dataType() == 1) // Neu series cua do am thi ket noi toi tooltip
        {

            connect(series2, &QSplineSeries::hovered, this, &DetailWidget::tooltip);
        } else // else if specData is temperature then connect to slot tooltip of temperature
        {

            connect(series2, &QSplineSeries::hovered, this, &DetailWidget::tooltip_temp);
        }
    }

    //create axisX and axisY by default
    chart->createDefaultAxes();
    //Set range of axisX based on date mode
    switch (cmbBox_dateMode->currentIndex()) {
    case 0://if mode is day
        chart->axisX()->setRange(0, 24);
        static_cast<QValueAxis *>(chart->axisX())->setTickCount(13);
        break;
    case 1://if mode is day
        chart->axisX()->setRange(0, 24);
        static_cast<QValueAxis *>(chart->axisX())->setTickCount(13);
        break;
    case 2: //if mode is 7 days
        chart->axisX()->setRange(0, 6);
        static_cast<QValueAxis *>(chart->axisX())->setTickCount(7);
        break;
    case 3://if mode is month
        chart->axisX()->setRange(1, 31);
        static_cast<QValueAxis *>(chart->axisX())->setTickCount(11);
        break;
    default:
        break;
    }
    //axisY is a humidity axis (from 0 to 100 %)
    chart->axisY()->setRange(0, 100);
    chart->axisX()->setTitleText("Thời gian (h)");
    chart->axisY()->setTitleText("Độ ẩm (%)");
    //create temperature axis (from 0 to 60 degree)
    QValueAxis *axisTemp = new QValueAxis();
    axisTemp->setRange(0,60);
    axisTemp->setTitleText("Nhiệt độ (độ C)");
    chart->addAxis(axisTemp,Qt::AlignRight);

    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisY())->setLabelFormat("%.1f  ");

    return chart;
}

void DetailWidget::drawChart()
{
    if(cmbBox_device->currentIndex() != 0) //If currentText != Chon
    {
        m_tooltip = 0;
        //get infor from comboboxes and dateEdit
        QString deviceName = cmbBox_device->currentText();
        int timeMode = cmbBox_dateMode->currentIndex();
        QDate date = dateEdit_device1->date();

        std::vector<SpecificData*> specDataVector;
        QCheckBox *checkBoxes[4] = {checkBox_humi_soil, checkBox_humi_envi, checkBox_temp_soil, checkBox_temp_envi };
        int numberOfCheckBoxes = 0;
        //Create specific data based on checkbox checked
        for(int i = 0; i < 4; i++)
        {
            if(checkBoxes[i]->isChecked())
            {
                SpecificData *specData = new SpecificData(i,deviceName,timeMode,date);
                specDataVector.push_back(specData);
                numberOfCheckBoxes ++;
            }
        }

        //Check for the number of checkBox != 0
        if(numberOfCheckBoxes != 0)
        {
            //remove previous chart
            m_chartView->chart()->deleteLater();
            switch (cmbBox_graphMode->currentIndex()) {
            case 0:
                m_chartView->setChart(createLineChart(specDataVector));
                break;
            case 1:
                m_chartView->setChart(createSplineChart(specDataVector));
                break;
            case 2:
                m_chartView->setChart(createScatterChart(specDataVector));
                break;
            default:
                break;
            }
        } else emit sendMessToStatusBar(QString("Hãy chọn ít nhất một thông số!"));


        //Release memory allocated for specific data
        for (std::vector< SpecificData* >::iterator it = specDataVector.begin() ; it != specDataVector.end(); ++it)
        {
            delete (*it);
        }
        //and clear vector
        specDataVector.clear();

        //re-setup font chart
        setupFontChart(m_chartView->chart());

        //call currentIndexChanged function to change theme immediately
        cmbBox_theme->currentIndexChanged(cmbBox_theme->currentIndex());
    } else emit sendMessToStatusBar(QString("Hãy chọn thiết bị"));

}

void DetailWidget::viewFileData()
{
    QString deviceName = cmbBox_device->currentText();
    QDate date = dateEdit_device1->date();
    QString docPath = SpecificData::m_dataPath + "/" + deviceName + "/" +  QString::number(date.year())+ "/" + QString::number(date.month()) +  "/" + QString::number(date.day());
    QFile mFile(docPath);
    if(mFile.exists()) //If file exist
    {
        qDebug() << "available";
        QProcess::execute("gedit "+docPath);
    }else qDebug() << "not avaiable";


}

void DetailWidget::showPresentData()
{
    //set date to current day and date mode to day
    dateEdit_device1->setDate(QDate::currentDate());
    cmbBox_dateMode->setCurrentIndex(0);
    drawChart();
}

void DetailWidget::compareData()
{
    if(cmbBox_device->currentIndex() != 0) //If currentText != Chon
    {
        m_tooltip = 0;
        //get infor from comboboxes and dateEdit
        QString deviceName = cmbBox_device->currentText();
        QString deviceName2 = cmbBox_device2->currentText();
        QString deviceName3 = cmbBox_device3->currentText();
        int timeMode = cmbBox_dateMode->currentIndex();
        QDate date = dateEdit_device1->date();
        QDate date2 = dateEdit_device2->date();
        QDate date3 = dateEdit_device3->date();

        std::vector<SpecificData*> specDataVector;
        QCheckBox *checkBoxes[4] = {checkBox_humi_soil, checkBox_humi_envi, checkBox_temp_soil, checkBox_temp_envi };
        //Create specific data based on checkbox checked
        for(int i = 0; i < 4; i++)
        {
            if(checkBoxes[i]->isChecked())
            {
                SpecificData *specData = new SpecificData(i,deviceName,timeMode,date);
                specDataVector.push_back(specData);
                if(cmbBox_device2->currentIndex() != 0)
                {
                    SpecificData *specData2 = new SpecificData(i,deviceName2,timeMode,date2);
                    specDataVector.push_back(specData2);
                }
                if(cmbBox_device3->currentIndex() != 0)
                {
                    SpecificData *specData3 = new SpecificData(i,deviceName3,timeMode,date3);
                    specDataVector.push_back(specData3);
                }
            }
        }
        //remove previous chart
        m_chartView->chart()->deleteLater();
        switch (cmbBox_graphMode->currentIndex()) {
        case 0:
            m_chartView->setChart(createLineChart(specDataVector));
            break;
        case 1:
            m_chartView->setChart(createSplineChart(specDataVector));
            break;
        case 2:
            m_chartView->setChart(createScatterChart(specDataVector));
            break;
        default:
            break;
        }
        //Release memory allocated for specific data
        for (std::vector< SpecificData* >::iterator it = specDataVector.begin() ; it != specDataVector.end(); ++it)
        {
            delete (*it);
        }
        //and clear vector
        specDataVector.clear();

        //re-setup font chart
        setupFontChart(m_chartView->chart());

        //call currentIndexChanged function to change theme immediately
        cmbBox_theme->currentIndexChanged(cmbBox_theme->currentIndex());
    } else emit sendMessToStatusBar(QString("Hãy chọn thiết bị"));
}

void DetailWidget::hideComparison()
{
    drawChart();
}

//tooltip for humidity
void DetailWidget::tooltip(QPointF point, bool state)
{
    //check whether tooltip is created?
    if (m_tooltip == 0)
        m_tooltip = new Callout(m_chartView->chart());

    if (state) {
        if(cmbBox_dateMode->currentIndex() == 2 || cmbBox_dateMode->currentIndex() == 3)
        {
            m_tooltip->setText(QString("Ngày:%1\nĐ.Ẩm:%2").arg(floor(point.x())).arg(round(point.y()*100)/100));
        }else
        {
            //get minute value from coordinate
            int minute = (int)((point.x()-(int)point.x())*60);
            //show value and time to tooltip
            m_tooltip->setText(QString("T.Gian:%1h%2p\nĐ.Ẩm:%3").arg(round(point.x())).arg(minute).arg(round(point.y()*100)/100));
        }
        m_tooltip->setAnchor(point);
        m_tooltip->setZValue(11);
        m_tooltip->updateGeometry();
        m_tooltip->show();
    } else {
        m_tooltip->hide();
    }
}

//tooltip for temperature
void DetailWidget::tooltip_temp(QPointF point, bool state)
{
     //check whether tooltip is created?
    if (m_tooltip == 0)
        m_tooltip = new Callout(m_chartView->chart());

    if (state) {
        if(cmbBox_dateMode->currentIndex() == 2 || cmbBox_dateMode->currentIndex() == 3)
        {
            m_tooltip->setText(QString("Ngày:%1\nN.Độ:%2").arg(floor(point.x())).arg(round(point.y()*60)/100));
        } else
        {
            //get minute value from coordinate
            int minute = (int)((point.x()-(int)point.x())*60);
            //show value and time to tooltip
            m_tooltip->setText(QString("T.Gian:%1h%2p\nN.Độ:%3").arg(round(point.x())).arg(minute).arg(round(point.y()*60)/100));
        }
        m_tooltip->setAnchor(point);
        m_tooltip->setZValue(11);
        m_tooltip->updateGeometry();
        m_tooltip->show();
    } else {
        m_tooltip->hide();
    }
}

void DetailWidget::changeTheme(int index)
{
    //change theme based on index of theme combobox
    switch (index) {
    case 0:
        m_chartTheme = QChart::ChartThemeLight;
        break;
    case 1:
        m_chartTheme = QChart::ChartThemeDark;
        break;
    case 2:
        m_chartTheme = QChart::ChartThemeBlueCerulean;
        break;
    case 3:
        m_chartTheme = QChart::ChartThemeBrownSand;
        break;
    case 4:
        m_chartTheme = QChart::ChartThemeBlueNcs;
        break;
    case 5:
        m_chartTheme = QChart::ChartThemeHighContrast;
        break;
    case 6:
        m_chartTheme = QChart::ChartThemeBlueIcy;
        break;
    case 7:
        m_chartTheme = QChart::ChartThemeQt;
        break;
    default:
        break;
    }

        m_chartView->chart()->setTheme(m_chartTheme);
        setupFontChart(m_chartView->chart());

        // Set palette colors based on selected theme
        //![8]
        QPalette pal = window()->palette();
        if (m_chartTheme == QChart::ChartThemeLight) {
            pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        //![8]
        } else if (m_chartTheme == QChart::ChartThemeDark) {
            pal.setColor(QPalette::Window, QRgb(0x40434a));
            pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
        } else if (m_chartTheme == QChart::ChartThemeBlueCerulean) {
            pal.setColor(QPalette::Window, QRgb(0x0D6299));
            pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
        } else if (m_chartTheme == QChart::ChartThemeBrownSand) {
            pal.setColor(QPalette::Window, QRgb(0x9e8965));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else if (m_chartTheme == QChart::ChartThemeBlueNcs) {
            pal.setColor(QPalette::Window, QRgb(0x018bba));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else if (m_chartTheme == QChart::ChartThemeHighContrast) {
            pal.setColor(QPalette::Window, QRgb(0xffab03));
            pal.setColor(QPalette::WindowText, QRgb(0x181818));
        } else if (m_chartTheme == QChart::ChartThemeBlueIcy) {
            pal.setColor(QPalette::Window, QRgb(0xcee7f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else {
            pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        }
        frame_content->setPalette(pal);
        frame_option->setPalette(pal);
        window()->setPalette(pal);
}

void DetailWidget::changeDataDisplay(QString deviceName)
{
    int dataType;
    if(checkBox_humi_soil->isChecked()) dataType = 0;
    else if(checkBox_humi_envi->isChecked()) dataType = 1;
    else if(checkBox_temp_soil->isChecked()) dataType = 2;
    else if(checkBox_temp_envi->isChecked()) dataType = 3;
    SpecificData *todayData = new SpecificData(deviceName,QDate::currentDate());

    Data_Time temporaryData_Table = todayData->getLastValue(dataType);
    lcdNumber_curValue->display(temporaryData_Table.first);
    lcdNumber_curValue->setToolTip(QString("T.Gian: %1h%2p").arg(round(temporaryData_Table.second)).arg((int)((temporaryData_Table.second-(int)temporaryData_Table.second)*60)));

    lcdNumber_aveValue->display(todayData->getAverageValue(dataType));

    temporaryData_Table = todayData->getMinValue(dataType);
    lcdNumber_minValue->display(temporaryData_Table.first);
    lcdNumber_minValue->setToolTip(QString("T.Gian: %1h%2p").arg(round(temporaryData_Table.second)).arg((int)((temporaryData_Table.second-(int)temporaryData_Table.second)*60)));

    temporaryData_Table = todayData->getMaxValue(dataType);
    lcdNumber_maxValue->display(temporaryData_Table.first);
    lcdNumber_maxValue->setToolTip(QString("T.Gian: %1h%2p").arg(round(temporaryData_Table.second)).arg((int)((temporaryData_Table.second-(int)temporaryData_Table.second)*60)));

    delete todayData;
}

//initiate and setup widgets
void DetailWidget::setupWidgets()
{
    QFont font;
    font.setFamily(QStringLiteral("Calibri"));
    gridLayout_2 = new QGridLayout(this);
    gridLayout_2->setSpacing(2);
    gridLayout_2->setContentsMargins(11, 11, 11, 11);
    gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
    gridLayout_2->setContentsMargins(3, 3, 3, 3);
    frame_content = new QFrame(this);
    frame_content->setObjectName(QStringLiteral("frame_content"));
    QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Minimum);
    sizePolicy4.setHorizontalStretch(0);
    sizePolicy4.setVerticalStretch(0);
    sizePolicy4.setHeightForWidth(frame_content->sizePolicy().hasHeightForWidth());
    frame_content->setSizePolicy(sizePolicy4);
    frame_content->setFrameShape(QFrame::StyledPanel);
    frame_content->setFrameShadow(QFrame::Raised);
    gridLayout_5 = new QGridLayout(frame_content);
    gridLayout_5->setSpacing(2);
    gridLayout_5->setContentsMargins(11, 11, 11, 11);
    gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
    gridLayout_5->setContentsMargins(3, 3, 3, 3);
    horizontalLayout_11 = new QHBoxLayout();
    horizontalLayout_11->setSpacing(3);
    horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
    horizontalLayout_8 = new QHBoxLayout();
    horizontalLayout_8->setSpacing(6);
    horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
    label_9 = new QLabel(frame_content);
    label_9->setObjectName(QStringLiteral("label_9"));
    QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
    sizePolicy1.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
    label_9->setSizePolicy(sizePolicy1);
    QFont font7;
    font7.setFamily(QStringLiteral("Calibri"));
    font7.setPointSize(11);
    label_9->setFont(font7);

    horizontalLayout_8->addWidget(label_9);

    lcdNumber_curValue = new QLCDNumber(frame_content);
    lcdNumber_curValue->setObjectName(QStringLiteral("lcdNumber_curValue"));
    QSizePolicy sizePolicy5(QSizePolicy::Maximum, QSizePolicy::Maximum);
    sizePolicy5.setHorizontalStretch(0);
    sizePolicy5.setVerticalStretch(0);
    sizePolicy5.setHeightForWidth(lcdNumber_curValue->sizePolicy().hasHeightForWidth());
    lcdNumber_curValue->setSizePolicy(sizePolicy5);
    lcdNumber_curValue->setMaximumSize(QSize(16777215, 22));
    lcdNumber_curValue->setFont(font);

    horizontalLayout_8->addWidget(lcdNumber_curValue);


    horizontalLayout_11->addLayout(horizontalLayout_8);

    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

    horizontalLayout_11->addItem(horizontalSpacer);

    horizontalLayout_9 = new QHBoxLayout();
    horizontalLayout_9->setSpacing(6);
    horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
    label_10 = new QLabel(frame_content);
    label_10->setObjectName(QStringLiteral("label_10"));
    sizePolicy1.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
    label_10->setSizePolicy(sizePolicy1);
    label_10->setFont(font7);

    horizontalLayout_9->addWidget(label_10);

    lcdNumber_aveValue = new QLCDNumber(frame_content);
    lcdNumber_aveValue->setObjectName(QStringLiteral("lcdNumber_aveValue"));
    sizePolicy5.setHeightForWidth(lcdNumber_aveValue->sizePolicy().hasHeightForWidth());
    lcdNumber_aveValue->setSizePolicy(sizePolicy5);
    lcdNumber_aveValue->setMaximumSize(QSize(16777215, 22));
    lcdNumber_aveValue->setFont(font);

    horizontalLayout_9->addWidget(lcdNumber_aveValue);


    horizontalLayout_11->addLayout(horizontalLayout_9);

    horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

    horizontalLayout_11->addItem(horizontalSpacer_2);

    horizontalLayout_10 = new QHBoxLayout();
    horizontalLayout_10->setSpacing(6);
    horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
    label_11 = new QLabel(frame_content);
    label_11->setObjectName(QStringLiteral("label_11"));
    sizePolicy1.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
    label_11->setSizePolicy(sizePolicy1);
    label_11->setFont(font7);

    horizontalLayout_10->addWidget(label_11);

    lcdNumber_minValue = new QLCDNumber(frame_content);
    lcdNumber_minValue->setObjectName(QStringLiteral("lcdNumber_minValue"));
    sizePolicy5.setHeightForWidth(lcdNumber_minValue->sizePolicy().hasHeightForWidth());
    lcdNumber_minValue->setSizePolicy(sizePolicy5);
    lcdNumber_minValue->setMaximumSize(QSize(16777215, 22));
    lcdNumber_minValue->setFont(font);

    horizontalLayout_10->addWidget(lcdNumber_minValue);

    label_12 = new QLabel(frame_content);
    label_12->setObjectName(QStringLiteral("label_12"));
    QSizePolicy sizePolicy6(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy6.setHorizontalStretch(0);
    sizePolicy6.setVerticalStretch(0);
    sizePolicy6.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
    label_12->setSizePolicy(sizePolicy6);
    label_12->setFont(font);

    horizontalLayout_10->addWidget(label_12);

    lcdNumber_maxValue = new QLCDNumber(frame_content);
    lcdNumber_maxValue->setObjectName(QStringLiteral("lcdNumber_maxValue"));
    sizePolicy5.setHeightForWidth(lcdNumber_maxValue->sizePolicy().hasHeightForWidth());
    lcdNumber_maxValue->setSizePolicy(sizePolicy5);
    lcdNumber_maxValue->setMaximumSize(QSize(16777215, 22));
    lcdNumber_maxValue->setFont(font);

    horizontalLayout_10->addWidget(lcdNumber_maxValue);


    horizontalLayout_11->addLayout(horizontalLayout_10);


    gridLayout_5->addLayout(horizontalLayout_11, 0, 0, 1, 1);

    gridLayout_graph = new QGridLayout();
    gridLayout_graph->setSpacing(3);
    gridLayout_graph->setObjectName(QStringLiteral("gridLayout_graph"));

    gridLayout_5->addLayout(gridLayout_graph, 1, 0, 1, 1);


    gridLayout_2->addWidget(frame_content, 0, 0, 1, 1);

    frame_option = new QFrame(this);
    frame_option->setObjectName(QStringLiteral("frame_option"));
    sizePolicy4.setHeightForWidth(frame_option->sizePolicy().hasHeightForWidth());
    frame_option->setSizePolicy(sizePolicy4);
    frame_option->setFrameShape(QFrame::StyledPanel);
    frame_option->setFrameShadow(QFrame::Raised);
    gridLayout_6 = new QGridLayout(frame_option);
    gridLayout_6->setSpacing(2);
    gridLayout_6->setContentsMargins(11, 11, 11, 11);
    gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
    gridLayout_6->setContentsMargins(3, 3, 3, 3);
    verticalLayout_3 = new QVBoxLayout();
    verticalLayout_3->setSpacing(3);
    verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
    verticalLayout_4 = new QVBoxLayout();
    verticalLayout_4->setSpacing(3);
    verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
    verticalLayout_4->setContentsMargins(-1, 0, -1, -1);
    label_16 = new QLabel(frame_option);
    label_16->setObjectName(QStringLiteral("label_16"));
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
    label_16->setSizePolicy(sizePolicy);
    label_16->setFont(font7);
    label_16->setAlignment(Qt::AlignCenter);

    verticalLayout_4->addWidget(label_16);

    checkBox_humi_soil = new QCheckBox(frame_option);
    checkBox_humi_soil->setObjectName(QStringLiteral("checkBox_humi_soil"));
    QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
    sizePolicy2.setHeightForWidth(checkBox_humi_soil->sizePolicy().hasHeightForWidth());
    checkBox_humi_soil->setSizePolicy(sizePolicy2);
    checkBox_humi_soil->setMaximumSize(QSize(16777215, 20));
    checkBox_humi_soil->setFont(font7);
    checkBox_humi_soil->setChecked(true);

    verticalLayout_4->addWidget(checkBox_humi_soil);

    checkBox_humi_envi = new QCheckBox(frame_option);
    checkBox_humi_envi->setObjectName(QStringLiteral("checkBox_humi_envi"));
    sizePolicy2.setHeightForWidth(checkBox_humi_envi->sizePolicy().hasHeightForWidth());
    checkBox_humi_envi->setSizePolicy(sizePolicy2);
    checkBox_humi_envi->setMaximumSize(QSize(16777215, 20));
    checkBox_humi_envi->setFont(font7);

    verticalLayout_4->addWidget(checkBox_humi_envi);

    checkBox_temp_soil = new QCheckBox(frame_option);
    checkBox_temp_soil->setObjectName(QStringLiteral("checkBox_temp_soil"));
    sizePolicy2.setHeightForWidth(checkBox_temp_soil->sizePolicy().hasHeightForWidth());
    checkBox_temp_soil->setSizePolicy(sizePolicy2);
    checkBox_temp_soil->setMaximumSize(QSize(16777215, 20));
    checkBox_temp_soil->setFont(font7);

    verticalLayout_4->addWidget(checkBox_temp_soil);

    checkBox_temp_envi = new QCheckBox(frame_option);
    checkBox_temp_envi->setObjectName(QStringLiteral("checkBox_temp_envi"));
    sizePolicy2.setHeightForWidth(checkBox_temp_envi->sizePolicy().hasHeightForWidth());
    checkBox_temp_envi->setSizePolicy(sizePolicy2);
    checkBox_temp_envi->setMaximumSize(QSize(16777215, 20));
    checkBox_temp_envi->setFont(font7);

    verticalLayout_4->addWidget(checkBox_temp_envi);


    verticalLayout_3->addLayout(verticalLayout_4);

    horizontalLayout_6 = new QHBoxLayout();
    horizontalLayout_6->setSpacing(6);
    horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
    horizontalLayout_6->setSizeConstraint(QLayout::SetFixedSize);
    label_7 = new QLabel(frame_option);
    label_7->setObjectName(QStringLiteral("label_7"));
    sizePolicy1.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
    label_7->setSizePolicy(sizePolicy1);
    label_7->setFont(font7);

    horizontalLayout_6->addWidget(label_7);

    cmbBox_device = new QComboBox(frame_option);
    cmbBox_device->setObjectName(QStringLiteral("cmbBox_device"));
    sizePolicy2.setHeightForWidth(cmbBox_device->sizePolicy().hasHeightForWidth());
    cmbBox_device->setSizePolicy(sizePolicy2);
    cmbBox_device->setMaximumSize(QSize(16777215, 21));
    cmbBox_device->setFont(font7);
    cmbBox_device->setEditable(false);

    horizontalLayout_6->addWidget(cmbBox_device);


    verticalLayout_3->addLayout(horizontalLayout_6);

    horizontalLayout_13 = new QHBoxLayout();
    horizontalLayout_13->setSpacing(6);
    horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
    label_13 = new QLabel(frame_option);
    label_13->setObjectName(QStringLiteral("label_13"));
    sizePolicy1.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
    label_13->setSizePolicy(sizePolicy1);
    label_13->setFont(font7);

    horizontalLayout_13->addWidget(label_13);

    cmbBox_dateMode = new QComboBox(frame_option);
    cmbBox_dateMode->setObjectName(QStringLiteral("cmbBox_dateMode"));
    sizePolicy2.setHeightForWidth(cmbBox_dateMode->sizePolicy().hasHeightForWidth());
    cmbBox_dateMode->setSizePolicy(sizePolicy2);
    cmbBox_dateMode->setMaximumSize(QSize(16777215, 21));
    cmbBox_dateMode->setFont(font7);

    horizontalLayout_13->addWidget(cmbBox_dateMode);


    verticalLayout_3->addLayout(horizontalLayout_13);

    horizontalLayout_7 = new QHBoxLayout();
    horizontalLayout_7->setSpacing(6);
    horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
    horizontalLayout_7->setSizeConstraint(QLayout::SetFixedSize);
    label_8 = new QLabel(frame_option);
    label_8->setObjectName(QStringLiteral("label_8"));
    sizePolicy1.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
    label_8->setSizePolicy(sizePolicy1);
    label_8->setFont(font7);

    horizontalLayout_7->addWidget(label_8);

    dateEdit_device1 = new QDateEdit(frame_option);
    dateEdit_device1->setObjectName(QStringLiteral("dateEdit_device1"));
    dateEdit_device1->setMaximumSize(QSize(16777215, 21));
    dateEdit_device1->setFont(font7);
    dateEdit_device1->setCalendarPopup(true);
    dateEdit_device1->setDate(QDate(2001, 1, 18));

    horizontalLayout_7->addWidget(dateEdit_device1);


    verticalLayout_3->addLayout(horizontalLayout_7);

    pushButton_OK = new QPushButton(frame_option);
    pushButton_OK->setObjectName(QStringLiteral("pushButton_OK"));
    sizePolicy2.setHeightForWidth(pushButton_OK->sizePolicy().hasHeightForWidth());
    pushButton_OK->setSizePolicy(sizePolicy2);
    pushButton_OK->setMaximumSize(QSize(16777215, 21));
    pushButton_OK->setFont(font7);
    pushButton_OK->setLayoutDirection(Qt::LeftToRight);

    verticalLayout_3->addWidget(pushButton_OK);

    horizontalLayout_19 = new QHBoxLayout();
    horizontalLayout_19->setSpacing(6);
    horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
    pushButton_viewNow = new QPushButton(frame_option);
    pushButton_viewNow->setObjectName(QStringLiteral("pushButton_viewNow"));
    pushButton_viewNow->setMaximumSize(QSize(16777215, 21));
    pushButton_viewNow->setFont(font7);

    horizontalLayout_19->addWidget(pushButton_viewNow);

    pushButton_showData = new QPushButton(frame_option);
    pushButton_showData->setObjectName(QStringLiteral("pushButton_showData"));
    pushButton_showData->setEnabled(true);
    pushButton_showData->setMaximumSize(QSize(16777215, 21));
    QFont font8;
    font8.setFamily(QStringLiteral("Calibri"));
    font8.setPointSize(11);
    font8.setBold(false);
    font8.setWeight(50);
    font8.setKerning(true);
    pushButton_showData->setFont(font8);

    horizontalLayout_19->addWidget(pushButton_showData);


    verticalLayout_3->addLayout(horizontalLayout_19);

    line = new QFrame(frame_option);
    line->setObjectName(QStringLiteral("line"));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    verticalLayout_3->addWidget(line);

    label_15 = new QLabel(frame_option);
    label_15->setObjectName(QStringLiteral("label_15"));
    sizePolicy.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
    label_15->setSizePolicy(sizePolicy);
    label_15->setFont(font7);
    label_15->setAlignment(Qt::AlignCenter);

    verticalLayout_3->addWidget(label_15);

    horizontalLayout_14 = new QHBoxLayout();
    horizontalLayout_14->setSpacing(6);
    horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
    label_19 = new QLabel(frame_option);
    label_19->setObjectName(QStringLiteral("label_19"));
    sizePolicy1.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
    label_19->setSizePolicy(sizePolicy1);
    label_19->setFont(font7);

    horizontalLayout_14->addWidget(label_19);

    cmbBox_device2 = new QComboBox(frame_option);
    cmbBox_device2->setObjectName(QStringLiteral("cmbBox_device2"));
    sizePolicy2.setHeightForWidth(cmbBox_device2->sizePolicy().hasHeightForWidth());
    cmbBox_device2->setSizePolicy(sizePolicy2);
    cmbBox_device2->setMaximumSize(QSize(16777215, 21));
    cmbBox_device2->setFont(font7);

    horizontalLayout_14->addWidget(cmbBox_device2);


    verticalLayout_3->addLayout(horizontalLayout_14);

    horizontalLayout_15 = new QHBoxLayout();
    horizontalLayout_15->setSpacing(6);
    horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
    horizontalLayout_15->setSizeConstraint(QLayout::SetFixedSize);
    label_17 = new QLabel(frame_option);
    label_17->setObjectName(QStringLiteral("label_17"));
    sizePolicy1.setHeightForWidth(label_17->sizePolicy().hasHeightForWidth());
    label_17->setSizePolicy(sizePolicy1);
    label_17->setFont(font7);

    horizontalLayout_15->addWidget(label_17);

    dateEdit_device2 = new QDateEdit(frame_option);
    dateEdit_device2->setObjectName(QStringLiteral("dateEdit_device2"));
    dateEdit_device2->setMaximumSize(QSize(16777215, 21));
    dateEdit_device2->setFont(font7);
    dateEdit_device2->setCalendarPopup(true);

    horizontalLayout_15->addWidget(dateEdit_device2);


    verticalLayout_3->addLayout(horizontalLayout_15);

    horizontalLayout_18 = new QHBoxLayout();
    horizontalLayout_18->setSpacing(6);
    horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
    label_20 = new QLabel(frame_option);
    label_20->setObjectName(QStringLiteral("label_20"));
    sizePolicy1.setHeightForWidth(label_20->sizePolicy().hasHeightForWidth());
    label_20->setSizePolicy(sizePolicy1);
    label_20->setFont(font7);

    horizontalLayout_18->addWidget(label_20);

    cmbBox_device3 = new QComboBox(frame_option);
    cmbBox_device3->setObjectName(QStringLiteral("cmbBox_device3"));
    sizePolicy2.setHeightForWidth(cmbBox_device3->sizePolicy().hasHeightForWidth());
    cmbBox_device3->setSizePolicy(sizePolicy2);
    cmbBox_device3->setMaximumSize(QSize(16777215, 21));
    cmbBox_device3->setFont(font7);

    horizontalLayout_18->addWidget(cmbBox_device3);


    verticalLayout_3->addLayout(horizontalLayout_18);

    horizontalLayout_16 = new QHBoxLayout();
    horizontalLayout_16->setSpacing(6);
    horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
    horizontalLayout_16->setSizeConstraint(QLayout::SetFixedSize);
    label_18 = new QLabel(frame_option);
    label_18->setObjectName(QStringLiteral("label_18"));
    sizePolicy1.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
    label_18->setSizePolicy(sizePolicy1);
    label_18->setFont(font7);

    horizontalLayout_16->addWidget(label_18);

    dateEdit_device3 = new QDateEdit(frame_option);
    dateEdit_device3->setObjectName(QStringLiteral("dateEdit_device3"));
    dateEdit_device3->setMaximumSize(QSize(16777215, 21));
    dateEdit_device3->setFont(font7);
    dateEdit_device3->setCalendarPopup(true);

    horizontalLayout_16->addWidget(dateEdit_device3);


    verticalLayout_3->addLayout(horizontalLayout_16);

    horizontalLayout_17 = new QHBoxLayout();
    horizontalLayout_17->setSpacing(6);
    horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
    pushBtn_compare = new QPushButton(frame_option);
    pushBtn_compare->setObjectName(QStringLiteral("pushBtn_compare"));
    sizePolicy4.setHeightForWidth(pushBtn_compare->sizePolicy().hasHeightForWidth());
    pushBtn_compare->setSizePolicy(sizePolicy4);
    pushBtn_compare->setMaximumSize(QSize(16777215, 21));
    pushBtn_compare->setFont(font7);

    horizontalLayout_17->addWidget(pushBtn_compare);

    pushBtn_notCompare = new QPushButton(frame_option);
    pushBtn_notCompare->setObjectName(QStringLiteral("pushBtn_notCompare"));
    sizePolicy2.setHeightForWidth(pushBtn_notCompare->sizePolicy().hasHeightForWidth());
    pushBtn_notCompare->setSizePolicy(sizePolicy2);
    pushBtn_notCompare->setMaximumSize(QSize(16777215, 21));
    pushBtn_notCompare->setFont(font7);

    horizontalLayout_17->addWidget(pushBtn_notCompare);


    verticalLayout_3->addLayout(horizontalLayout_17);

    line_2 = new QFrame(frame_option);
    line_2->setObjectName(QStringLiteral("line_2"));
    line_2->setFrameShape(QFrame::HLine);
    line_2->setFrameShadow(QFrame::Sunken);

    verticalLayout_3->addWidget(line_2);

    label_21 = new QLabel(frame_option);
    label_21->setObjectName(QStringLiteral("label_21"));
    sizePolicy.setHeightForWidth(label_21->sizePolicy().hasHeightForWidth());
    label_21->setSizePolicy(sizePolicy);
    label_21->setFont(font7);
    label_21->setAlignment(Qt::AlignCenter);

    verticalLayout_3->addWidget(label_21);

    horizontalLayout_12 = new QHBoxLayout();
    horizontalLayout_12->setSpacing(6);
    horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
    horizontalLayout_12->setSizeConstraint(QLayout::SetFixedSize);
    label_14 = new QLabel(frame_option);
    label_14->setObjectName(QStringLiteral("label_14"));
    sizePolicy1.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
    label_14->setSizePolicy(sizePolicy1);
    label_14->setFont(font7);

    horizontalLayout_12->addWidget(label_14);

    cmbBox_graphMode = new QComboBox(frame_option);
    cmbBox_graphMode->setObjectName(QStringLiteral("cmbBox_graphMode"));
    sizePolicy2.setHeightForWidth(cmbBox_graphMode->sizePolicy().hasHeightForWidth());
    cmbBox_graphMode->setSizePolicy(sizePolicy2);
    cmbBox_graphMode->setMaximumSize(QSize(16777215, 21));
    cmbBox_graphMode->setFont(font7);

    horizontalLayout_12->addWidget(cmbBox_graphMode);


    verticalLayout_3->addLayout(horizontalLayout_12);

    horizontalLayout_20 = new QHBoxLayout();
    horizontalLayout_20->setSpacing(6);
    horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
    label_23 = new QLabel(frame_option);
    label_23->setObjectName(QStringLiteral("label_23"));
    sizePolicy1.setHeightForWidth(label_23->sizePolicy().hasHeightForWidth());
    label_23->setSizePolicy(sizePolicy1);
    label_23->setFont(font7);

    horizontalLayout_20->addWidget(label_23);

    cmbBox_theme = new QComboBox(frame_option);
    cmbBox_theme->setObjectName(QStringLiteral("cmbBox_theme"));
    sizePolicy2.setHeightForWidth(cmbBox_theme->sizePolicy().hasHeightForWidth());
    cmbBox_theme->setSizePolicy(sizePolicy2);
    cmbBox_theme->setMaximumSize(QSize(16777215, 21));
    cmbBox_theme->setFont(font7);

    horizontalLayout_20->addWidget(cmbBox_theme);


    verticalLayout_3->addLayout(horizontalLayout_20);


    gridLayout_6->addLayout(verticalLayout_3, 0, 0, 1, 1);

    verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout_6->addItem(verticalSpacer, 1, 0, 1, 1);


    gridLayout_2->addWidget(frame_option, 0, 1, 1, 2);


    label_9->setText(QApplication::translate("MainWindow", "Hi\341\273\207n t\341\272\241i", nullptr));
    label_10->setText(QApplication::translate("MainWindow", "Trung b\303\254nh", nullptr));
    label_11->setText(QApplication::translate("MainWindow", "Min/Max", nullptr));
    label_12->setText(QApplication::translate("MainWindow", "/", nullptr));
    label_16->setText(QApplication::translate("MainWindow", "\304\220\341\273\222 TH\341\273\212 CH\303\215NH", nullptr));
    checkBox_humi_soil->setText(QApplication::translate("MainWindow", "\304\220\341\273\231 \341\272\251m \304\221\341\272\245t", nullptr));
    checkBox_humi_envi->setText(QApplication::translate("MainWindow", "\304\220\341\273\231 \341\272\251m m\303\264i tr\306\260\341\273\235ng", nullptr));
    checkBox_temp_soil->setText(QApplication::translate("MainWindow", "Nhi\341\273\207t \304\221\341\273\231 \304\221\341\272\245t", nullptr));
    checkBox_temp_envi->setText(QApplication::translate("MainWindow", "Nhi\341\273\207t \304\221\341\273\231 m\303\264i tr\306\260\341\273\235ng", nullptr));
    label_7->setText(QApplication::translate("MainWindow", "Thi\341\272\277t b\341\273\213", nullptr));
    cmbBox_device->setCurrentText(QString());
    label_13->setText(QApplication::translate("MainWindow", "Theo th\341\273\235i gian", nullptr));
    label_8->setText(QApplication::translate("MainWindow", "Ng\303\240y", nullptr));
    dateEdit_device1->setDisplayFormat(QApplication::translate("MainWindow", "dd/MM/yyyy", nullptr));
    pushButton_OK->setText(QApplication::translate("MainWindow", "OK", nullptr));
    pushButton_viewNow->setText(QApplication::translate("MainWindow", "Hi\341\273\207n t\341\272\241i", nullptr));
    pushButton_showData->setText(QApplication::translate("MainWindow", "M\341\273\237 file", nullptr));
    label_15->setText(QApplication::translate("MainWindow", "SO S\303\201NH", nullptr));
    label_19->setText(QApplication::translate("MainWindow", "Thi\341\272\277t b\341\273\213 2", nullptr));
    label_17->setText(QApplication::translate("MainWindow", "Ng\303\240y 2", nullptr));
    dateEdit_device2->setDisplayFormat(QApplication::translate("MainWindow", "dd/MM/yyyy", nullptr));
    label_20->setText(QApplication::translate("MainWindow", "Thi\341\272\277t b\341\273\213 3", nullptr));
    label_18->setText(QApplication::translate("MainWindow", "Ng\303\240y 3", nullptr));
    dateEdit_device3->setDisplayFormat(QApplication::translate("MainWindow", "dd/MM/yyyy", nullptr));
    pushBtn_compare->setText(QApplication::translate("MainWindow", "So s\303\241nh", nullptr));
    pushBtn_notCompare->setText(QApplication::translate("MainWindow", "\341\272\250n so s\303\241nh", nullptr));
    label_21->setText(QApplication::translate("MainWindow", "T\303\231Y CH\341\273\214N", nullptr));
    label_14->setText(QApplication::translate("MainWindow", "Ki\341\273\203u \304\221\341\273\223 th\341\273\213", nullptr));
    label_23->setText(QApplication::translate("MainWindow", "Theme", nullptr));

    m_chartView = new QChartView();
    m_chartView->setRenderHint(QPainter::Antialiasing, true);
   // m_chartView->setMaximumSize(800,450);
    gridLayout_graph->addWidget(m_chartView);
}

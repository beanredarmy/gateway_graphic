#include "detailwidget.h"

DetailWidget::DetailWidget(QWidget *parent) : QWidget(parent)
{

    QGridLayout *gridLayout_2 = new QGridLayout(this);
    gridLayout_2->setSpacing(6);
    gridLayout_2->setContentsMargins(11, 11, 11, 11);
    gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
    QFrame *frame_option = new QFrame(this);
    frame_option->setObjectName(QStringLiteral("frame_option"));
    QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Minimum);
    sizePolicy4.setHorizontalStretch(0);
    sizePolicy4.setVerticalStretch(0);
    sizePolicy4.setHeightForWidth(frame_option->sizePolicy().hasHeightForWidth());
    frame_option->setSizePolicy(sizePolicy4);
    frame_option->setFrameShape(QFrame::StyledPanel);
    frame_option->setFrameShadow(QFrame::Raised);
    QGridLayout *gridLayout_6 = new QGridLayout(frame_option);
    gridLayout_6->setSpacing(6);
    gridLayout_6->setContentsMargins(11, 11, 11, 11);
    gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
    QVBoxLayout *verticalLayout_3 = new QVBoxLayout();
    verticalLayout_3->setSpacing(6);
    verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
    QLabel *label_16 = new QLabel(frame_option);
    label_16->setObjectName(QStringLiteral("label_16"));
    label_16->setAlignment(Qt::AlignCenter);
    verticalLayout_3->addWidget(label_16);

    QHBoxLayout *horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setSpacing(6);
    horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
    QLabel *label_2 = new QLabel(frame_option);
    label_2->setObjectName(QStringLiteral("label_2"));
    QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
    sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
    label_2->setSizePolicy(sizePolicy1);

    horizontalLayout_2->addWidget(label_2);

    QComboBox *cmbBox_index = new QComboBox(frame_option);
    cmbBox_index->setObjectName(QStringLiteral("cmbBox_index"));
    QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
    sizePolicy2.setHeightForWidth(cmbBox_index->sizePolicy().hasHeightForWidth());
    cmbBox_index->setSizePolicy(sizePolicy2);

    horizontalLayout_2->addWidget(cmbBox_index);


    verticalLayout_3->addLayout(horizontalLayout_2);

    QHBoxLayout *horizontalLayout_6 = new QHBoxLayout();
    horizontalLayout_6->setSpacing(6);
    horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
    horizontalLayout_6->setSizeConstraint(QLayout::SetFixedSize);
    QLabel *label_7 = new QLabel(frame_option);
    label_7->setObjectName(QStringLiteral("label_7"));
    sizePolicy1.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
    label_7->setSizePolicy(sizePolicy1);

    horizontalLayout_6->addWidget(label_7);

    QComboBox *cmbBox_place = new QComboBox(frame_option);
    cmbBox_place->setObjectName(QStringLiteral("cmbBox_place"));
    sizePolicy2.setHeightForWidth(cmbBox_place->sizePolicy().hasHeightForWidth());
    cmbBox_place->setSizePolicy(sizePolicy2);
    cmbBox_place->setEditable(false);

    horizontalLayout_6->addWidget(cmbBox_place);


    verticalLayout_3->addLayout(horizontalLayout_6);

    QHBoxLayout *horizontalLayout_13 = new QHBoxLayout();
    horizontalLayout_13->setSpacing(6);
    horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
    QLabel *label_13 = new QLabel(frame_option);
    label_13->setObjectName(QStringLiteral("label_13"));
    sizePolicy1.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
    label_13->setSizePolicy(sizePolicy1);

    horizontalLayout_13->addWidget(label_13);

    QComboBox *cmbBox_dateMode = new QComboBox(frame_option);
    cmbBox_dateMode->setObjectName(QStringLiteral("cmbBox_dateMode"));
    sizePolicy2.setHeightForWidth(cmbBox_dateMode->sizePolicy().hasHeightForWidth());
    cmbBox_dateMode->setSizePolicy(sizePolicy2);

    horizontalLayout_13->addWidget(cmbBox_dateMode);


    verticalLayout_3->addLayout(horizontalLayout_13);

    QHBoxLayout *horizontalLayout_7 = new QHBoxLayout();
    horizontalLayout_7->setSpacing(6);
    horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
    horizontalLayout_7->setSizeConstraint(QLayout::SetFixedSize);
    QLabel *label_8 = new QLabel(frame_option);
    label_8->setObjectName(QStringLiteral("label_8"));
    sizePolicy1.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
    label_8->setSizePolicy(sizePolicy1);

    horizontalLayout_7->addWidget(label_8);

    QDateTimeEdit *dateEdit_date = new QDateTimeEdit(frame_option);
    dateEdit_date->setObjectName(QStringLiteral("dateEdit_date"));

    horizontalLayout_7->addWidget(dateEdit_date);


    verticalLayout_3->addLayout(horizontalLayout_7);

    QPushButton *pushButton_OK = new QPushButton(frame_option);
    pushButton_OK->setObjectName(QStringLiteral("pushButton_OK"));
    sizePolicy2.setHeightForWidth(pushButton_OK->sizePolicy().hasHeightForWidth());
    pushButton_OK->setSizePolicy(sizePolicy2);
    pushButton_OK->setLayoutDirection(Qt::LeftToRight);

    verticalLayout_3->addWidget(pushButton_OK);

    QPushButton *pushButton_viewNow = new QPushButton(frame_option);
    pushButton_viewNow->setObjectName(QStringLiteral("pushButton_viewNow"));

    verticalLayout_3->addWidget(pushButton_viewNow);

    QFrame *line = new QFrame(frame_option);
    line->setObjectName(QStringLiteral("line"));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    verticalLayout_3->addWidget(line);

    QLabel *label_15 = new QLabel(frame_option);
    label_15->setObjectName(QStringLiteral("label_15"));
    label_15->setAlignment(Qt::AlignCenter);

    verticalLayout_3->addWidget(label_15);

    QHBoxLayout *horizontalLayout_14 = new QHBoxLayout();
    horizontalLayout_14->setSpacing(6);
    horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
    QLabel *label_19 = new QLabel(frame_option);
    label_19->setObjectName(QStringLiteral("label_19"));
    sizePolicy1.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
    label_19->setSizePolicy(sizePolicy1);

    horizontalLayout_14->addWidget(label_19);

    QComboBox *cmbBox_place2 = new QComboBox(frame_option);
    cmbBox_place2->setObjectName(QStringLiteral("cmbBox_place2"));
    sizePolicy2.setHeightForWidth(cmbBox_place2->sizePolicy().hasHeightForWidth());
    cmbBox_place2->setSizePolicy(sizePolicy2);

    horizontalLayout_14->addWidget(cmbBox_place2);


    verticalLayout_3->addLayout(horizontalLayout_14);

    QHBoxLayout *horizontalLayout_15 = new QHBoxLayout();
    horizontalLayout_15->setSpacing(6);
    horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
    horizontalLayout_15->setSizeConstraint(QLayout::SetFixedSize);
    QLabel *label_17 = new QLabel(frame_option);
    label_17->setObjectName(QStringLiteral("label_17"));
    sizePolicy1.setHeightForWidth(label_17->sizePolicy().hasHeightForWidth());
    label_17->setSizePolicy(sizePolicy1);

    horizontalLayout_15->addWidget(label_17);

    QDateTimeEdit *dateEdit_date2 = new QDateTimeEdit(frame_option);
    dateEdit_date2->setObjectName(QStringLiteral("dateEdit_date2"));

    horizontalLayout_15->addWidget(dateEdit_date2);


    verticalLayout_3->addLayout(horizontalLayout_15);

    QHBoxLayout *horizontalLayout_18 = new QHBoxLayout();
    horizontalLayout_18->setSpacing(6);
    horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
    QLabel *label_20 = new QLabel(frame_option);
    label_20->setObjectName(QStringLiteral("label_20"));
    sizePolicy1.setHeightForWidth(label_20->sizePolicy().hasHeightForWidth());
    label_20->setSizePolicy(sizePolicy1);

    horizontalLayout_18->addWidget(label_20);

    QComboBox *cmbBox_place3 = new QComboBox(frame_option);
    cmbBox_place3->setObjectName(QStringLiteral("cmbBox_place3"));
    sizePolicy2.setHeightForWidth(cmbBox_place3->sizePolicy().hasHeightForWidth());
    cmbBox_place3->setSizePolicy(sizePolicy2);

    horizontalLayout_18->addWidget(cmbBox_place3);


    verticalLayout_3->addLayout(horizontalLayout_18);

    QHBoxLayout *horizontalLayout_16 = new QHBoxLayout();
    horizontalLayout_16->setSpacing(6);
    horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
    horizontalLayout_16->setSizeConstraint(QLayout::SetFixedSize);
    QLabel *label_18 = new QLabel(frame_option);
    label_18->setObjectName(QStringLiteral("label_18"));
    sizePolicy1.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
    label_18->setSizePolicy(sizePolicy1);

    horizontalLayout_16->addWidget(label_18);

    QDateTimeEdit *dateEdit_date3 = new QDateTimeEdit(frame_option);
    dateEdit_date3->setObjectName(QStringLiteral("dateEdit_date3"));

    horizontalLayout_16->addWidget(dateEdit_date3);


    verticalLayout_3->addLayout(horizontalLayout_16);

    QHBoxLayout *horizontalLayout_17 = new QHBoxLayout();
    horizontalLayout_17->setSpacing(6);
    horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
    QPushButton *pushBtn_compare = new QPushButton(frame_option);
    pushBtn_compare->setObjectName(QStringLiteral("pushBtn_compare"));
    QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Minimum);
    sizePolicy5.setHorizontalStretch(0);
    sizePolicy5.setVerticalStretch(0);
    sizePolicy5.setHeightForWidth(pushBtn_compare->sizePolicy().hasHeightForWidth());
    pushBtn_compare->setSizePolicy(sizePolicy5);

    horizontalLayout_17->addWidget(pushBtn_compare);

    QPushButton *pushBtn_notCompare = new QPushButton(frame_option);
    pushBtn_notCompare->setObjectName(QStringLiteral("pushBtn_notCompare"));
    sizePolicy2.setHeightForWidth(pushBtn_notCompare->sizePolicy().hasHeightForWidth());
    pushBtn_notCompare->setSizePolicy(sizePolicy2);

    horizontalLayout_17->addWidget(pushBtn_notCompare);


    verticalLayout_3->addLayout(horizontalLayout_17);

    QFrame *line_2 = new QFrame(frame_option);
    line_2->setObjectName(QStringLiteral("line_2"));
    line_2->setFrameShape(QFrame::HLine);
    line_2->setFrameShadow(QFrame::Sunken);

    verticalLayout_3->addWidget(line_2);

    QLabel *label_21 = new QLabel(frame_option);
    label_21->setObjectName(QStringLiteral("label_21"));
    label_21->setAlignment(Qt::AlignCenter);

    verticalLayout_3->addWidget(label_21);

    QHBoxLayout *horizontalLayout_19 = new QHBoxLayout();
    horizontalLayout_19->setSpacing(6);
    horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
    QLabel *label_22 = new QLabel(frame_option);
    label_22->setObjectName(QStringLiteral("label_22"));
    sizePolicy1.setHeightForWidth(label_22->sizePolicy().hasHeightForWidth());
    label_22->setSizePolicy(sizePolicy1);

    horizontalLayout_19->addWidget(label_22);

    QSlider *horizontalSlider = new QSlider(frame_option);
    horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
    sizePolicy2.setHeightForWidth(horizontalSlider->sizePolicy().hasHeightForWidth());
    horizontalSlider->setSizePolicy(sizePolicy2);
    horizontalSlider->setOrientation(Qt::Horizontal);

    horizontalLayout_19->addWidget(horizontalSlider);


    verticalLayout_3->addLayout(horizontalLayout_19);

    QHBoxLayout *horizontalLayout_12 = new QHBoxLayout();
    horizontalLayout_12->setSpacing(6);
    horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
    horizontalLayout_12->setSizeConstraint(QLayout::SetFixedSize);
    QLabel *label_14 = new QLabel(frame_option);
    label_14->setObjectName(QStringLiteral("label_14"));
    sizePolicy1.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
    label_14->setSizePolicy(sizePolicy1);

    horizontalLayout_12->addWidget(label_14);

    QComboBox *cmbBox_graphMode = new QComboBox(frame_option);
    cmbBox_graphMode->setObjectName(QStringLiteral("cmbBox_graphMode"));
    sizePolicy2.setHeightForWidth(cmbBox_graphMode->sizePolicy().hasHeightForWidth());
    cmbBox_graphMode->setSizePolicy(sizePolicy2);

    horizontalLayout_12->addWidget(cmbBox_graphMode);


    verticalLayout_3->addLayout(horizontalLayout_12);

    QHBoxLayout *horizontalLayout_20 = new QHBoxLayout();
    horizontalLayout_20->setSpacing(6);
    horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
    QLabel *label_23 = new QLabel(frame_option);
    label_23->setObjectName(QStringLiteral("label_23"));
    sizePolicy1.setHeightForWidth(label_23->sizePolicy().hasHeightForWidth());
    label_23->setSizePolicy(sizePolicy1);

    horizontalLayout_20->addWidget(label_23);

    QComboBox *cmbBox_theme = new QComboBox(frame_option);
    cmbBox_theme->setObjectName(QStringLiteral("cmbBox_theme"));
    sizePolicy2.setHeightForWidth(cmbBox_theme->sizePolicy().hasHeightForWidth());
    cmbBox_theme->setSizePolicy(sizePolicy2);

    horizontalLayout_20->addWidget(cmbBox_theme);


    verticalLayout_3->addLayout(horizontalLayout_20);


    gridLayout_6->addLayout(verticalLayout_3, 0, 0, 1, 1);

    QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout_6->addItem(verticalSpacer, 1, 0, 1, 1);


    gridLayout_2->addWidget(frame_option, 0, 2, 1, 1);

    QFrame *frame_content = new QFrame(this);
    frame_content->setObjectName(QStringLiteral("frame_content"));
    sizePolicy5.setHeightForWidth(frame_content->sizePolicy().hasHeightForWidth());
    frame_content->setSizePolicy(sizePolicy5);
    frame_content->setFrameShape(QFrame::StyledPanel);
    frame_content->setFrameShadow(QFrame::Raised);
    QGridLayout *gridLayout_5 = new QGridLayout(frame_content);
    gridLayout_5->setSpacing(6);
    gridLayout_5->setContentsMargins(11, 11, 11, 11);
    gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
    QHBoxLayout *horizontalLayout_11 = new QHBoxLayout();
    horizontalLayout_11->setSpacing(6);
    horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
    QHBoxLayout *horizontalLayout_8 = new QHBoxLayout();
    horizontalLayout_8->setSpacing(6);
    horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
    QLabel *label_9 = new QLabel(frame_content);
    label_9->setObjectName(QStringLiteral("label_9"));
    QSizePolicy sizePolicy6(QSizePolicy::Maximum, QSizePolicy::Maximum);
    sizePolicy6.setHorizontalStretch(0);
    sizePolicy6.setVerticalStretch(0);
    sizePolicy6.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
    label_9->setSizePolicy(sizePolicy6);

    horizontalLayout_8->addWidget(label_9);

    QLCDNumber *lcdNumber_curValue = new QLCDNumber(frame_content);
    lcdNumber_curValue->setObjectName(QStringLiteral("lcdNumber_curValue"));
    sizePolicy6.setHeightForWidth(lcdNumber_curValue->sizePolicy().hasHeightForWidth());
    lcdNumber_curValue->setSizePolicy(sizePolicy6);

    horizontalLayout_8->addWidget(lcdNumber_curValue);


    horizontalLayout_11->addLayout(horizontalLayout_8);

    QSpacerItem *horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

    horizontalLayout_11->addItem(horizontalSpacer);

    QHBoxLayout *horizontalLayout_9 = new QHBoxLayout();
    horizontalLayout_9->setSpacing(6);
    horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
    QLabel *label_10 = new QLabel(frame_content);
    label_10->setObjectName(QStringLiteral("label_10"));
    sizePolicy6.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
    label_10->setSizePolicy(sizePolicy6);

    horizontalLayout_9->addWidget(label_10);

    QLCDNumber *lcdNumber_aveValue = new QLCDNumber(frame_content);
    lcdNumber_aveValue->setObjectName(QStringLiteral("lcdNumber_aveValue"));
    sizePolicy6.setHeightForWidth(lcdNumber_aveValue->sizePolicy().hasHeightForWidth());
    lcdNumber_aveValue->setSizePolicy(sizePolicy6);

    horizontalLayout_9->addWidget(lcdNumber_aveValue);


    horizontalLayout_11->addLayout(horizontalLayout_9);

    QSpacerItem *horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

    horizontalLayout_11->addItem(horizontalSpacer_2);

    QHBoxLayout *horizontalLayout_10 = new QHBoxLayout();
    horizontalLayout_10->setSpacing(6);
    horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
    QLabel *label_11 = new QLabel(frame_content);
    label_11->setObjectName(QStringLiteral("label_11"));
    sizePolicy6.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
    label_11->setSizePolicy(sizePolicy6);

    horizontalLayout_10->addWidget(label_11);

    QLCDNumber *lcdNumber_minValue = new QLCDNumber(frame_content);
    lcdNumber_minValue->setObjectName(QStringLiteral("lcdNumber_minValue"));
    sizePolicy6.setHeightForWidth(lcdNumber_minValue->sizePolicy().hasHeightForWidth());
    lcdNumber_minValue->setSizePolicy(sizePolicy6);

    horizontalLayout_10->addWidget(lcdNumber_minValue);

    QLabel *label_12 = new QLabel(frame_content);
    label_12->setObjectName(QStringLiteral("label_12"));
    sizePolicy6.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
    label_12->setSizePolicy(sizePolicy6);

    horizontalLayout_10->addWidget(label_12);

    QLCDNumber *lcdNumber_maxValue = new QLCDNumber(frame_content);
    lcdNumber_maxValue->setObjectName(QStringLiteral("lcdNumber_maxValue"));
    sizePolicy6.setHeightForWidth(lcdNumber_maxValue->sizePolicy().hasHeightForWidth());
    lcdNumber_maxValue->setSizePolicy(sizePolicy6);

    horizontalLayout_10->addWidget(lcdNumber_maxValue);


    horizontalLayout_11->addLayout(horizontalLayout_10);


    gridLayout_5->addLayout(horizontalLayout_11, 0, 0, 1, 1);

    QGridLayout *gridLayout_graph = new QGridLayout();
    gridLayout_graph->setSpacing(6);
    gridLayout_graph->setObjectName(QStringLiteral("gridLayout_graph"));

    gridLayout_5->addLayout(gridLayout_graph, 1, 0, 1, 1);


    gridLayout_2->addWidget(frame_content, 0, 0, 1, 1);
    label_16->setText(QApplication::translate("MainWindow", "\304\220\341\273\222 TH\341\273\212 CH\303\215NH", nullptr));
    label_2->setText(QApplication::translate("MainWindow", "Th\303\264ng s\341\273\221", nullptr));
    label_7->setText(QApplication::translate("MainWindow", "\304\220\341\273\213a \304\221i\341\273\203m", nullptr));
    cmbBox_place->setCurrentText(QString());
    label_13->setText(QApplication::translate("MainWindow", "Theo th\341\273\235i gian", nullptr));
    label_8->setText(QApplication::translate("MainWindow", "Ng\303\240y", nullptr));
    pushButton_OK->setText(QApplication::translate("MainWindow", "OK", nullptr));
    pushButton_viewNow->setText(QApplication::translate("MainWindow", "Xem hi\341\273\207n t\341\272\241i", nullptr));
    label_15->setText(QApplication::translate("MainWindow", "SO S\303\201NH", nullptr));
    label_19->setText(QApplication::translate("MainWindow", "\304\220\341\273\213a \304\221i\341\273\203m 2", nullptr));
    label_17->setText(QApplication::translate("MainWindow", "Ng\303\240y 2", nullptr));
    label_20->setText(QApplication::translate("MainWindow", "\304\220\341\273\213a \304\221i\341\273\203m 3", nullptr));
    label_18->setText(QApplication::translate("MainWindow", "Ng\303\240y 3", nullptr));
    pushBtn_compare->setText(QApplication::translate("MainWindow", "So s\303\241nh", nullptr));
    pushBtn_notCompare->setText(QApplication::translate("MainWindow", "\341\272\250n so s\303\241nh", nullptr));
    label_21->setText(QApplication::translate("MainWindow", "T\303\231Y CH\341\273\214N", nullptr));
    label_22->setText(QApplication::translate("MainWindow", "Zoom", nullptr));
    label_14->setText(QApplication::translate("MainWindow", "Ki\341\273\203u \304\221\341\273\223 th\341\273\213", nullptr));
    label_23->setText(QApplication::translate("MainWindow", "Theme", nullptr));
    label_9->setText(QApplication::translate("MainWindow", "Hi\341\273\207n t\341\272\241i", nullptr));
    label_10->setText(QApplication::translate("MainWindow", "Trung b\303\254nh", nullptr));
    label_11->setText(QApplication::translate("MainWindow", "Min/Max", nullptr));
    label_12->setText(QApplication::translate("MainWindow", "/", nullptr));
}

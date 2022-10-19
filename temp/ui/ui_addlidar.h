/********************************************************************************
** Form generated from reading UI file 'addlidar.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDLIDAR_H
#define UI_ADDLIDAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <childtitlebar.h>

QT_BEGIN_NAMESPACE

class Ui_AddLidar
{
public:
    QGridLayout *gridLayout_6;
    ChildTitleBar *widget;
    QWidget *widget_2;
    QGridLayout *gridLayout_5;
    QVBoxLayout *verticalLayout_10;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_26;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLineEdit *JAngle;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *JDis;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_6;
    QLineEdit *setradius;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_9;
    QLineEdit *XAngle;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QLineEdit *base_x;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *YAngle;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QLineEdit *base_y;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_27;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_7;
    QLineEdit *clusterTolerance;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_11;
    QLineEdit *resolution;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_12;
    QLineEdit *difference_threshold;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_8;
    QLineEdit *minClusterSize;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_10;
    QLineEdit *maxClusterSize;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_33;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_13;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_28;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_30;
    QLabel *label_26;
    QLineEdit *view_x;
    QHBoxLayout *horizontalLayout_31;
    QLabel *label_27;
    QLineEdit *view_y;
    QHBoxLayout *horizontalLayout_32;
    QLabel *label_28;
    QLineEdit *view_z;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_21;
    QLineEdit *pos_x;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_16;
    QLineEdit *pos_y;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_22;
    QLineEdit *pos_z;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_14;
    QLineEdit *up_x;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_15;
    QLineEdit *up_y;
    QHBoxLayout *horizontalLayout_24;
    QLabel *label_23;
    QLineEdit *up_z;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_34;
    QHBoxLayout *horizontalLayout_29;
    QLabel *label_25;
    QLineEdit *lidarPort;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_24;
    QLineEdit *ledIp;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btn_sure;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_no;
    QFrame *line;

    void setupUi(QDialog *AddLidar)
    {
        if (AddLidar->objectName().isEmpty())
            AddLidar->setObjectName(QString::fromUtf8("AddLidar"));
        AddLidar->resize(651, 690);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AddLidar->sizePolicy().hasHeightForWidth());
        AddLidar->setSizePolicy(sizePolicy);
        gridLayout_6 = new QGridLayout(AddLidar);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setHorizontalSpacing(0);
        gridLayout_6->setVerticalSpacing(6);
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        widget = new ChildTitleBar(AddLidar);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 30));
        widget->setMaximumSize(QSize(16777215, 30));

        gridLayout_6->addWidget(widget, 0, 0, 1, 1);

        widget_2 = new QWidget(AddLidar);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        gridLayout_5 = new QGridLayout(widget_2);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox = new QGroupBox(widget_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_4);

        JAngle = new QLineEdit(groupBox);
        JAngle->setObjectName(QString::fromUtf8("JAngle"));
        JAngle->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(JAngle);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 2);

        verticalLayout_5->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_2);

        JDis = new QLineEdit(groupBox);
        JDis->setObjectName(QString::fromUtf8("JDis"));
        JDis->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(JDis);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 2);

        verticalLayout_5->addLayout(horizontalLayout);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_7->addWidget(label_6);

        setradius = new QLineEdit(groupBox);
        setradius->setObjectName(QString::fromUtf8("setradius"));
        setradius->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(setradius);

        horizontalLayout_7->setStretch(0, 1);
        horizontalLayout_7->setStretch(1, 2);

        verticalLayout_5->addLayout(horizontalLayout_7);


        horizontalLayout_26->addLayout(verticalLayout_5);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_3->addWidget(label_9);

        XAngle = new QLineEdit(groupBox);
        XAngle->setObjectName(QString::fromUtf8("XAngle"));
        XAngle->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(XAngle);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_5->addWidget(label);

        base_x = new QLineEdit(groupBox);
        base_x->setObjectName(QString::fromUtf8("base_x"));
        base_x->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(base_x);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_3);

        YAngle = new QLineEdit(groupBox);
        YAngle->setObjectName(QString::fromUtf8("YAngle"));
        YAngle->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(YAngle);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_6->addWidget(label_5);

        base_y = new QLineEdit(groupBox);
        base_y->setObjectName(QString::fromUtf8("base_y"));
        base_y->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(base_y);

        horizontalLayout_6->setStretch(0, 1);
        horizontalLayout_6->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout_6);


        horizontalLayout_26->addLayout(verticalLayout);


        gridLayout_3->addLayout(horizontalLayout_26, 0, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(widget_2);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_8->addWidget(label_7);

        clusterTolerance = new QLineEdit(groupBox_2);
        clusterTolerance->setObjectName(QString::fromUtf8("clusterTolerance"));
        clusterTolerance->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(clusterTolerance);

        horizontalLayout_8->setStretch(0, 1);
        horizontalLayout_8->setStretch(1, 2);

        verticalLayout_6->addLayout(horizontalLayout_8);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_11->addWidget(label_11);

        resolution = new QLineEdit(groupBox_2);
        resolution->setObjectName(QString::fromUtf8("resolution"));
        resolution->setAlignment(Qt::AlignCenter);

        horizontalLayout_11->addWidget(resolution);

        horizontalLayout_11->setStretch(0, 1);
        horizontalLayout_11->setStretch(1, 2);

        verticalLayout_6->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_12->addWidget(label_12);

        difference_threshold = new QLineEdit(groupBox_2);
        difference_threshold->setObjectName(QString::fromUtf8("difference_threshold"));
        difference_threshold->setAlignment(Qt::AlignCenter);

        horizontalLayout_12->addWidget(difference_threshold);

        horizontalLayout_12->setStretch(0, 1);
        horizontalLayout_12->setStretch(1, 2);

        verticalLayout_6->addLayout(horizontalLayout_12);


        horizontalLayout_27->addLayout(verticalLayout_6);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_9->addWidget(label_8);

        minClusterSize = new QLineEdit(groupBox_2);
        minClusterSize->setObjectName(QString::fromUtf8("minClusterSize"));
        minClusterSize->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(minClusterSize);

        horizontalLayout_9->setStretch(0, 1);
        horizontalLayout_9->setStretch(1, 2);

        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_10->addWidget(label_10);

        maxClusterSize = new QLineEdit(groupBox_2);
        maxClusterSize->setObjectName(QString::fromUtf8("maxClusterSize"));
        maxClusterSize->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(maxClusterSize);

        horizontalLayout_10->setStretch(0, 1);
        horizontalLayout_10->setStretch(1, 2);

        verticalLayout_2->addLayout(horizontalLayout_10);


        horizontalLayout_27->addLayout(verticalLayout_2);


        gridLayout_4->addLayout(horizontalLayout_27, 0, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(widget_2);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout_33 = new QHBoxLayout();
        horizontalLayout_33->setObjectName(QString::fromUtf8("horizontalLayout_33"));
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_13 = new QLabel(groupBox_3);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_14->addWidget(label_13);

        comboBox = new QComboBox(groupBox_3);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout_14->addWidget(comboBox);

        horizontalLayout_14->setStretch(0, 1);
        horizontalLayout_14->setStretch(1, 2);

        horizontalLayout_33->addLayout(horizontalLayout_14);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_33->addItem(horizontalSpacer_2);


        verticalLayout_9->addLayout(horizontalLayout_33);

        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setObjectName(QString::fromUtf8("horizontalLayout_28"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_30 = new QHBoxLayout();
        horizontalLayout_30->setObjectName(QString::fromUtf8("horizontalLayout_30"));
        label_26 = new QLabel(groupBox_3);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        horizontalLayout_30->addWidget(label_26);

        view_x = new QLineEdit(groupBox_3);
        view_x->setObjectName(QString::fromUtf8("view_x"));
        view_x->setAlignment(Qt::AlignCenter);

        horizontalLayout_30->addWidget(view_x);

        horizontalLayout_30->setStretch(0, 1);
        horizontalLayout_30->setStretch(1, 2);

        verticalLayout_4->addLayout(horizontalLayout_30);

        horizontalLayout_31 = new QHBoxLayout();
        horizontalLayout_31->setObjectName(QString::fromUtf8("horizontalLayout_31"));
        label_27 = new QLabel(groupBox_3);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        horizontalLayout_31->addWidget(label_27);

        view_y = new QLineEdit(groupBox_3);
        view_y->setObjectName(QString::fromUtf8("view_y"));
        view_y->setAlignment(Qt::AlignCenter);

        horizontalLayout_31->addWidget(view_y);

        horizontalLayout_31->setStretch(0, 1);
        horizontalLayout_31->setStretch(1, 2);

        verticalLayout_4->addLayout(horizontalLayout_31);

        horizontalLayout_32 = new QHBoxLayout();
        horizontalLayout_32->setObjectName(QString::fromUtf8("horizontalLayout_32"));
        label_28 = new QLabel(groupBox_3);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        horizontalLayout_32->addWidget(label_28);

        view_z = new QLineEdit(groupBox_3);
        view_z->setObjectName(QString::fromUtf8("view_z"));
        view_z->setAlignment(Qt::AlignCenter);

        horizontalLayout_32->addWidget(view_z);

        horizontalLayout_32->setStretch(0, 1);
        horizontalLayout_32->setStretch(1, 2);

        verticalLayout_4->addLayout(horizontalLayout_32);


        horizontalLayout_28->addLayout(verticalLayout_4);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        label_21 = new QLabel(groupBox_3);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        horizontalLayout_22->addWidget(label_21);

        pos_x = new QLineEdit(groupBox_3);
        pos_x->setObjectName(QString::fromUtf8("pos_x"));
        pos_x->setAlignment(Qt::AlignCenter);

        horizontalLayout_22->addWidget(pos_x);

        horizontalLayout_22->setStretch(0, 1);
        horizontalLayout_22->setStretch(1, 2);

        verticalLayout_8->addLayout(horizontalLayout_22);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        label_16 = new QLabel(groupBox_3);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        horizontalLayout_17->addWidget(label_16);

        pos_y = new QLineEdit(groupBox_3);
        pos_y->setObjectName(QString::fromUtf8("pos_y"));
        pos_y->setAlignment(Qt::AlignCenter);

        horizontalLayout_17->addWidget(pos_y);

        horizontalLayout_17->setStretch(0, 1);
        horizontalLayout_17->setStretch(1, 2);

        verticalLayout_8->addLayout(horizontalLayout_17);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        label_22 = new QLabel(groupBox_3);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        horizontalLayout_23->addWidget(label_22);

        pos_z = new QLineEdit(groupBox_3);
        pos_z->setObjectName(QString::fromUtf8("pos_z"));
        pos_z->setAlignment(Qt::AlignCenter);

        horizontalLayout_23->addWidget(pos_z);

        horizontalLayout_23->setStretch(0, 1);
        horizontalLayout_23->setStretch(1, 2);

        verticalLayout_8->addLayout(horizontalLayout_23);


        horizontalLayout_28->addLayout(verticalLayout_8);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_14 = new QLabel(groupBox_3);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_15->addWidget(label_14);

        up_x = new QLineEdit(groupBox_3);
        up_x->setObjectName(QString::fromUtf8("up_x"));
        up_x->setAlignment(Qt::AlignCenter);

        horizontalLayout_15->addWidget(up_x);

        horizontalLayout_15->setStretch(0, 1);
        horizontalLayout_15->setStretch(1, 2);

        verticalLayout_7->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_15 = new QLabel(groupBox_3);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        horizontalLayout_16->addWidget(label_15);

        up_y = new QLineEdit(groupBox_3);
        up_y->setObjectName(QString::fromUtf8("up_y"));
        up_y->setAlignment(Qt::AlignCenter);

        horizontalLayout_16->addWidget(up_y);

        horizontalLayout_16->setStretch(0, 1);
        horizontalLayout_16->setStretch(1, 2);

        verticalLayout_7->addLayout(horizontalLayout_16);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        label_23 = new QLabel(groupBox_3);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        horizontalLayout_24->addWidget(label_23);

        up_z = new QLineEdit(groupBox_3);
        up_z->setObjectName(QString::fromUtf8("up_z"));
        up_z->setAlignment(Qt::AlignCenter);

        horizontalLayout_24->addWidget(up_z);

        horizontalLayout_24->setStretch(0, 1);
        horizontalLayout_24->setStretch(1, 2);

        verticalLayout_7->addLayout(horizontalLayout_24);


        horizontalLayout_28->addLayout(verticalLayout_7);


        verticalLayout_9->addLayout(horizontalLayout_28);


        gridLayout->addLayout(verticalLayout_9, 1, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(widget_2);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_2 = new QGridLayout(groupBox_4);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_34 = new QHBoxLayout();
        horizontalLayout_34->setObjectName(QString::fromUtf8("horizontalLayout_34"));
        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setObjectName(QString::fromUtf8("horizontalLayout_29"));
        label_25 = new QLabel(groupBox_4);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        horizontalLayout_29->addWidget(label_25);

        lidarPort = new QLineEdit(groupBox_4);
        lidarPort->setObjectName(QString::fromUtf8("lidarPort"));
        lidarPort->setAlignment(Qt::AlignCenter);

        horizontalLayout_29->addWidget(lidarPort);

        horizontalLayout_29->setStretch(0, 1);
        horizontalLayout_29->setStretch(1, 2);

        horizontalLayout_34->addLayout(horizontalLayout_29);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        label_24 = new QLabel(groupBox_4);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        horizontalLayout_25->addWidget(label_24);

        ledIp = new QLineEdit(groupBox_4);
        ledIp->setObjectName(QString::fromUtf8("ledIp"));
        ledIp->setAlignment(Qt::AlignCenter);

        horizontalLayout_25->addWidget(ledIp);

        horizontalLayout_25->setStretch(0, 1);
        horizontalLayout_25->setStretch(1, 2);

        horizontalLayout_34->addLayout(horizontalLayout_25);


        gridLayout_2->addLayout(horizontalLayout_34, 1, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox_4);


        verticalLayout_10->addLayout(verticalLayout_3);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_3);

        btn_sure = new QPushButton(widget_2);
        btn_sure->setObjectName(QString::fromUtf8("btn_sure"));

        horizontalLayout_13->addWidget(btn_sure);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer);

        btn_no = new QPushButton(widget_2);
        btn_no->setObjectName(QString::fromUtf8("btn_no"));

        horizontalLayout_13->addWidget(btn_no);

        horizontalLayout_13->setStretch(0, 2);

        verticalLayout_10->addLayout(horizontalLayout_13);


        gridLayout_5->addLayout(verticalLayout_10, 0, 0, 1, 1);


        gridLayout_6->addWidget(widget_2, 2, 0, 1, 1);

        line = new QFrame(AddLidar);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_6->addWidget(line, 1, 0, 1, 1);


        retranslateUi(AddLidar);

        QMetaObject::connectSlotsByName(AddLidar);
    } // setupUi

    void retranslateUi(QDialog *AddLidar)
    {
        AddLidar->setWindowTitle(QCoreApplication::translate("AddLidar", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("AddLidar", "\347\233\270\346\234\272\345\217\202\346\225\260", nullptr));
        label_4->setText(QCoreApplication::translate("AddLidar", "\351\242\204\347\275\256\347\202\271\350\247\222\345\272\246(\345\272\246)", nullptr));
        label_2->setText(QCoreApplication::translate("AddLidar", "\347\233\221\346\216\247\350\214\203\345\233\264(m)", nullptr));
        label_6->setText(QCoreApplication::translate("AddLidar", "\346\265\213\351\207\217\350\267\235\347\246\273(m)", nullptr));
        label_9->setText(QCoreApplication::translate("AddLidar", "X\346\226\271\345\220\221(\350\247\222\345\272\246)", nullptr));
        label->setText(QCoreApplication::translate("AddLidar", "X \350\275\264\347\233\270\350\267\235(m)", nullptr));
        label_3->setText(QCoreApplication::translate("AddLidar", "Y\346\226\271\345\220\221(\350\247\222\345\272\246)", nullptr));
        label_5->setText(QCoreApplication::translate("AddLidar", "Y\350\275\264\347\233\270\350\267\235(m)", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("AddLidar", "\350\201\232\347\261\273\345\217\202\346\225\260", nullptr));
        label_7->setText(QCoreApplication::translate("AddLidar", "\350\201\232\347\261\273\350\267\235\347\246\273", nullptr));
        label_11->setText(QCoreApplication::translate("AddLidar", "\346\240\205\346\240\274\345\244\247\345\260\217", nullptr));
        label_12->setText(QCoreApplication::translate("AddLidar", "\346\240\205\346\240\274\351\253\230\345\272\246\345\267\256", nullptr));
        label_8->setText(QCoreApplication::translate("AddLidar", "\350\201\232\347\261\273\346\234\200\345\260\217\347\202\271\346\225\260", nullptr));
        label_10->setText(QCoreApplication::translate("AddLidar", "\350\201\232\347\261\273\346\234\200\345\244\247\347\202\271\346\225\260", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("AddLidar", "\344\270\211\347\273\264\347\202\271\344\272\221\345\217\202\346\225\260", nullptr));
        label_13->setText(QCoreApplication::translate("AddLidar", "\351\233\267\350\276\276\345\236\213\345\217\267\357\274\232", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("AddLidar", "CH128X1", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("AddLidar", "C16", nullptr));

        label_26->setText(QCoreApplication::translate("AddLidar", "view_x", nullptr));
        label_27->setText(QCoreApplication::translate("AddLidar", "view_y", nullptr));
        label_28->setText(QCoreApplication::translate("AddLidar", "view_z", nullptr));
        label_21->setText(QCoreApplication::translate("AddLidar", "pos_x", nullptr));
        label_16->setText(QCoreApplication::translate("AddLidar", "pos_y", nullptr));
        label_22->setText(QCoreApplication::translate("AddLidar", "pos_z", nullptr));
        label_14->setText(QCoreApplication::translate("AddLidar", "up_x", nullptr));
        label_15->setText(QCoreApplication::translate("AddLidar", "up_y", nullptr));
        label_23->setText(QCoreApplication::translate("AddLidar", "up_z", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("AddLidar", "\345\205\266\344\273\226", nullptr));
        label_25->setText(QCoreApplication::translate("AddLidar", "\351\233\267\350\276\276\347\253\257\345\217\243", nullptr));
        label_24->setText(QCoreApplication::translate("AddLidar", "\346\212\245\350\255\246\347\201\257Ip", nullptr));
        btn_sure->setText(QCoreApplication::translate("AddLidar", "\347\241\256\350\256\244", nullptr));
        btn_no->setText(QCoreApplication::translate("AddLidar", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddLidar: public Ui_AddLidar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDLIDAR_H

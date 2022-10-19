/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <imageWidget.h>
#include <maintitlebar.h>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_14;
    QVBoxLayout *verticalLayout_6;
    MainTitleBar *widgetTitle;
    QHBoxLayout *horizontalLayout_11;
    ImageWidget *widget_2;
    QGridLayout *gridLayout_9;
    QFrame *frame;
    ImageWidget *video_widget;
    QGridLayout *gridLayout_7;
    QVTKWidget *qvtkWidget;
    QHBoxLayout *horizontalLayout_14;
    QHBoxLayout *horizontalLayout_10;
    ImageWidget *AreaConfigwidget;
    QGridLayout *gridLayout_6;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButton_addlidar;
    QPushButton *pushButton;
    QPushButton *pushButton_sms;
    ImageWidget *widget_5;
    QGridLayout *gridLayout_12;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_11;
    QGridLayout *gridLayout;
    QToolButton *toolButton_3;
    QToolButton *toolButton_left;
    QToolButton *toolButton;
    QToolButton *toolButton_2;
    QToolButton *toolButton_down;
    QToolButton *toolButton_right;
    QToolButton *toolButton_4;
    QToolButton *toolButton_up;
    QToolButton *toolButton_5;
    QToolButton *toolButton_6;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    ImageWidget *widget_4;
    QGridLayout *gridLayout_8;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_13;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_14;
    QToolButton *toolButton_savedata;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_20;
    QToolButton *toolButton_actionOpengrid;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_13;
    QToolButton *toolButton_Portlight;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_22;
    QToolButton *toolButton_sms;
    QFrame *line_3;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QToolButton *toolButton_7;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_21;
    QToolButton *toolButton_actionTrick;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QToolButton *toolButton_indoorlight;
    QHBoxLayout *horizontalLayout_13;
    ImageWidget *widget_3;
    QGridLayout *gridLayout_10;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_16;
    QGridLayout *gridLayout_4;
    QRadioButton *radioButton_Cluster_none;
    QRadioButton *radioButton_Cluster;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QFrame *line;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_9;
    QGridLayout *gridLayout_3;
    QRadioButton *radioButton_cloud_none;
    QRadioButton *radioButton_Cloud_all;
    QLabel *label_12;
    QRadioButton *radioButton_cloud_ob;
    QLabel *label_11;
    QLabel *label_10;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_8;
    QGridLayout *gridLayout_2;
    QRadioButton *radioButton_Area_none;
    QRadioButton *radioButton_Area_2d;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_15;
    ImageWidget *widget;
    QGridLayout *gridLayout_5;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_15;
    QTextEdit *textEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1328, 967);
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setStyleSheet(QString::fromUtf8(""));
        gridLayout_14 = new QGridLayout(centralWidget);
        gridLayout_14->setSpacing(0);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        gridLayout_14->setContentsMargins(0, 0, 0, 0);
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        widgetTitle = new MainTitleBar(centralWidget);
        widgetTitle->setObjectName(QString::fromUtf8("widgetTitle"));
        widgetTitle->setMinimumSize(QSize(0, 50));
        widgetTitle->setMaximumSize(QSize(16777215, 50));

        verticalLayout_6->addWidget(widgetTitle);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        widget_2 = new ImageWidget(centralWidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        gridLayout_9 = new QGridLayout(widget_2);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        frame = new QFrame(widget_2);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setLayoutDirection(Qt::LeftToRight);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        gridLayout_9->addWidget(frame, 0, 0, 1, 1);


        horizontalLayout_11->addWidget(widget_2);

        video_widget = new ImageWidget(centralWidget);
        video_widget->setObjectName(QString::fromUtf8("video_widget"));
        video_widget->setMaximumSize(QSize(16777215, 16777215));
        gridLayout_7 = new QGridLayout(video_widget);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        qvtkWidget = new QVTKWidget(video_widget);
        qvtkWidget->setObjectName(QString::fromUtf8("qvtkWidget"));

        gridLayout_7->addWidget(qvtkWidget, 0, 0, 1, 1);


        horizontalLayout_11->addWidget(video_widget);

        horizontalLayout_11->setStretch(0, 3);
        horizontalLayout_11->setStretch(1, 2);

        verticalLayout_6->addLayout(horizontalLayout_11);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        AreaConfigwidget = new ImageWidget(centralWidget);
        AreaConfigwidget->setObjectName(QString::fromUtf8("AreaConfigwidget"));
        AreaConfigwidget->setStyleSheet(QString::fromUtf8(""));
        gridLayout_6 = new QGridLayout(AreaConfigwidget);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        groupBox_2 = new QGroupBox(AreaConfigwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        pushButton_addlidar = new QPushButton(groupBox_2);
        pushButton_addlidar->setObjectName(QString::fromUtf8("pushButton_addlidar"));
        pushButton_addlidar->setStyleSheet(QString::fromUtf8("QPushButton:hover{\n"
"border:0px;\n"
"\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(), stop:1 rgba(157, 159, 162, 90));\n"
"/*background-color: rgba(157, 159, 162, 169);*/\n"
"}"));

        verticalLayout_3->addWidget(pushButton_addlidar);

        pushButton = new QPushButton(groupBox_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton:hover{\n"
"border:0px;\n"
"\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(), stop:1 rgba(157, 159, 162, 90));\n"
"	/*background-color: rgba(1, 64, 153, 169);*/\n"
"}"));

        verticalLayout_3->addWidget(pushButton);

        pushButton_sms = new QPushButton(groupBox_2);
        pushButton_sms->setObjectName(QString::fromUtf8("pushButton_sms"));
        pushButton_sms->setStyleSheet(QString::fromUtf8("QPushButton:hover{\n"
"border:0px;\n"
"\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(), stop:1 rgba(157, 159, 162, 90));\n"
"	/*background-color: rgba(1, 64, 153, 169);*/\n"
"}"));

        verticalLayout_3->addWidget(pushButton_sms);


        gridLayout_6->addWidget(groupBox_2, 2, 0, 1, 1);


        horizontalLayout_10->addWidget(AreaConfigwidget);

        widget_5 = new ImageWidget(centralWidget);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        gridLayout_12 = new QGridLayout(widget_5);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        groupBox_3 = new QGroupBox(widget_5);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setStyleSheet(QString::fromUtf8(""));
        gridLayout_11 = new QGridLayout(groupBox_3);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        toolButton_3 = new QToolButton(groupBox_3);
        toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));
        toolButton_3->setStyleSheet(QString::fromUtf8("QToolButton{\n"
"	border-image: url(:/images/reduce.png);\n"
"}\n"
"QToolButton:pressed{\n"
"	border-image: url(:/images/reduce_press.png);\n"
"}"));

        gridLayout->addWidget(toolButton_3, 4, 0, 1, 1);

        toolButton_left = new QToolButton(groupBox_3);
        toolButton_left->setObjectName(QString::fromUtf8("toolButton_left"));
        toolButton_left->setStyleSheet(QString::fromUtf8("background-image: url(:/images/add_left.png);"));

        gridLayout->addWidget(toolButton_left, 1, 0, 1, 1);

        toolButton = new QToolButton(groupBox_3);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setStyleSheet(QString::fromUtf8("QToolButton{\n"
"	border-image: url(:/images/reduce.png);\n"
"}\n"
"QToolButton:pressed{\n"
"	border-image: url(:/images/reduce_press.png);\n"
"}"));

        gridLayout->addWidget(toolButton, 3, 0, 1, 1);

        toolButton_2 = new QToolButton(groupBox_3);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
        toolButton_2->setStyleSheet(QString::fromUtf8("QToolButton{\n"
"	border-image: url(:/images/add.png);\n"
"}\n"
"QToolButton:pressed{\n"
"	border-image: url(:/images/add_press.png);\n"
"}"));

        gridLayout->addWidget(toolButton_2, 3, 2, 1, 1);

        toolButton_down = new QToolButton(groupBox_3);
        toolButton_down->setObjectName(QString::fromUtf8("toolButton_down"));
        toolButton_down->setStyleSheet(QString::fromUtf8("background-image: url(:/images/add_bottom.png);"));

        gridLayout->addWidget(toolButton_down, 2, 1, 1, 1);

        toolButton_right = new QToolButton(groupBox_3);
        toolButton_right->setObjectName(QString::fromUtf8("toolButton_right"));
        toolButton_right->setStyleSheet(QString::fromUtf8("background-image: url(:/images/add_right.png);"));

        gridLayout->addWidget(toolButton_right, 1, 2, 1, 1);

        toolButton_4 = new QToolButton(groupBox_3);
        toolButton_4->setObjectName(QString::fromUtf8("toolButton_4"));
        toolButton_4->setStyleSheet(QString::fromUtf8("QToolButton{\n"
"	border-image: url(:/images/add.png);\n"
"}\n"
"QToolButton:pressed{\n"
"	border-image: url(:/images/add_press.png);\n"
"}"));

        gridLayout->addWidget(toolButton_4, 4, 2, 1, 1);

        toolButton_up = new QToolButton(groupBox_3);
        toolButton_up->setObjectName(QString::fromUtf8("toolButton_up"));
        toolButton_up->setStyleSheet(QString::fromUtf8("background-image: url(:/images/add_top.png);"));

        gridLayout->addWidget(toolButton_up, 0, 1, 1, 1);

        toolButton_5 = new QToolButton(groupBox_3);
        toolButton_5->setObjectName(QString::fromUtf8("toolButton_5"));
        toolButton_5->setStyleSheet(QString::fromUtf8("QToolButton{\n"
"	border-image: url(:/images/reduce.png);\n"
"}\n"
"QToolButton:pressed{\n"
"	border-image: url(:/images/reduce_press.png);\n"
"}"));

        gridLayout->addWidget(toolButton_5, 5, 0, 1, 1);

        toolButton_6 = new QToolButton(groupBox_3);
        toolButton_6->setObjectName(QString::fromUtf8("toolButton_6"));
        toolButton_6->setStyleSheet(QString::fromUtf8("QToolButton{\n"
"	border-image: url(:/images/add.png);\n"
"}\n"
"QToolButton:pressed{\n"
"	border-image: url(:/images/add_press.png);\n"
"}"));

        gridLayout->addWidget(toolButton_6, 5, 2, 1, 1);

        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 3, 1, 1, 1);

        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 4, 1, 1, 1);

        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 5, 1, 1, 1);


        gridLayout_11->addLayout(gridLayout, 0, 0, 1, 1);


        gridLayout_12->addWidget(groupBox_3, 0, 0, 1, 1);


        horizontalLayout_10->addWidget(widget_5);

        widget_4 = new ImageWidget(centralWidget);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        gridLayout_8 = new QGridLayout(widget_4);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        groupBox_4 = new QGroupBox(widget_4);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_13 = new QGridLayout(groupBox_4);
        gridLayout_13->setSpacing(6);
        gridLayout_13->setContentsMargins(11, 11, 11, 11);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_14 = new QLabel(groupBox_4);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_6->addWidget(label_14);

        toolButton_savedata = new QToolButton(groupBox_4);
        toolButton_savedata->setObjectName(QString::fromUtf8("toolButton_savedata"));
        toolButton_savedata->setMinimumSize(QSize(58, 30));
        toolButton_savedata->setStyleSheet(QString::fromUtf8("border-image: url(:/images/ON.png);"));

        horizontalLayout_6->addWidget(toolButton_savedata);


        verticalLayout_4->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_20 = new QLabel(groupBox_4);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        horizontalLayout_7->addWidget(label_20);

        toolButton_actionOpengrid = new QToolButton(groupBox_4);
        toolButton_actionOpengrid->setObjectName(QString::fromUtf8("toolButton_actionOpengrid"));
        toolButton_actionOpengrid->setMinimumSize(QSize(58, 30));
        toolButton_actionOpengrid->setStyleSheet(QString::fromUtf8("border-image: url(:/images/ON.png);"));

        horizontalLayout_7->addWidget(toolButton_actionOpengrid);


        verticalLayout_4->addLayout(horizontalLayout_7);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_13 = new QLabel(groupBox_4);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_5->addWidget(label_13);

        toolButton_Portlight = new QToolButton(groupBox_4);
        toolButton_Portlight->setObjectName(QString::fromUtf8("toolButton_Portlight"));
        toolButton_Portlight->setMinimumSize(QSize(58, 30));
        toolButton_Portlight->setStyleSheet(QString::fromUtf8("border-image: url(:/images/ON.png);"));

        horizontalLayout_5->addWidget(toolButton_Portlight);


        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_22 = new QLabel(groupBox_4);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        horizontalLayout_15->addWidget(label_22);

        toolButton_sms = new QToolButton(groupBox_4);
        toolButton_sms->setObjectName(QString::fromUtf8("toolButton_sms"));
        toolButton_sms->setMinimumSize(QSize(58, 30));
        toolButton_sms->setStyleSheet(QString::fromUtf8("border-image: url(:/images/ON.png);"));

        horizontalLayout_15->addWidget(toolButton_sms);


        verticalLayout_4->addLayout(horizontalLayout_15);


        horizontalLayout_3->addLayout(verticalLayout_4);

        line_3 = new QFrame(groupBox_4);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setLineWidth(1);
        line_3->setMidLineWidth(10);
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line_3);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        toolButton_7 = new QToolButton(groupBox_4);
        toolButton_7->setObjectName(QString::fromUtf8("toolButton_7"));
        toolButton_7->setMinimumSize(QSize(58, 30));
        toolButton_7->setStyleSheet(QString::fromUtf8("border-image: url(:/images/ON.png);"));

        horizontalLayout_2->addWidget(toolButton_7);


        verticalLayout_5->addLayout(horizontalLayout_2);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_21 = new QLabel(groupBox_4);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        horizontalLayout_8->addWidget(label_21);

        toolButton_actionTrick = new QToolButton(groupBox_4);
        toolButton_actionTrick->setObjectName(QString::fromUtf8("toolButton_actionTrick"));
        toolButton_actionTrick->setMinimumSize(QSize(58, 30));
        toolButton_actionTrick->setStyleSheet(QString::fromUtf8("border-image: url(:/images/ON.png);"));

        horizontalLayout_8->addWidget(toolButton_actionTrick);


        verticalLayout_5->addLayout(horizontalLayout_8);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_4->addWidget(label_5);

        toolButton_indoorlight = new QToolButton(groupBox_4);
        toolButton_indoorlight->setObjectName(QString::fromUtf8("toolButton_indoorlight"));
        toolButton_indoorlight->setMinimumSize(QSize(58, 30));
        toolButton_indoorlight->setStyleSheet(QString::fromUtf8("border-image: url(:/images/ON.png);"));

        horizontalLayout_4->addWidget(toolButton_indoorlight);


        verticalLayout_5->addLayout(horizontalLayout_4);


        horizontalLayout_3->addLayout(verticalLayout_5);


        gridLayout_13->addLayout(horizontalLayout_3, 0, 0, 1, 1);


        gridLayout_8->addWidget(groupBox_4, 0, 1, 1, 1);


        horizontalLayout_10->addWidget(widget_4);

        horizontalLayout_10->setStretch(0, 1);
        horizontalLayout_10->setStretch(1, 1);
        horizontalLayout_10->setStretch(2, 1);

        horizontalLayout_14->addLayout(horizontalLayout_10);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        widget_3 = new ImageWidget(centralWidget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        gridLayout_10 = new QGridLayout(widget_3);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        groupBox = new QGroupBox(widget_3);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMaximumSize(QSize(16777215, 16777215));
        groupBox->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_16 = new QLabel(groupBox);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        horizontalLayout->addWidget(label_16);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        radioButton_Cluster_none = new QRadioButton(groupBox);
        radioButton_Cluster_none->setObjectName(QString::fromUtf8("radioButton_Cluster_none"));

        gridLayout_4->addWidget(radioButton_Cluster_none, 1, 2, 1, 1);

        radioButton_Cluster = new QRadioButton(groupBox);
        radioButton_Cluster->setObjectName(QString::fromUtf8("radioButton_Cluster"));

        gridLayout_4->addWidget(radioButton_Cluster, 1, 0, 1, 1);

        label_17 = new QLabel(groupBox);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(label_17, 0, 0, 1, 1);

        label_18 = new QLabel(groupBox);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(label_18, 0, 2, 1, 1);

        label_19 = new QLabel(groupBox);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_4->addWidget(label_19, 0, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout_4);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout);

        line = new QFrame(groupBox);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_9->addWidget(label_9);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        radioButton_cloud_none = new QRadioButton(groupBox);
        radioButton_cloud_none->setObjectName(QString::fromUtf8("radioButton_cloud_none"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(radioButton_cloud_none->sizePolicy().hasHeightForWidth());
        radioButton_cloud_none->setSizePolicy(sizePolicy);
        radioButton_cloud_none->setToolTipDuration(-1);
        radioButton_cloud_none->setLayoutDirection(Qt::LeftToRight);

        gridLayout_3->addWidget(radioButton_cloud_none, 1, 2, 1, 1);

        radioButton_Cloud_all = new QRadioButton(groupBox);
        radioButton_Cloud_all->setObjectName(QString::fromUtf8("radioButton_Cloud_all"));
        sizePolicy.setHeightForWidth(radioButton_Cloud_all->sizePolicy().hasHeightForWidth());
        radioButton_Cloud_all->setSizePolicy(sizePolicy);
        radioButton_Cloud_all->setLayoutDirection(Qt::LeftToRight);

        gridLayout_3->addWidget(radioButton_Cloud_all, 1, 0, 1, 1);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setStyleSheet(QString::fromUtf8(""));

        gridLayout_3->addWidget(label_12, 0, 2, 1, 1);

        radioButton_cloud_ob = new QRadioButton(groupBox);
        radioButton_cloud_ob->setObjectName(QString::fromUtf8("radioButton_cloud_ob"));

        gridLayout_3->addWidget(radioButton_cloud_ob, 1, 1, 1, 1);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setStyleSheet(QString::fromUtf8(""));

        gridLayout_3->addWidget(label_11, 0, 1, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setStyleSheet(QString::fromUtf8(""));

        gridLayout_3->addWidget(label_10, 0, 0, 1, 1);


        horizontalLayout_9->addLayout(gridLayout_3);

        horizontalLayout_9->setStretch(0, 1);
        horizontalLayout_9->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout_9);

        line_2 = new QFrame(groupBox);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_12->addWidget(label_8);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        radioButton_Area_none = new QRadioButton(groupBox);
        radioButton_Area_none->setObjectName(QString::fromUtf8("radioButton_Area_none"));

        gridLayout_2->addWidget(radioButton_Area_none, 1, 2, 1, 1);

        radioButton_Area_2d = new QRadioButton(groupBox);
        radioButton_Area_2d->setObjectName(QString::fromUtf8("radioButton_Area_2d"));

        gridLayout_2->addWidget(radioButton_Area_2d, 1, 0, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(label_6, 0, 0, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(label_7, 0, 2, 1, 1);

        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_2->addWidget(label_15, 0, 1, 1, 1);


        horizontalLayout_12->addLayout(gridLayout_2);

        horizontalLayout_12->setStretch(0, 1);
        horizontalLayout_12->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout_12);


        verticalLayout_2->addLayout(verticalLayout);


        gridLayout_10->addWidget(groupBox, 0, 0, 1, 1);


        horizontalLayout_13->addWidget(widget_3);

        widget = new ImageWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout_5 = new QGridLayout(widget);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        groupBox_5 = new QGroupBox(widget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        gridLayout_15 = new QGridLayout(groupBox_5);
        gridLayout_15->setSpacing(6);
        gridLayout_15->setContentsMargins(11, 11, 11, 11);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        textEdit = new QTextEdit(groupBox_5);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        gridLayout_15->addWidget(textEdit, 0, 0, 1, 1);


        gridLayout_5->addWidget(groupBox_5, 0, 0, 1, 1);


        horizontalLayout_13->addWidget(widget);


        horizontalLayout_14->addLayout(horizontalLayout_13);

        horizontalLayout_14->setStretch(0, 3);
        horizontalLayout_14->setStretch(1, 2);

        verticalLayout_6->addLayout(horizontalLayout_14);

        verticalLayout_6->setStretch(1, 10);
        verticalLayout_6->setStretch(2, 1);

        gridLayout_14->addLayout(verticalLayout_6, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\347\263\273\347\273\237\350\256\276\347\275\256", nullptr));
        pushButton_addlidar->setText(QCoreApplication::translate("MainWindow", " \347\233\221\346\216\247\350\256\276\347\275\256", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", " \351\230\262\345\214\272\350\256\276\347\275\256", nullptr));
        pushButton_sms->setText(QCoreApplication::translate("MainWindow", "\347\237\255\344\277\241\350\256\276\347\275\256", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\347\233\270\346\234\272\346\223\215\344\275\234", nullptr));
        toolButton_3->setText(QString());
        toolButton_left->setText(QString());
        toolButton->setText(QString());
        toolButton_2->setText(QString());
        toolButton_down->setText(QString());
        toolButton_right->setText(QString());
        toolButton_4->setText(QString());
        toolButton_up->setText(QString());
        toolButton_5->setText(QString());
        toolButton_6->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "\350\260\203\347\204\246", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\350\201\232\347\204\246", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\345\205\211\345\234\210", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "\346\216\247\345\210\266\351\235\242\346\235\277", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\344\277\235\345\255\230", nullptr));
        toolButton_savedata->setText(QString());
        label_20->setText(QCoreApplication::translate("MainWindow", "\346\240\205\346\240\274\346\230\276\347\244\272", nullptr));
        toolButton_actionOpengrid->setText(QString());
        label_13->setText(QCoreApplication::translate("MainWindow", "\346\270\257\345\217\243\346\212\245\350\255\246\347\201\257", nullptr));
        toolButton_Portlight->setText(QString());
        label_22->setText(QCoreApplication::translate("MainWindow", "\347\237\255\344\277\241\346\212\245\350\255\246", nullptr));
        toolButton_sms->setText(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "\350\201\224\345\212\250\347\233\270\346\234\272", nullptr));
        toolButton_7->setText(QString());
        label_21->setText(QCoreApplication::translate("MainWindow", "\347\233\256\346\240\207\350\275\250\350\277\271", nullptr));
        toolButton_actionTrick->setText(QString());
        label_5->setText(QCoreApplication::translate("MainWindow", "\346\234\272\346\210\277\346\212\245\350\255\246\347\201\257", nullptr));
        toolButton_indoorlight->setText(QString());
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\350\256\276\347\275\256", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "\346\212\245\350\255\246\346\230\276\347\244\272", nullptr));
        radioButton_Cluster_none->setText(QString());
        radioButton_Cluster->setText(QString());
        label_17->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "\344\270\215\346\230\276\347\244\272", nullptr));
        label_19->setText(QString());
        label_9->setText(QCoreApplication::translate("MainWindow", "\347\202\271\344\272\221\346\230\276\347\244\272", nullptr));
        radioButton_cloud_none->setText(QString());
        radioButton_Cloud_all->setText(QString());
        label_12->setText(QCoreApplication::translate("MainWindow", "\344\270\215\346\230\276\347\244\272", nullptr));
        radioButton_cloud_ob->setText(QString());
        label_11->setText(QCoreApplication::translate("MainWindow", "\347\233\256\346\240\207", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\345\205\250\351\203\250", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\351\230\262\345\214\272\346\230\276\347\244\272", nullptr));
        radioButton_Area_none->setText(QString());
        radioButton_Area_2d->setText(QString());
        label_6->setText(QCoreApplication::translate("MainWindow", "2D\351\230\262\345\214\272", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\344\270\215\346\230\276\347\244\272", nullptr));
        label_15->setText(QString());
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "\346\227\245\345\277\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

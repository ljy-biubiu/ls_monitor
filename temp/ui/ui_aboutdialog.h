/********************************************************************************
** Form generated from reading UI file 'aboutdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTDIALOG_H
#define UI_ABOUTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <childtitlebar.h>

QT_BEGIN_NAMESPACE

class Ui_aboutDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_4;
    ChildTitleBar *widget_childTitle;
    QFrame *line;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_4;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_5;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_title;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_version;
    QLabel *label_copyright;
    QLabel *label_7;
    QLabel *label_time;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *aboutDialog)
    {
        if (aboutDialog->objectName().isEmpty())
            aboutDialog->setObjectName(QString::fromUtf8("aboutDialog"));
        aboutDialog->resize(540, 280);
        aboutDialog->setMinimumSize(QSize(540, 280));
        aboutDialog->setMaximumSize(QSize(540, 280));
        gridLayout = new QGridLayout(aboutDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        widget_childTitle = new ChildTitleBar(aboutDialog);
        widget_childTitle->setObjectName(QString::fromUtf8("widget_childTitle"));
        widget_childTitle->setMinimumSize(QSize(0, 30));
        widget_childTitle->setMaximumSize(QSize(16777215, 30));

        verticalLayout_4->addWidget(widget_childTitle);

        line = new QFrame(aboutDialog);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_4);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(20);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(aboutDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/Logo.png")));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(aboutDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(100, 0));
        pushButton->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_3->addLayout(verticalLayout_2);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_5);


        horizontalLayout_2->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        label_title = new QLabel(aboutDialog);
        label_title->setObjectName(QString::fromUtf8("label_title"));
        label_title->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_title);

        verticalSpacer_2 = new QSpacerItem(223, 5, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label_version = new QLabel(aboutDialog);
        label_version->setObjectName(QString::fromUtf8("label_version"));
        label_version->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(label_version);

        label_copyright = new QLabel(aboutDialog);
        label_copyright->setObjectName(QString::fromUtf8("label_copyright"));
        label_copyright->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(label_copyright);

        label_7 = new QLabel(aboutDialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(label_7);

        label_time = new QLabel(aboutDialog);
        label_time->setObjectName(QString::fromUtf8("label_time"));
        label_time->setMinimumSize(QSize(0, 30));
        label_time->setMaximumSize(QSize(16777215, 50));
        label_time->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_time);

        verticalSpacer = new QSpacerItem(223, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 2);

        verticalLayout_4->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout_4, 0, 0, 1, 1);


        retranslateUi(aboutDialog);

        QMetaObject::connectSlotsByName(aboutDialog);
    } // setupUi

    void retranslateUi(QDialog *aboutDialog)
    {
        aboutDialog->setWindowTitle(QCoreApplication::translate("aboutDialog", "About LidarPercept", nullptr));
        label->setText(QString());
        pushButton->setText(QCoreApplication::translate("aboutDialog", "\350\201\224\347\263\273\346\210\221\344\273\254", nullptr));
        label_title->setText(QCoreApplication::translate("aboutDialog", "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt; font-weight:600; color:#000000;\">\351\225\255\347\245\236\346\231\272\350\203\275\346\277\200\345\205\211\351\233\267\350\276\276\345\256\211\351\230\262\347\263\273\347\273\237</span></p></body></html>", nullptr));
        label_version->setText(QCoreApplication::translate("aboutDialog", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;\">Version 1.0.1</span></p></body></html>", nullptr));
        label_copyright->setText(QCoreApplication::translate("aboutDialog", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;\">Copyright(C) 2022 LeiShen</span></p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("aboutDialog", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;\">All rights reservd. </span></p></body></html>", nullptr));
        label_time->setText(QCoreApplication::translate("aboutDialog", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;\">2021.11.23</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class aboutDialog: public Ui_aboutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTDIALOG_H

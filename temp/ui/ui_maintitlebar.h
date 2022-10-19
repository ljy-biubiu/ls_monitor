/********************************************************************************
** Form generated from reading UI file 'maintitlebar.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINTITLEBAR_H
#define UI_MAINTITLEBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainTitleBar
{
public:
    QGridLayout *gridLayout_3;
    QFrame *frameBorder;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer;
    QLabel *labelTitleName;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonAbout;
    QPushButton *pushButtonMin;
    QPushButton *pushButtonNormalMax;
    QPushButton *pushButtonClose;

    void setupUi(QWidget *MainTitleBar)
    {
        if (MainTitleBar->objectName().isEmpty())
            MainTitleBar->setObjectName(QString::fromUtf8("MainTitleBar"));
        MainTitleBar->resize(652, 53);
        MainTitleBar->setStyleSheet(QString::fromUtf8(""));
        gridLayout_3 = new QGridLayout(MainTitleBar);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        frameBorder = new QFrame(MainTitleBar);
        frameBorder->setObjectName(QString::fromUtf8("frameBorder"));
        frameBorder->setStyleSheet(QString::fromUtf8("QFrame#frameBorder{border-image: url(:/images/title.png);}"));
        frameBorder->setFrameShape(QFrame::StyledPanel);
        frameBorder->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frameBorder);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        gridLayout_2->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        labelTitleName = new QLabel(frameBorder);
        labelTitleName->setObjectName(QString::fromUtf8("labelTitleName"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        labelTitleName->setFont(font);
        labelTitleName->setScaledContents(true);
        labelTitleName->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(labelTitleName, 0, 1, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButtonAbout = new QPushButton(frameBorder);
        pushButtonAbout->setObjectName(QString::fromUtf8("pushButtonAbout"));
        pushButtonAbout->setMinimumSize(QSize(20, 20));
        pushButtonAbout->setMaximumSize(QSize(20, 20));

        horizontalLayout->addWidget(pushButtonAbout);

        pushButtonMin = new QPushButton(frameBorder);
        pushButtonMin->setObjectName(QString::fromUtf8("pushButtonMin"));
        pushButtonMin->setMinimumSize(QSize(20, 20));
        pushButtonMin->setMaximumSize(QSize(20, 20));
        QFont font1;
        font1.setPointSize(6);
        pushButtonMin->setFont(font1);
        pushButtonMin->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(pushButtonMin);

        pushButtonNormalMax = new QPushButton(frameBorder);
        pushButtonNormalMax->setObjectName(QString::fromUtf8("pushButtonNormalMax"));
        pushButtonNormalMax->setMinimumSize(QSize(20, 20));
        pushButtonNormalMax->setMaximumSize(QSize(20, 20));
        pushButtonNormalMax->setFont(font1);
        pushButtonNormalMax->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(pushButtonNormalMax);

        pushButtonClose = new QPushButton(frameBorder);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));
        pushButtonClose->setMinimumSize(QSize(20, 20));
        pushButtonClose->setMaximumSize(QSize(20, 20));

        horizontalLayout->addWidget(pushButtonClose);


        gridLayout->addLayout(horizontalLayout, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 2, 1, 1);


        gridLayout_3->addWidget(frameBorder, 0, 0, 1, 1);


        retranslateUi(MainTitleBar);

        QMetaObject::connectSlotsByName(MainTitleBar);
    } // setupUi

    void retranslateUi(QWidget *MainTitleBar)
    {
        MainTitleBar->setWindowTitle(QCoreApplication::translate("MainTitleBar", "Form", nullptr));
        labelTitleName->setText(QCoreApplication::translate("MainTitleBar", "<html><head/><body><p><span style=\" font-size:18pt; color:#ffffff;\">\351\225\255\347\245\236\350\275\246\350\267\257\345\215\217\345\220\214\347\263\273\347\273\237</span></p></body></html>", nullptr));
        pushButtonAbout->setText(QString());
        pushButtonMin->setText(QString());
        pushButtonNormalMax->setText(QString());
        pushButtonClose->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainTitleBar: public Ui_MainTitleBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINTITLEBAR_H

/********************************************************************************
** Form generated from reading UI file 'childtitlebar.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHILDTITLEBAR_H
#define UI_CHILDTITLEBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChildTitleBar
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer;
    QLabel *labelTitleName;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonClose;

    void setupUi(QWidget *ChildTitleBar)
    {
        if (ChildTitleBar->objectName().isEmpty())
            ChildTitleBar->setObjectName(QString::fromUtf8("ChildTitleBar"));
        ChildTitleBar->resize(688, 52);
        ChildTitleBar->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_2 = new QHBoxLayout(ChildTitleBar);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 9, -1, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        horizontalLayout_2->addLayout(horizontalLayout_3);

        labelTitleName = new QLabel(ChildTitleBar);
        labelTitleName->setObjectName(QString::fromUtf8("labelTitleName"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        labelTitleName->setFont(font);
        labelTitleName->setScaledContents(true);
        labelTitleName->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(labelTitleName);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(60, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButtonClose = new QPushButton(ChildTitleBar);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));
        pushButtonClose->setMinimumSize(QSize(20, 20));
        pushButtonClose->setMaximumSize(QSize(20, 20));

        horizontalLayout->addWidget(pushButtonClose);


        horizontalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2->setStretch(0, 2);
        horizontalLayout_2->setStretch(1, 1);
        horizontalLayout_2->setStretch(2, 2);

        retranslateUi(ChildTitleBar);

        QMetaObject::connectSlotsByName(ChildTitleBar);
    } // setupUi

    void retranslateUi(QWidget *ChildTitleBar)
    {
        ChildTitleBar->setWindowTitle(QCoreApplication::translate("ChildTitleBar", "Form", nullptr));
        labelTitleName->setText(QCoreApplication::translate("ChildTitleBar", "<html><head/><body><p><span style=\" font-size:12pt; color:#ffffff;\">\351\225\255\347\245\236\350\275\246\350\267\257\345\215\217\345\220\214\347\263\273\347\273\237</span></p></body></html>", nullptr));
        pushButtonClose->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ChildTitleBar: public Ui_ChildTitleBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHILDTITLEBAR_H

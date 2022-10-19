/********************************************************************************
** Form generated from reading UI file 'smsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMSDIALOG_H
#define UI_SMSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <childtitlebar.h>

QT_BEGIN_NAMESPACE

class Ui_SMSDialog
{
public:
    QGridLayout *gridLayout_3;
    ChildTitleBar *widget;
    QTreeWidget *treeWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEdit;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpinBox *spinBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QSpinBox *spinBox_dist;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_time;

    void setupUi(QDialog *SMSDialog)
    {
        if (SMSDialog->objectName().isEmpty())
            SMSDialog->setObjectName(QString::fromUtf8("SMSDialog"));
        SMSDialog->resize(530, 411);
        gridLayout_3 = new QGridLayout(SMSDialog);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, -1);
        widget = new ChildTitleBar(SMSDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 30));
        widget->setMaximumSize(QSize(16777215, 30));

        gridLayout_3->addWidget(widget, 0, 0, 1, 1);

        treeWidget = new QTreeWidget(SMSDialog);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setTextAlignment(1, Qt::AlignCenter);
        __qtreewidgetitem->setTextAlignment(0, Qt::AlignCenter);
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->header()->setCascadingSectionResizes(false);

        gridLayout_3->addWidget(treeWidget, 1, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(8, -1, 8, -1);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        lineEdit = new QLineEdit(SMSDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout_2->addWidget(lineEdit, 0, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton = new QPushButton(SMSDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(SMSDialog);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        spinBox = new QSpinBox(SMSDialog);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        horizontalLayout_2->addWidget(spinBox);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(SMSDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        spinBox_dist = new QSpinBox(SMSDialog);
        spinBox_dist->setObjectName(QString::fromUtf8("spinBox_dist"));

        horizontalLayout_3->addWidget(spinBox_dist);


        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout_4->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pushButton_time = new QPushButton(SMSDialog);
        pushButton_time->setObjectName(QString::fromUtf8("pushButton_time"));

        verticalLayout_2->addWidget(pushButton_time);


        horizontalLayout_4->addLayout(verticalLayout_2);

        horizontalLayout_4->setStretch(0, 1);

        verticalLayout_3->addLayout(horizontalLayout_4);


        gridLayout_3->addLayout(verticalLayout_3, 2, 0, 1, 1);


        retranslateUi(SMSDialog);

        QMetaObject::connectSlotsByName(SMSDialog);
    } // setupUi

    void retranslateUi(QDialog *SMSDialog)
    {
        SMSDialog->setWindowTitle(QCoreApplication::translate("SMSDialog", "Dialog", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("SMSDialog", "\346\211\213\346\234\272\345\217\267\347\240\201", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("SMSDialog", "\345\272\217\345\217\267", nullptr));
        pushButton->setText(QCoreApplication::translate("SMSDialog", "\346\267\273\345\212\240", nullptr));
        label->setText(QCoreApplication::translate("SMSDialog", "\347\237\255\344\277\241\346\212\245\350\255\246\346\227\266\351\227\264\351\227\264\351\232\224\357\274\210\345\210\206\351\222\237\357\274\211\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("SMSDialog", "\347\237\255\344\277\241\346\212\245\350\255\246\347\233\256\346\240\207\350\267\235\347\246\273\357\274\210\347\261\263\357\274\211\357\274\232", nullptr));
        pushButton_time->setText(QCoreApplication::translate("SMSDialog", "\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SMSDialog: public Ui_SMSDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMSDIALOG_H

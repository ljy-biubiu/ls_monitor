/********************************************************************************
** Form generated from reading UI file 'setroi.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETROI_H
#define UI_SETROI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <childtitlebar.h>

QT_BEGIN_NAMESPACE

class Ui_SetROI
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    ChildTitleBar *widget;
    QFrame *line;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QFrame *frame_edit;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_times;
    QLabel *label_4;
    QComboBox *comboBox;
    QLabel *label_3;
    QLineEdit *lineEdit_Area_height_max;
    QLineEdit *lineEdit_Area_height_min;
    QLabel *label;
    QTableWidget *tableWidget_2;
    QHBoxLayout *horizontalLayout;

    void setupUi(QWidget *SetROI)
    {
        if (SetROI->objectName().isEmpty())
            SetROI->setObjectName(QString::fromUtf8("SetROI"));
        SetROI->resize(961, 730);
        gridLayout = new QGridLayout(SetROI);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(8);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget = new ChildTitleBar(SetROI);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 30));
        widget->setMaximumSize(QSize(16777215, 30));

        verticalLayout_2->addWidget(widget);

        line = new QFrame(SetROI);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableWidget = new QTableWidget(SetROI);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (tableWidget->rowCount() < 9)
            tableWidget->setRowCount(9);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(7, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(8, __qtablewidgetitem9);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setDragEnabled(true);
        tableWidget->horizontalHeader()->setVisible(false);

        verticalLayout->addWidget(tableWidget);

        frame_edit = new QFrame(SetROI);
        frame_edit->setObjectName(QString::fromUtf8("frame_edit"));
        frame_edit->setFrameShape(QFrame::Box);
        frame_edit->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_edit);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(2, 0, 2, 0);
        label_2 = new QLabel(frame_edit);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_times = new QLineEdit(frame_edit);
        lineEdit_times->setObjectName(QString::fromUtf8("lineEdit_times"));

        gridLayout_2->addWidget(lineEdit_times, 1, 1, 1, 1);

        label_4 = new QLabel(frame_edit);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        comboBox = new QComboBox(frame_edit);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout_2->addWidget(comboBox, 0, 1, 1, 1);

        label_3 = new QLabel(frame_edit);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        lineEdit_Area_height_max = new QLineEdit(frame_edit);
        lineEdit_Area_height_max->setObjectName(QString::fromUtf8("lineEdit_Area_height_max"));

        gridLayout_2->addWidget(lineEdit_Area_height_max, 3, 1, 1, 1);

        lineEdit_Area_height_min = new QLineEdit(frame_edit);
        lineEdit_Area_height_min->setObjectName(QString::fromUtf8("lineEdit_Area_height_min"));

        gridLayout_2->addWidget(lineEdit_Area_height_min, 2, 1, 1, 1);

        label = new QLabel(frame_edit);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);


        verticalLayout->addWidget(frame_edit);

        tableWidget_2 = new QTableWidget(SetROI);
        if (tableWidget_2->columnCount() < 2)
            tableWidget_2->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem11);
        tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));
        tableWidget_2->setDragEnabled(false);
        tableWidget_2->horizontalHeader()->setVisible(false);

        verticalLayout->addWidget(tableWidget_2);

        verticalLayout->setStretch(0, 2);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 2);

        horizontalLayout_2->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

        horizontalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 4);

        verticalLayout_2->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);


        retranslateUi(SetROI);

        QMetaObject::connectSlotsByName(SetROI);
    } // setupUi

    void retranslateUi(QWidget *SetROI)
    {
        SetROI->setWindowTitle(QCoreApplication::translate("SetROI", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SetROI", "\345\261\236\346\200\247", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SetROI", "\351\233\267\350\276\276Ip", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SetROI", "\351\233\267\350\276\276\345\272\217\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SetROI", "\351\233\267\350\276\276\346\211\253\346\217\217\345\215\212\345\276\204", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SetROI", "\345\217\257\347\274\226\350\276\221\345\214\272\345\237\237\345\272\217\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("SetROI", "\345\237\272\345\207\206\345\235\220\346\240\207", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("SetROI", "\345\237\272\345\207\206\350\275\254\350\247\222", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("SetROI", "\345\203\217\347\264\240\350\267\235\347\246\273\346\257\224", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(7);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("SetROI", "\345\214\272\345\237\237\345\206\205\347\202\271\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->verticalHeaderItem(8);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("SetROI", "\345\214\272\345\237\237\345\244\226\347\202\271\346\225\260", nullptr));
        label_2->setText(QCoreApplication::translate("SetROI", "\351\232\234\347\242\215\347\211\251\345\255\230\345\234\250\346\227\266\351\227\264", nullptr));
        label_4->setText(QCoreApplication::translate("SetROI", "\351\230\262\345\214\272\351\253\230\345\272\246\346\234\200\345\244\247\345\200\274\357\274\210\345\215\225\344\275\215\357\274\232m\357\274\211", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("SetROI", "1", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("SetROI", "2", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("SetROI", "3", nullptr));

        label_3->setText(QCoreApplication::translate("SetROI", "\351\230\262\345\214\272\351\253\230\345\272\246\346\234\200\345\260\217\345\200\274\357\274\210\345\215\225\344\275\215\357\274\232m\357\274\211", nullptr));
        label->setText(QCoreApplication::translate("SetROI", "\345\214\272\345\237\237\351\200\211\346\213\251", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("SetROI", "X", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("SetROI", "Y", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetROI: public Ui_SetROI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETROI_H

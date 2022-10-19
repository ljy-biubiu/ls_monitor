/********************************************************************************
** Form generated from reading UI file 'addpolygon.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDPOLYGON_H
#define UI_ADDPOLYGON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Addpolygon
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_x;
    QLineEdit *lineEdit_y;

    void setupUi(QDialog *Addpolygon)
    {
        if (Addpolygon->objectName().isEmpty())
            Addpolygon->setObjectName(QString::fromUtf8("Addpolygon"));
        Addpolygon->resize(400, 300);
        buttonBox = new QDialogButtonBox(Addpolygon);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        gridLayoutWidget = new QWidget(Addpolygon);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(110, 60, 160, 80));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_x = new QLineEdit(gridLayoutWidget);
        lineEdit_x->setObjectName(QString::fromUtf8("lineEdit_x"));

        gridLayout->addWidget(lineEdit_x, 0, 1, 1, 1);

        lineEdit_y = new QLineEdit(gridLayoutWidget);
        lineEdit_y->setObjectName(QString::fromUtf8("lineEdit_y"));

        gridLayout->addWidget(lineEdit_y, 1, 1, 1, 1);


        retranslateUi(Addpolygon);
        QObject::connect(buttonBox, SIGNAL(accepted()), Addpolygon, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Addpolygon, SLOT(reject()));

        QMetaObject::connectSlotsByName(Addpolygon);
    } // setupUi

    void retranslateUi(QDialog *Addpolygon)
    {
        Addpolygon->setWindowTitle(QCoreApplication::translate("Addpolygon", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Addpolygon", "x(\345\215\225\344\275\215mm)", nullptr));
        label_2->setText(QCoreApplication::translate("Addpolygon", "y(\345\215\225\344\275\215mm)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Addpolygon: public Ui_Addpolygon {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDPOLYGON_H

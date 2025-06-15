/********************************************************************************
** Form generated from reading UI file 'ChinaDay.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHINADAY_H
#define UI_CHINADAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_ChinaDayClass
{
public:

    void setupUi(QDialog *ChinaDayClass)
    {
        if (ChinaDayClass->objectName().isEmpty())
            ChinaDayClass->setObjectName(QString::fromUtf8("ChinaDayClass"));
        ChinaDayClass->resize(302, 554);
        ChinaDayClass->setStyleSheet(QString::fromUtf8(""));

        retranslateUi(ChinaDayClass);

        QMetaObject::connectSlotsByName(ChinaDayClass);
    } // setupUi

    void retranslateUi(QDialog *ChinaDayClass)
    {
        ChinaDayClass->setWindowTitle(QCoreApplication::translate("ChinaDayClass", "ChinaDay", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChinaDayClass: public Ui_ChinaDayClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHINADAY_H

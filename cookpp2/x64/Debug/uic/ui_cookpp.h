/********************************************************************************
** Form generated from reading UI file 'cookpp.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COOKPP_H
#define UI_COOKPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cookppClass
{
public:

    void setupUi(QWidget *cookppClass)
    {
        if (cookppClass->objectName().isEmpty())
            cookppClass->setObjectName("cookppClass");
        cookppClass->resize(600, 400);

        retranslateUi(cookppClass);

        QMetaObject::connectSlotsByName(cookppClass);
    } // setupUi

    void retranslateUi(QWidget *cookppClass)
    {
        cookppClass->setWindowTitle(QCoreApplication::translate("cookppClass", "cookpp", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cookppClass: public Ui_cookppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COOKPP_H

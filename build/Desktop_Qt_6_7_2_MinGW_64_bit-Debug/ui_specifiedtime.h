/********************************************************************************
** Form generated from reading UI file 'specifiedtime.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPECIFIEDTIME_H
#define UI_SPECIFIEDTIME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SpecifiedTime
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QDateTimeEdit *fromDateTimeEdit;
    QDateTimeEdit *toDateTimeEdit;
    QPushButton *fetchButton;
    QTableWidget *tableWidget;

    void setupUi(QWidget *SpecifiedTime)
    {
        if (SpecifiedTime->objectName().isEmpty())
            SpecifiedTime->setObjectName("SpecifiedTime");
        verticalLayout = new QVBoxLayout(SpecifiedTime);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(SpecifiedTime);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        fromDateTimeEdit = new QDateTimeEdit(SpecifiedTime);
        fromDateTimeEdit->setObjectName("fromDateTimeEdit");
        fromDateTimeEdit->setCalendarPopup(true);

        verticalLayout->addWidget(fromDateTimeEdit);

        toDateTimeEdit = new QDateTimeEdit(SpecifiedTime);
        toDateTimeEdit->setObjectName("toDateTimeEdit");
        toDateTimeEdit->setCalendarPopup(true);

        verticalLayout->addWidget(toDateTimeEdit);

        fetchButton = new QPushButton(SpecifiedTime);
        fetchButton->setObjectName("fetchButton");

        verticalLayout->addWidget(fetchButton);

        tableWidget = new QTableWidget(SpecifiedTime);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setColumnCount(6);

        verticalLayout->addWidget(tableWidget);


        retranslateUi(SpecifiedTime);

        QMetaObject::connectSlotsByName(SpecifiedTime);
    } // setupUi

    void retranslateUi(QWidget *SpecifiedTime)
    {
        label->setText(QCoreApplication::translate("SpecifiedTime", "Specify Time Range", nullptr));
        fetchButton->setText(QCoreApplication::translate("SpecifiedTime", "Fetch Call Logs", nullptr));
        tableWidget->setHorizontalHeaderLabels(QStringList{
            QCoreApplication::translate("SpecifiedTime", "Call Ref ID", nullptr),
            QCoreApplication::translate("SpecifiedTime", "Channel", nullptr),
            QCoreApplication::translate("SpecifiedTime", "Call Type", nullptr),
            QCoreApplication::translate("SpecifiedTime", "Call Time", nullptr),
            QCoreApplication::translate("SpecifiedTime", "Duration", nullptr),
            QCoreApplication::translate("SpecifiedTime", "Status", nullptr)});
        (void)SpecifiedTime;
    } // retranslateUi

};

namespace Ui {
    class SpecifiedTime: public Ui_SpecifiedTime {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPECIFIEDTIME_H

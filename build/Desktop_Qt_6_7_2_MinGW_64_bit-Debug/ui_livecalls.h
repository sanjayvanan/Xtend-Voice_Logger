/********************************************************************************
** Form generated from reading UI file 'livecalls.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIVECALLS_H
#define UI_LIVECALLS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LiveCalls
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelStatus;
    QTableWidget *tableLiveCalls;

    void setupUi(QWidget *LiveCalls)
    {
        if (LiveCalls->objectName().isEmpty())
            LiveCalls->setObjectName("LiveCalls");
        LiveCalls->resize(800, 600);
        verticalLayout = new QVBoxLayout(LiveCalls);
        verticalLayout->setObjectName("verticalLayout");
        labelStatus = new QLabel(LiveCalls);
        labelStatus->setObjectName("labelStatus");

        verticalLayout->addWidget(labelStatus);

        tableLiveCalls = new QTableWidget(LiveCalls);
        if (tableLiveCalls->columnCount() < 8)
            tableLiveCalls->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableLiveCalls->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableLiveCalls->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableLiveCalls->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableLiveCalls->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableLiveCalls->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableLiveCalls->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableLiveCalls->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableLiveCalls->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        tableLiveCalls->setObjectName("tableLiveCalls");
        tableLiveCalls->setColumnCount(8);

        verticalLayout->addWidget(tableLiveCalls);


        retranslateUi(LiveCalls);

        QMetaObject::connectSlotsByName(LiveCalls);
    } // setupUi

    void retranslateUi(QWidget *LiveCalls)
    {
        LiveCalls->setWindowTitle(QCoreApplication::translate("LiveCalls", "Live Calls", nullptr));
        labelStatus->setText(QCoreApplication::translate("LiveCalls", "Active Calls: 0", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableLiveCalls->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("LiveCalls", "Channel", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableLiveCalls->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("LiveCalls", "Channel Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableLiveCalls->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("LiveCalls", "Call Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableLiveCalls->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("LiveCalls", "Call Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableLiveCalls->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("LiveCalls", "Caller ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableLiveCalls->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("LiveCalls", "Called ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableLiveCalls->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("LiveCalls", "Reason", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableLiveCalls->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("LiveCalls", "Actions", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LiveCalls: public Ui_LiveCalls {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIVECALLS_H

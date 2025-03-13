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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LiveCalls
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLabel *labelChannelGroup;
    QComboBox *channelGroupCombo;
    QSpacerItem *horizontalSpacer;
    QLabel *labelStatus;
    QTableWidget *tableLiveCalls;

    void setupUi(QWidget *LiveCalls)
    {
        if (LiveCalls->objectName().isEmpty())
            LiveCalls->setObjectName("LiveCalls");
        LiveCalls->resize(800, 600);
        verticalLayout = new QVBoxLayout(LiveCalls);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(LiveCalls);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        labelChannelGroup = new QLabel(LiveCalls);
        labelChannelGroup->setObjectName("labelChannelGroup");

        horizontalLayout->addWidget(labelChannelGroup);

        channelGroupCombo = new QComboBox(LiveCalls);
        channelGroupCombo->addItem(QString());
        channelGroupCombo->setObjectName("channelGroupCombo");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(channelGroupCombo->sizePolicy().hasHeightForWidth());
        channelGroupCombo->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(channelGroupCombo);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        labelStatus = new QLabel(LiveCalls);
        labelStatus->setObjectName("labelStatus");

        horizontalLayout->addWidget(labelStatus);


        verticalLayout->addLayout(horizontalLayout);

        tableLiveCalls = new QTableWidget(LiveCalls);
        if (tableLiveCalls->columnCount() < 10)
            tableLiveCalls->setColumnCount(10);
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
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableLiveCalls->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableLiveCalls->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        tableLiveCalls->setObjectName("tableLiveCalls");
        tableLiveCalls->setAlternatingRowColors(true);
        tableLiveCalls->setSelectionMode(QAbstractItemView::SingleSelection);
        tableLiveCalls->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout->addWidget(tableLiveCalls);


        retranslateUi(LiveCalls);

        QMetaObject::connectSlotsByName(LiveCalls);
    } // setupUi

    void retranslateUi(QWidget *LiveCalls)
    {
        LiveCalls->setWindowTitle(QCoreApplication::translate("LiveCalls", "Form", nullptr));
        label->setText(QCoreApplication::translate("LiveCalls", "Live Calls", nullptr));
        labelChannelGroup->setText(QCoreApplication::translate("LiveCalls", "Channel Group:", nullptr));
        channelGroupCombo->setItemText(0, QCoreApplication::translate("LiveCalls", "All", nullptr));

        labelStatus->setText(QCoreApplication::translate("LiveCalls", "Total Active Calls: 0", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableLiveCalls->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("LiveCalls", "Channel", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableLiveCalls->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("LiveCalls", "Channel Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableLiveCalls->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("LiveCalls", "Call Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableLiveCalls->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("LiveCalls", "Call Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableLiveCalls->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("LiveCalls", "Call Ref ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableLiveCalls->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("LiveCalls", "Duration", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableLiveCalls->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("LiveCalls", "Caller ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableLiveCalls->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("LiveCalls", "Called ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableLiveCalls->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("LiveCalls", "Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableLiveCalls->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("LiveCalls", "Listen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LiveCalls: public Ui_LiveCalls {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIVECALLS_H

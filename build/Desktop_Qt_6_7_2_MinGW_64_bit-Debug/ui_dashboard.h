/********************************************************************************
** Form generated from reading UI file 'dashboard.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DASHBOARD_H
#define UI_DASHBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dashboard
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTitle;
    QGridLayout *gridLayout;
    QFrame *frameToday;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelTodayHeader;
    QLabel *labelTodayTotal;
    QLabel *labelTodayConnected;
    QLabel *labelTodayMissed;
    QLabel *labelTodayIncoming;
    QLabel *labelTodayOutgoing;
    QFrame *frameLive;
    QVBoxLayout *verticalLayout_3;
    QLabel *labelLiveHeader;
    QLabel *labelActiveCalls;
    QLabel *labelActiveIncoming;
    QLabel *labelActiveOutgoing;

    void setupUi(QWidget *Dashboard)
    {
        if (Dashboard->objectName().isEmpty())
            Dashboard->setObjectName("Dashboard");
        Dashboard->resize(800, 600);
        verticalLayout = new QVBoxLayout(Dashboard);
        verticalLayout->setObjectName("verticalLayout");
        labelTitle = new QLabel(Dashboard);
        labelTitle->setObjectName("labelTitle");
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        labelTitle->setFont(font);
        labelTitle->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelTitle);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        frameToday = new QFrame(Dashboard);
        frameToday->setObjectName("frameToday");
        frameToday->setFrameShape(QFrame::StyledPanel);
        frameToday->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frameToday);
        verticalLayout_2->setObjectName("verticalLayout_2");
        labelTodayHeader = new QLabel(frameToday);
        labelTodayHeader->setObjectName("labelTodayHeader");
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        labelTodayHeader->setFont(font1);

        verticalLayout_2->addWidget(labelTodayHeader);

        labelTodayTotal = new QLabel(frameToday);
        labelTodayTotal->setObjectName("labelTodayTotal");

        verticalLayout_2->addWidget(labelTodayTotal);

        labelTodayConnected = new QLabel(frameToday);
        labelTodayConnected->setObjectName("labelTodayConnected");

        verticalLayout_2->addWidget(labelTodayConnected);

        labelTodayMissed = new QLabel(frameToday);
        labelTodayMissed->setObjectName("labelTodayMissed");

        verticalLayout_2->addWidget(labelTodayMissed);

        labelTodayIncoming = new QLabel(frameToday);
        labelTodayIncoming->setObjectName("labelTodayIncoming");

        verticalLayout_2->addWidget(labelTodayIncoming);

        labelTodayOutgoing = new QLabel(frameToday);
        labelTodayOutgoing->setObjectName("labelTodayOutgoing");

        verticalLayout_2->addWidget(labelTodayOutgoing);


        gridLayout->addWidget(frameToday, 0, 0, 1, 1);

        frameLive = new QFrame(Dashboard);
        frameLive->setObjectName("frameLive");
        frameLive->setFrameShape(QFrame::StyledPanel);
        frameLive->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frameLive);
        verticalLayout_3->setObjectName("verticalLayout_3");
        labelLiveHeader = new QLabel(frameLive);
        labelLiveHeader->setObjectName("labelLiveHeader");
        labelLiveHeader->setFont(font1);

        verticalLayout_3->addWidget(labelLiveHeader);

        labelActiveCalls = new QLabel(frameLive);
        labelActiveCalls->setObjectName("labelActiveCalls");

        verticalLayout_3->addWidget(labelActiveCalls);

        labelActiveIncoming = new QLabel(frameLive);
        labelActiveIncoming->setObjectName("labelActiveIncoming");

        verticalLayout_3->addWidget(labelActiveIncoming);

        labelActiveOutgoing = new QLabel(frameLive);
        labelActiveOutgoing->setObjectName("labelActiveOutgoing");

        verticalLayout_3->addWidget(labelActiveOutgoing);


        gridLayout->addWidget(frameLive, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(Dashboard);

        QMetaObject::connectSlotsByName(Dashboard);
    } // setupUi

    void retranslateUi(QWidget *Dashboard)
    {
        Dashboard->setWindowTitle(QCoreApplication::translate("Dashboard", "Dashboard", nullptr));
        labelTitle->setText(QCoreApplication::translate("Dashboard", "Voice Logger Dashboard", nullptr));
        labelTodayHeader->setText(QCoreApplication::translate("Dashboard", "Today's Statistics", nullptr));
        labelTodayTotal->setText(QCoreApplication::translate("Dashboard", "Total Calls: 0", nullptr));
        labelTodayConnected->setText(QCoreApplication::translate("Dashboard", "Connected: 0", nullptr));
        labelTodayMissed->setText(QCoreApplication::translate("Dashboard", "Missed: 0", nullptr));
        labelTodayIncoming->setText(QCoreApplication::translate("Dashboard", "Incoming: 0", nullptr));
        labelTodayOutgoing->setText(QCoreApplication::translate("Dashboard", "Outgoing: 0", nullptr));
        labelLiveHeader->setText(QCoreApplication::translate("Dashboard", "Live Status", nullptr));
        labelActiveCalls->setText(QCoreApplication::translate("Dashboard", "Active Calls: 0", nullptr));
        labelActiveIncoming->setText(QCoreApplication::translate("Dashboard", "Active Incoming: 0", nullptr));
        labelActiveOutgoing->setText(QCoreApplication::translate("Dashboard", "Active Outgoing: 0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dashboard: public Ui_Dashboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DASHBOARD_H

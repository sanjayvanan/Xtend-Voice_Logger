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
    QFrame *frameStats;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelTotalCalls;
    QLabel *labelConnectedCalls;
    QLabel *labelActiveCalls;

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
        frameStats = new QFrame(Dashboard);
        frameStats->setObjectName("frameStats");
        frameStats->setFrameShape(QFrame::StyledPanel);
        frameStats->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frameStats);
        verticalLayout_2->setObjectName("verticalLayout_2");
        labelTotalCalls = new QLabel(frameStats);
        labelTotalCalls->setObjectName("labelTotalCalls");
        QFont font1;
        font1.setPointSize(12);
        labelTotalCalls->setFont(font1);

        verticalLayout_2->addWidget(labelTotalCalls);

        labelConnectedCalls = new QLabel(frameStats);
        labelConnectedCalls->setObjectName("labelConnectedCalls");
        labelConnectedCalls->setFont(font1);

        verticalLayout_2->addWidget(labelConnectedCalls);

        labelActiveCalls = new QLabel(frameStats);
        labelActiveCalls->setObjectName("labelActiveCalls");
        labelActiveCalls->setFont(font1);

        verticalLayout_2->addWidget(labelActiveCalls);


        gridLayout->addWidget(frameStats, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(Dashboard);

        QMetaObject::connectSlotsByName(Dashboard);
    } // setupUi

    void retranslateUi(QWidget *Dashboard)
    {
        Dashboard->setWindowTitle(QCoreApplication::translate("Dashboard", "Dashboard", nullptr));
        labelTitle->setText(QCoreApplication::translate("Dashboard", "Voice Logger Dashboard", nullptr));
        labelTotalCalls->setText(QCoreApplication::translate("Dashboard", "Total Calls: 0", nullptr));
        labelConnectedCalls->setText(QCoreApplication::translate("Dashboard", "Connected Calls: 0", nullptr));
        labelActiveCalls->setText(QCoreApplication::translate("Dashboard", "Active Calls: 0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dashboard: public Ui_Dashboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DASHBOARD_H

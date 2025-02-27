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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dashboard
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTitle;
    QHBoxLayout *horizontalLayout;
    QFrame *frameStats;
    QHBoxLayout *horizontalLayout_2;
    QFrame *statTotal;
    QVBoxLayout *verticalLayout_4;
    QLabel *labelStatTotal;
    QLabel *labelStatTotalText;
    QFrame *statConnected;
    QVBoxLayout *verticalLayout_5;
    QLabel *labelStatConnected;
    QLabel *labelStatConnectedText;
    QFrame *statMissed;
    QVBoxLayout *verticalLayout_6;
    QLabel *labelStatMissed;
    QLabel *labelStatMissedText;
    QFrame *statActive;
    QVBoxLayout *verticalLayout_7;
    QLabel *labelStatActive;
    QLabel *labelStatActiveText;
    QHBoxLayout *horizontalLayout_3;
    QFrame *frameCallTypes;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelHeaderCallTypes;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelIncoming;
    QProgressBar *progressIncoming;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelOutgoing;
    QProgressBar *progressOutgoing;
    QSpacerItem *verticalSpacer;
    QFrame *frameCallStatus;
    QVBoxLayout *verticalLayout_3;
    QLabel *labelHeaderCallStatus;
    QHBoxLayout *horizontalLayout_6;
    QLabel *labelConnected;
    QProgressBar *progressConnected;
    QHBoxLayout *horizontalLayout_7;
    QLabel *labelMissed;
    QProgressBar *progressMissed;
    QSpacerItem *verticalSpacer_2;
    QFrame *frameLiveStatus;
    QVBoxLayout *verticalLayout_8;
    QLabel *labelHeaderLiveStatus;
    QHBoxLayout *horizontalLayout_8;
    QFrame *frameLiveIncoming;
    QVBoxLayout *verticalLayout_9;
    QLabel *labelLiveIncoming;
    QLabel *labelLiveIncomingText;
    QFrame *frameLiveOutgoing;
    QVBoxLayout *verticalLayout_10;
    QLabel *labelLiveOutgoing;
    QLabel *labelLiveOutgoingText;

    void setupUi(QWidget *Dashboard)
    {
        if (Dashboard->objectName().isEmpty())
            Dashboard->setObjectName("Dashboard");
        Dashboard->resize(800, 600);
        Dashboard->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-color: #f5f5f5;\n"
"    color: #333333;\n"
"}\n"
"QFrame {\n"
"    border-radius: 8px;\n"
"    background-color: white;\n"
"    border: 1px solid #e0e0e0;\n"
"}\n"
"QLabel {\n"
"    color: #333333;\n"
"}\n"
"QLabel[objectName^=\"labelHeader\"] {\n"
"    color: #2c3e50;\n"
"    font-weight: bold;\n"
"}\n"
"QLabel[objectName^=\"labelTitle\"] {\n"
"    color: #2c3e50;\n"
"    font-weight: bold;\n"
"}\n"
"QLabel[objectName^=\"labelStat\"] {\n"
"     font-size: 24px;\n"
"    padding: 10px;\n"
"    min-height: 40px;\n"
"}\n"
"QProgressBar {\n"
"    border: none;\n"
"    border-radius: 4px;\n"
"    background-color: #ecf0f1;\n"
"    text-align: center;\n"
"}\n"
"QProgressBar::chunk {\n"
"    border-radius: 4px;\n"
"}\n"
"#progressIncoming::chunk { background-color: #3498db; }\n"
"#progressOutgoing::chunk { background-color: #2ecc71; }\n"
"#progressConnected::chunk { background-color: #27ae60; }\n"
"#progressMissed::chunk { background-color: #e74c3c; }\n"
""));
        verticalLayout = new QVBoxLayout(Dashboard);
        verticalLayout->setSpacing(16);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(16, 16, 16, 16);
        labelTitle = new QLabel(Dashboard);
        labelTitle->setObjectName("labelTitle");
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        labelTitle->setFont(font);

        verticalLayout->addWidget(labelTitle);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(16);
        horizontalLayout->setObjectName("horizontalLayout");
        frameStats = new QFrame(Dashboard);
        frameStats->setObjectName("frameStats");
        frameStats->setMinimumSize(QSize(0, 180));
        frameStats->setFrameShape(QFrame::Shape::StyledPanel);
        frameStats->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_2 = new QHBoxLayout(frameStats);
        horizontalLayout_2->setSpacing(24);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        statTotal = new QFrame(frameStats);
        statTotal->setObjectName("statTotal");
        statTotal->setStyleSheet(QString::fromUtf8("background-color: #3498db;\n"
"color: white;\n"
"border: none;"));
        statTotal->setFrameShape(QFrame::Shape::StyledPanel);
        statTotal->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_4 = new QVBoxLayout(statTotal);
        verticalLayout_4->setObjectName("verticalLayout_4");
        labelStatTotal = new QLabel(statTotal);
        labelStatTotal->setObjectName("labelStatTotal");
        QFont font1;
        font1.setBold(true);
        labelStatTotal->setFont(font1);
        labelStatTotal->setStyleSheet(QString::fromUtf8("color: white;"));
        labelStatTotal->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(labelStatTotal);

        labelStatTotalText = new QLabel(statTotal);
        labelStatTotalText->setObjectName("labelStatTotalText");
        labelStatTotalText->setStyleSheet(QString::fromUtf8("color: white;"));
        labelStatTotalText->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(labelStatTotalText);


        horizontalLayout_2->addWidget(statTotal);

        statConnected = new QFrame(frameStats);
        statConnected->setObjectName("statConnected");
        statConnected->setStyleSheet(QString::fromUtf8("background-color: #27ae60;\n"
"color: white;\n"
"border: none;"));
        statConnected->setFrameShape(QFrame::Shape::StyledPanel);
        statConnected->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_5 = new QVBoxLayout(statConnected);
        verticalLayout_5->setObjectName("verticalLayout_5");
        labelStatConnected = new QLabel(statConnected);
        labelStatConnected->setObjectName("labelStatConnected");
        labelStatConnected->setFont(font1);
        labelStatConnected->setStyleSheet(QString::fromUtf8("color: white;"));
        labelStatConnected->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_5->addWidget(labelStatConnected);

        labelStatConnectedText = new QLabel(statConnected);
        labelStatConnectedText->setObjectName("labelStatConnectedText");
        labelStatConnectedText->setStyleSheet(QString::fromUtf8("color: white;"));
        labelStatConnectedText->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_5->addWidget(labelStatConnectedText);


        horizontalLayout_2->addWidget(statConnected);

        statMissed = new QFrame(frameStats);
        statMissed->setObjectName("statMissed");
        statMissed->setStyleSheet(QString::fromUtf8("background-color: #e74c3c;\n"
"color: white;\n"
"border: none;"));
        statMissed->setFrameShape(QFrame::Shape::StyledPanel);
        statMissed->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_6 = new QVBoxLayout(statMissed);
        verticalLayout_6->setObjectName("verticalLayout_6");
        labelStatMissed = new QLabel(statMissed);
        labelStatMissed->setObjectName("labelStatMissed");
        labelStatMissed->setFont(font1);
        labelStatMissed->setStyleSheet(QString::fromUtf8("color: white;"));
        labelStatMissed->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_6->addWidget(labelStatMissed);

        labelStatMissedText = new QLabel(statMissed);
        labelStatMissedText->setObjectName("labelStatMissedText");
        labelStatMissedText->setStyleSheet(QString::fromUtf8("color: white;"));
        labelStatMissedText->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_6->addWidget(labelStatMissedText);


        horizontalLayout_2->addWidget(statMissed);

        statActive = new QFrame(frameStats);
        statActive->setObjectName("statActive");
        statActive->setStyleSheet(QString::fromUtf8("background-color: #f39c12;\n"
"color: white;\n"
"border: none;"));
        statActive->setFrameShape(QFrame::Shape::StyledPanel);
        statActive->setFrameShadow(QFrame::Shadow::Raised);
        statActive->setLineWidth(1);
        verticalLayout_7 = new QVBoxLayout(statActive);
        verticalLayout_7->setSpacing(3);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        labelStatActive = new QLabel(statActive);
        labelStatActive->setObjectName("labelStatActive");
        labelStatActive->setFont(font1);
        labelStatActive->setStyleSheet(QString::fromUtf8("color: white;"));
        labelStatActive->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_7->addWidget(labelStatActive);

        labelStatActiveText = new QLabel(statActive);
        labelStatActiveText->setObjectName("labelStatActiveText");
        labelStatActiveText->setStyleSheet(QString::fromUtf8("color: white;"));
        labelStatActiveText->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_7->addWidget(labelStatActiveText);


        horizontalLayout_2->addWidget(statActive);


        horizontalLayout->addWidget(frameStats);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(16);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        frameCallTypes = new QFrame(Dashboard);
        frameCallTypes->setObjectName("frameCallTypes");
        frameCallTypes->setMinimumSize(QSize(100, 50));
        frameCallTypes->setFrameShape(QFrame::Shape::StyledPanel);
        frameCallTypes->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_2 = new QVBoxLayout(frameCallTypes);
        verticalLayout_2->setObjectName("verticalLayout_2");
        labelHeaderCallTypes = new QLabel(frameCallTypes);
        labelHeaderCallTypes->setObjectName("labelHeaderCallTypes");
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        labelHeaderCallTypes->setFont(font2);

        verticalLayout_2->addWidget(labelHeaderCallTypes);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        labelIncoming = new QLabel(frameCallTypes);
        labelIncoming->setObjectName("labelIncoming");
        labelIncoming->setMinimumSize(QSize(100, 0));

        horizontalLayout_4->addWidget(labelIncoming);

        progressIncoming = new QProgressBar(frameCallTypes);
        progressIncoming->setObjectName("progressIncoming");
        progressIncoming->setValue(0);

        horizontalLayout_4->addWidget(progressIncoming);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        labelOutgoing = new QLabel(frameCallTypes);
        labelOutgoing->setObjectName("labelOutgoing");
        labelOutgoing->setMinimumSize(QSize(100, 0));

        horizontalLayout_5->addWidget(labelOutgoing);

        progressOutgoing = new QProgressBar(frameCallTypes);
        progressOutgoing->setObjectName("progressOutgoing");
        progressOutgoing->setValue(0);

        horizontalLayout_5->addWidget(progressOutgoing);


        verticalLayout_2->addLayout(horizontalLayout_5);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_3->addWidget(frameCallTypes);

        frameCallStatus = new QFrame(Dashboard);
        frameCallStatus->setObjectName("frameCallStatus");
        frameCallStatus->setMinimumSize(QSize(0, 200));
        frameCallStatus->setFrameShape(QFrame::Shape::StyledPanel);
        frameCallStatus->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_3 = new QVBoxLayout(frameCallStatus);
        verticalLayout_3->setObjectName("verticalLayout_3");
        labelHeaderCallStatus = new QLabel(frameCallStatus);
        labelHeaderCallStatus->setObjectName("labelHeaderCallStatus");
        labelHeaderCallStatus->setFont(font2);

        verticalLayout_3->addWidget(labelHeaderCallStatus);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        labelConnected = new QLabel(frameCallStatus);
        labelConnected->setObjectName("labelConnected");
        labelConnected->setMinimumSize(QSize(100, 0));

        horizontalLayout_6->addWidget(labelConnected);

        progressConnected = new QProgressBar(frameCallStatus);
        progressConnected->setObjectName("progressConnected");
        progressConnected->setValue(0);

        horizontalLayout_6->addWidget(progressConnected);


        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        labelMissed = new QLabel(frameCallStatus);
        labelMissed->setObjectName("labelMissed");
        labelMissed->setMinimumSize(QSize(100, 0));

        horizontalLayout_7->addWidget(labelMissed);

        progressMissed = new QProgressBar(frameCallStatus);
        progressMissed->setObjectName("progressMissed");
        progressMissed->setValue(0);

        horizontalLayout_7->addWidget(progressMissed);


        verticalLayout_3->addLayout(horizontalLayout_7);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);


        horizontalLayout_3->addWidget(frameCallStatus);


        verticalLayout->addLayout(horizontalLayout_3);

        frameLiveStatus = new QFrame(Dashboard);
        frameLiveStatus->setObjectName("frameLiveStatus");
        frameLiveStatus->setMinimumSize(QSize(0, 150));
        frameLiveStatus->setFrameShape(QFrame::Shape::StyledPanel);
        frameLiveStatus->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_8 = new QVBoxLayout(frameLiveStatus);
        verticalLayout_8->setObjectName("verticalLayout_8");
        labelHeaderLiveStatus = new QLabel(frameLiveStatus);
        labelHeaderLiveStatus->setObjectName("labelHeaderLiveStatus");
        QFont font3;
        font3.setPointSize(24);
        font3.setBold(true);
        labelHeaderLiveStatus->setFont(font3);

        verticalLayout_8->addWidget(labelHeaderLiveStatus);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        frameLiveIncoming = new QFrame(frameLiveStatus);
        frameLiveIncoming->setObjectName("frameLiveIncoming");
        frameLiveIncoming->setStyleSheet(QString::fromUtf8("background-color: #3498db;\n"
"color: white;\n"
"border-radius: 8px;"));
        frameLiveIncoming->setFrameShape(QFrame::Shape::StyledPanel);
        frameLiveIncoming->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_9 = new QVBoxLayout(frameLiveIncoming);
        verticalLayout_9->setObjectName("verticalLayout_9");
        labelLiveIncoming = new QLabel(frameLiveIncoming);
        labelLiveIncoming->setObjectName("labelLiveIncoming");
        QFont font4;
        font4.setPointSize(18);
        font4.setBold(true);
        labelLiveIncoming->setFont(font4);
        labelLiveIncoming->setStyleSheet(QString::fromUtf8("color: white;"));
        labelLiveIncoming->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_9->addWidget(labelLiveIncoming);

        labelLiveIncomingText = new QLabel(frameLiveIncoming);
        labelLiveIncomingText->setObjectName("labelLiveIncomingText");
        labelLiveIncomingText->setStyleSheet(QString::fromUtf8("color: white;"));
        labelLiveIncomingText->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_9->addWidget(labelLiveIncomingText);


        horizontalLayout_8->addWidget(frameLiveIncoming);

        frameLiveOutgoing = new QFrame(frameLiveStatus);
        frameLiveOutgoing->setObjectName("frameLiveOutgoing");
        frameLiveOutgoing->setStyleSheet(QString::fromUtf8("background-color: #2ecc71;\n"
"color: white;\n"
"border-radius: 8px;"));
        frameLiveOutgoing->setFrameShape(QFrame::Shape::StyledPanel);
        frameLiveOutgoing->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_10 = new QVBoxLayout(frameLiveOutgoing);
        verticalLayout_10->setObjectName("verticalLayout_10");
        labelLiveOutgoing = new QLabel(frameLiveOutgoing);
        labelLiveOutgoing->setObjectName("labelLiveOutgoing");
        labelLiveOutgoing->setFont(font4);
        labelLiveOutgoing->setStyleSheet(QString::fromUtf8("color: white;"));
        labelLiveOutgoing->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_10->addWidget(labelLiveOutgoing);

        labelLiveOutgoingText = new QLabel(frameLiveOutgoing);
        labelLiveOutgoingText->setObjectName("labelLiveOutgoingText");
        labelLiveOutgoingText->setStyleSheet(QString::fromUtf8("color: white;"));
        labelLiveOutgoingText->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_10->addWidget(labelLiveOutgoingText);


        horizontalLayout_8->addWidget(frameLiveOutgoing);


        verticalLayout_8->addLayout(horizontalLayout_8);


        verticalLayout->addWidget(frameLiveStatus);


        retranslateUi(Dashboard);

        QMetaObject::connectSlotsByName(Dashboard);
    } // setupUi

    void retranslateUi(QWidget *Dashboard)
    {
        Dashboard->setWindowTitle(QCoreApplication::translate("Dashboard", "Dashboard", nullptr));
        labelTitle->setText(QCoreApplication::translate("Dashboard", "Dashboard Overview", nullptr));
        labelStatTotal->setText(QCoreApplication::translate("Dashboard", "0", nullptr));
        labelStatTotalText->setText(QCoreApplication::translate("Dashboard", "Total Calls", nullptr));
        labelStatConnected->setText(QCoreApplication::translate("Dashboard", "0", nullptr));
        labelStatConnectedText->setText(QCoreApplication::translate("Dashboard", "Connected", nullptr));
        labelStatMissed->setText(QCoreApplication::translate("Dashboard", "0", nullptr));
        labelStatMissedText->setText(QCoreApplication::translate("Dashboard", "Missed", nullptr));
        labelStatActive->setText(QCoreApplication::translate("Dashboard", "0", nullptr));
        labelStatActiveText->setText(QCoreApplication::translate("Dashboard", "Active Calls", nullptr));
        labelHeaderCallTypes->setText(QCoreApplication::translate("Dashboard", "Call Types", nullptr));
        labelIncoming->setText(QCoreApplication::translate("Dashboard", "Incoming:", nullptr));
        progressIncoming->setFormat(QCoreApplication::translate("Dashboard", "%v", nullptr));
        labelOutgoing->setText(QCoreApplication::translate("Dashboard", "Outgoing:", nullptr));
        progressOutgoing->setFormat(QCoreApplication::translate("Dashboard", "%v", nullptr));
        labelHeaderCallStatus->setText(QCoreApplication::translate("Dashboard", "Call Status", nullptr));
        labelConnected->setText(QCoreApplication::translate("Dashboard", "Connected:", nullptr));
        progressConnected->setFormat(QCoreApplication::translate("Dashboard", "%v", nullptr));
        labelMissed->setText(QCoreApplication::translate("Dashboard", "Missed:", nullptr));
        progressMissed->setFormat(QCoreApplication::translate("Dashboard", "%v", nullptr));
        labelHeaderLiveStatus->setText(QCoreApplication::translate("Dashboard", "Live Status", nullptr));
        labelLiveIncoming->setText(QCoreApplication::translate("Dashboard", "0", nullptr));
        labelLiveIncomingText->setText(QCoreApplication::translate("Dashboard", "Active Incoming", nullptr));
        labelLiveOutgoing->setText(QCoreApplication::translate("Dashboard", "0", nullptr));
        labelLiveOutgoingText->setText(QCoreApplication::translate("Dashboard", "Active Outgoing", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dashboard: public Ui_Dashboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DASHBOARD_H

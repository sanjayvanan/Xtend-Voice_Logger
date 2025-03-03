/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainLayout;
    QWidget *navBar;
    QHBoxLayout *navBarLayout;
    QVBoxLayout *titleLayout;
    QLabel *labelTitle;
    QFrame *titleLine;
    QSpacerItem *horizontalSpacer;
    QLabel *labelUserName;
    QPushButton *btnUserManagement;
    QPushButton *btnLogout;
    QHBoxLayout *horizontalLayout;
    QWidget *sideBar;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btnDashboard;
    QPushButton *btnLiveCalls;
    QPushButton *btnTimeTime;
    QSpacerItem *verticalSpacer;
    QStackedWidget *stackedWidget;
    QWidget *pageDashboard;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QWidget *pageCallLogs;
    QVBoxLayout *verticalLayout_3;
    QLabel *labelTotalCalls;
    QTableWidget *tableWidget;
    QWidget *pageLiveCalls;
    QVBoxLayout *verticalLayout_4;
    QLabel *labelLiveCallsStatus;
    QTableWidget *tableLiveCalls;
    QWidget *pageUsers;
    QVBoxLayout *verticalLayout_5;
    QTableWidget *tableUsers;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1217, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainLayout = new QVBoxLayout(centralwidget);
        mainLayout->setSpacing(0);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(0, 0, 0, 0);
        navBar = new QWidget(centralwidget);
        navBar->setObjectName("navBar");
        navBar->setMinimumSize(QSize(0, 50));
        navBar->setMaximumSize(QSize(16777215, 50));
        navBar->setStyleSheet(QString::fromUtf8("background-color: #2C3E50;"));
        navBarLayout = new QHBoxLayout(navBar);
        navBarLayout->setObjectName("navBarLayout");
        navBarLayout->setContentsMargins(15, 0, 15, 0);
        titleLayout = new QVBoxLayout();
        titleLayout->setSpacing(2);
        titleLayout->setObjectName("titleLayout");
        labelTitle = new QLabel(navBar);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setStyleSheet(QString::fromUtf8("color: white; font-size: 16px; font-weight: bold;"));

        titleLayout->addWidget(labelTitle);

        titleLine = new QFrame(navBar);
        titleLine->setObjectName("titleLine");
        titleLine->setMinimumSize(QSize(150, 2));
        titleLine->setMaximumSize(QSize(150, 2));
        titleLine->setStyleSheet(QString::fromUtf8("background-color: #3498db;"));
        titleLine->setFrameShape(QFrame::Shape::HLine);
        titleLine->setFrameShadow(QFrame::Shadow::Sunken);

        titleLayout->addWidget(titleLine);


        navBarLayout->addLayout(titleLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        navBarLayout->addItem(horizontalSpacer);

        labelUserName = new QLabel(navBar);
        labelUserName->setObjectName("labelUserName");
        labelUserName->setStyleSheet(QString::fromUtf8("color: white;"));

        navBarLayout->addWidget(labelUserName);

        btnUserManagement = new QPushButton(navBar);
        btnUserManagement->setObjectName("btnUserManagement");
        btnUserManagement->setStyleSheet(QString::fromUtf8("\n"
"           QPushButton {\n"
"               color: white;\n"
"               background-color: #2980b9;\n"
"               border: none;\n"
"               border-radius: 4px;\n"
"               padding: 5px 15px;\n"
"           }\n"
"           QPushButton:hover {\n"
"               background-color: #3498db;\n"
"           }\n"
"          "));

        navBarLayout->addWidget(btnUserManagement);

        btnLogout = new QPushButton(navBar);
        btnLogout->setObjectName("btnLogout");
        btnLogout->setMinimumSize(QSize(100, 30));
        btnLogout->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnLogout->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    color: white;\n"
"    background-color: #e74c3c;\n"
"    border: none;\n"
"    border-radius: 4px;\n"
"    padding: 5px 15px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #c0392b;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #a93226;\n"
"}"));

        navBarLayout->addWidget(btnLogout);


        mainLayout->addWidget(navBar);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        sideBar = new QWidget(centralwidget);
        sideBar->setObjectName("sideBar");
        sideBar->setMinimumSize(QSize(180, 0));
        sideBar->setMaximumSize(QSize(16777215, 16777215));
        sideBar->setStyleSheet(QString::fromUtf8("background-color: #2C3E50;"));
        verticalLayout_2 = new QVBoxLayout(sideBar);
        verticalLayout_2->setSpacing(5);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 10, 0, 0);
        btnDashboard = new QPushButton(sideBar);
        btnDashboard->setObjectName("btnDashboard");
        btnDashboard->setMinimumSize(QSize(0, 40));
        btnDashboard->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnDashboard->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    color: white;\n"
"    border: none;\n"
"    text-align: left;\n"
"    padding-left: 15px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #34495E;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #2980B9;\n"
"}"));

        verticalLayout_2->addWidget(btnDashboard);

        btnLiveCalls = new QPushButton(sideBar);
        btnLiveCalls->setObjectName("btnLiveCalls");
        btnLiveCalls->setMinimumSize(QSize(0, 40));
        btnLiveCalls->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnLiveCalls->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    color: white;\n"
"    border: none;\n"
"    text-align: left;\n"
"    padding-left: 15px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #34495E;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #2980B9;\n"
"}"));

        verticalLayout_2->addWidget(btnLiveCalls);

        btnTimeTime = new QPushButton(sideBar);
        btnTimeTime->setObjectName("btnTimeTime");
        btnTimeTime->setMinimumSize(QSize(0, 40));
        btnTimeTime->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnTimeTime->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    color: white;\n"
"    border: none;\n"
"    text-align: left;\n"
"    padding-left: 15px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #34495E;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #2980B9;\n"
"}"));

        verticalLayout_2->addWidget(btnTimeTime);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout->addWidget(sideBar);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        pageDashboard = new QWidget();
        pageDashboard->setObjectName("pageDashboard");
        verticalLayout = new QVBoxLayout(pageDashboard);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(pageDashboard);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        stackedWidget->addWidget(pageDashboard);
        pageCallLogs = new QWidget();
        pageCallLogs->setObjectName("pageCallLogs");
        verticalLayout_3 = new QVBoxLayout(pageCallLogs);
        verticalLayout_3->setObjectName("verticalLayout_3");
        labelTotalCalls = new QLabel(pageCallLogs);
        labelTotalCalls->setObjectName("labelTotalCalls");

        verticalLayout_3->addWidget(labelTotalCalls);

        tableWidget = new QTableWidget(pageCallLogs);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidget->setObjectName("tableWidget");

        verticalLayout_3->addWidget(tableWidget);

        stackedWidget->addWidget(pageCallLogs);
        pageLiveCalls = new QWidget();
        pageLiveCalls->setObjectName("pageLiveCalls");
        verticalLayout_4 = new QVBoxLayout(pageLiveCalls);
        verticalLayout_4->setObjectName("verticalLayout_4");
        labelLiveCallsStatus = new QLabel(pageLiveCalls);
        labelLiveCallsStatus->setObjectName("labelLiveCallsStatus");

        verticalLayout_4->addWidget(labelLiveCallsStatus);

        tableLiveCalls = new QTableWidget(pageLiveCalls);
        if (tableLiveCalls->columnCount() < 8)
            tableLiveCalls->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableLiveCalls->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableLiveCalls->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableLiveCalls->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableLiveCalls->setHorizontalHeaderItem(3, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableLiveCalls->setHorizontalHeaderItem(4, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableLiveCalls->setHorizontalHeaderItem(5, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableLiveCalls->setHorizontalHeaderItem(6, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableLiveCalls->setHorizontalHeaderItem(7, __qtablewidgetitem13);
        tableLiveCalls->setObjectName("tableLiveCalls");

        verticalLayout_4->addWidget(tableLiveCalls);

        stackedWidget->addWidget(pageLiveCalls);
        pageUsers = new QWidget();
        pageUsers->setObjectName("pageUsers");
        verticalLayout_5 = new QVBoxLayout(pageUsers);
        verticalLayout_5->setObjectName("verticalLayout_5");
        tableUsers = new QTableWidget(pageUsers);
        if (tableUsers->columnCount() < 3)
            tableUsers->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableUsers->setHorizontalHeaderItem(0, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableUsers->setHorizontalHeaderItem(1, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableUsers->setHorizontalHeaderItem(2, __qtablewidgetitem16);
        tableUsers->setObjectName("tableUsers");
        tableUsers->setColumnCount(3);

        verticalLayout_5->addWidget(tableUsers);

        stackedWidget->addWidget(pageUsers);

        horizontalLayout->addWidget(stackedWidget);


        mainLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        labelTitle->setText(QCoreApplication::translate("MainWindow", "Zosh Voice Logger", nullptr));
        btnUserManagement->setText(QCoreApplication::translate("MainWindow", "User Management", nullptr));
        btnLogout->setText(QCoreApplication::translate("MainWindow", "Logout", nullptr));
        btnDashboard->setText(QCoreApplication::translate("MainWindow", "Dashboard", nullptr));
        btnLiveCalls->setText(QCoreApplication::translate("MainWindow", "Live Calls", nullptr));
        btnTimeTime->setText(QCoreApplication::translate("MainWindow", "Time to Time", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Dashboard Page", nullptr));
        labelTotalCalls->setText(QCoreApplication::translate("MainWindow", "Total Connected Calls: 0", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Call Ref ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Channel", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Call Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Call Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Duration", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Status", nullptr));
        labelLiveCallsStatus->setText(QCoreApplication::translate("MainWindow", "Active Calls: 0", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableLiveCalls->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Channel", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableLiveCalls->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Channel Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableLiveCalls->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Call Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableLiveCalls->horizontalHeaderItem(3);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "Call Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableLiveCalls->horizontalHeaderItem(4);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "Caller ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableLiveCalls->horizontalHeaderItem(5);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "Called ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableLiveCalls->horizontalHeaderItem(6);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableLiveCalls->horizontalHeaderItem(7);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "Listen", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableUsers->horizontalHeaderItem(0);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableUsers->horizontalHeaderItem(1);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "Display Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableUsers->horizontalHeaderItem(2);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "Role", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

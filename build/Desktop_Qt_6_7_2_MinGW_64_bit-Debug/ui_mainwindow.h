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
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLogout;
    QWidget *centralwidget;
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
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1217, 600);
        actionLogout = new QAction(MainWindow);
        actionLogout->setObjectName("actionLogout");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        sideBar = new QWidget(centralwidget);
        sideBar->setObjectName("sideBar");
        sideBar->setMinimumSize(QSize(200, 0));
        sideBar->setMaximumSize(QSize(200, 16777215));
        sideBar->setStyleSheet(QString::fromUtf8("background-color: #2C3E50;"));
        verticalLayout_2 = new QVBoxLayout(sideBar);
        verticalLayout_2->setObjectName("verticalLayout_2");
        btnDashboard = new QPushButton(sideBar);
        btnDashboard->setObjectName("btnDashboard");
        btnDashboard->setMinimumSize(QSize(0, 40));
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

        horizontalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1217, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionLogout);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionLogout->setText(QCoreApplication::translate("MainWindow", "Logout", nullptr));
#if QT_CONFIG(shortcut)
        actionLogout->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+L", nullptr));
#endif // QT_CONFIG(shortcut)
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
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

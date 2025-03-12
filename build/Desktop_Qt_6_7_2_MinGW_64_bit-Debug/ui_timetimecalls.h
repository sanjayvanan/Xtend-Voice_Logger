/********************************************************************************
** Form generated from reading UI file 'timetimecalls.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMETIMECALLS_H
#define UI_TIMETIMECALLS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TimeTimeCalls
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QGroupBox *searchGroup;
    QGridLayout *gridLayout;
    QLabel *labelFromDate;
    QDateTimeEdit *fromDateTime;
    QLabel *labelToDate;
    QDateTimeEdit *toDateTime;
    QLabel *labelPhoneNo;
    QLineEdit *phoneNumber;
    QLabel *labelCallType;
    QComboBox *callTypeCombo;
    QLabel *labelPageSize;
    QSpinBox *pageSize;
    QPushButton *searchButton;
    QHBoxLayout *paginationLayout;
    QLabel *labelTotalCalls;
    QSpacerItem *horizontalSpacer;
    QLabel *labelPage;
    QPushButton *btnPrevPage;
    QSpinBox *currentPage;
    QPushButton *btnNextPage;
    QTableWidget *tableWidget;

    void setupUi(QWidget *TimeTimeCalls)
    {
        if (TimeTimeCalls->objectName().isEmpty())
            TimeTimeCalls->setObjectName("TimeTimeCalls");
        TimeTimeCalls->resize(1265, 654);
        TimeTimeCalls->setMinimumSize(QSize(800, 500));
        verticalLayout = new QVBoxLayout(TimeTimeCalls);
        verticalLayout->setSpacing(12);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(12, 12, 12, 12);
        label = new QLabel(TimeTimeCalls);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        label->setFont(font);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label);

        searchGroup = new QGroupBox(TimeTimeCalls);
        searchGroup->setObjectName("searchGroup");
        gridLayout = new QGridLayout(searchGroup);
        gridLayout->setContentsMargins(15, 15, 15, 15);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setHorizontalSpacing(15);
        gridLayout->setVerticalSpacing(10);
        labelFromDate = new QLabel(searchGroup);
        labelFromDate->setObjectName("labelFromDate");

        gridLayout->addWidget(labelFromDate, 0, 0, 1, 1);

        fromDateTime = new QDateTimeEdit(searchGroup);
        fromDateTime->setObjectName("fromDateTime");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(fromDateTime->sizePolicy().hasHeightForWidth());
        fromDateTime->setSizePolicy(sizePolicy);

        gridLayout->addWidget(fromDateTime, 0, 1, 1, 1);

        labelToDate = new QLabel(searchGroup);
        labelToDate->setObjectName("labelToDate");

        gridLayout->addWidget(labelToDate, 0, 2, 1, 1);

        toDateTime = new QDateTimeEdit(searchGroup);
        toDateTime->setObjectName("toDateTime");
        sizePolicy.setHeightForWidth(toDateTime->sizePolicy().hasHeightForWidth());
        toDateTime->setSizePolicy(sizePolicy);

        gridLayout->addWidget(toDateTime, 0, 3, 1, 1);

        labelPhoneNo = new QLabel(searchGroup);
        labelPhoneNo->setObjectName("labelPhoneNo");

        gridLayout->addWidget(labelPhoneNo, 1, 0, 1, 1);

        phoneNumber = new QLineEdit(searchGroup);
        phoneNumber->setObjectName("phoneNumber");
        sizePolicy.setHeightForWidth(phoneNumber->sizePolicy().hasHeightForWidth());
        phoneNumber->setSizePolicy(sizePolicy);

        gridLayout->addWidget(phoneNumber, 1, 1, 1, 1);

        labelCallType = new QLabel(searchGroup);
        labelCallType->setObjectName("labelCallType");

        gridLayout->addWidget(labelCallType, 1, 2, 1, 1);

        callTypeCombo = new QComboBox(searchGroup);
        callTypeCombo->addItem(QString());
        callTypeCombo->addItem(QString());
        callTypeCombo->addItem(QString());
        callTypeCombo->setObjectName("callTypeCombo");
        sizePolicy.setHeightForWidth(callTypeCombo->sizePolicy().hasHeightForWidth());
        callTypeCombo->setSizePolicy(sizePolicy);

        gridLayout->addWidget(callTypeCombo, 1, 3, 1, 1);

        labelPageSize = new QLabel(searchGroup);
        labelPageSize->setObjectName("labelPageSize");

        gridLayout->addWidget(labelPageSize, 2, 0, 1, 1);

        pageSize = new QSpinBox(searchGroup);
        pageSize->setObjectName("pageSize");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pageSize->sizePolicy().hasHeightForWidth());
        pageSize->setSizePolicy(sizePolicy1);
        pageSize->setMinimum(1);
        pageSize->setMaximum(1000);
        pageSize->setValue(50);

        gridLayout->addWidget(pageSize, 2, 1, 1, 1);

        searchButton = new QPushButton(searchGroup);
        searchButton->setObjectName("searchButton");
        sizePolicy1.setHeightForWidth(searchButton->sizePolicy().hasHeightForWidth());
        searchButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(searchButton, 2, 3, 1, 1);


        verticalLayout->addWidget(searchGroup);

        paginationLayout = new QHBoxLayout();
        paginationLayout->setObjectName("paginationLayout");
        labelTotalCalls = new QLabel(TimeTimeCalls);
        labelTotalCalls->setObjectName("labelTotalCalls");
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        labelTotalCalls->setFont(font1);

        paginationLayout->addWidget(labelTotalCalls);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        paginationLayout->addItem(horizontalSpacer);

        labelPage = new QLabel(TimeTimeCalls);
        labelPage->setObjectName("labelPage");
        labelPage->setFont(font1);

        paginationLayout->addWidget(labelPage);

        btnPrevPage = new QPushButton(TimeTimeCalls);
        btnPrevPage->setObjectName("btnPrevPage");
        btnPrevPage->setMinimumSize(QSize(40, 30));
        btnPrevPage->setMaximumSize(QSize(40, 30));
        btnPrevPage->setFont(font1);
        btnPrevPage->setStyleSheet(QString::fromUtf8("background-color: #3498db; color: white; border-radius: 4px;"));

        paginationLayout->addWidget(btnPrevPage);

        currentPage = new QSpinBox(TimeTimeCalls);
        currentPage->setObjectName("currentPage");
        currentPage->setMinimumSize(QSize(70, 30));
        QFont font2;
        font2.setPointSize(10);
        currentPage->setFont(font2);
        currentPage->setStyleSheet(QString::fromUtf8("padding: 2px 5px;"));
        currentPage->setMinimum(1);
        currentPage->setMaximum(999999);

        paginationLayout->addWidget(currentPage);

        btnNextPage = new QPushButton(TimeTimeCalls);
        btnNextPage->setObjectName("btnNextPage");
        btnNextPage->setMinimumSize(QSize(40, 30));
        btnNextPage->setMaximumSize(QSize(40, 30));
        btnNextPage->setFont(font1);
        btnNextPage->setStyleSheet(QString::fromUtf8("background-color: #3498db; color: white; border-radius: 4px;"));

        paginationLayout->addWidget(btnNextPage);


        verticalLayout->addLayout(paginationLayout);

        tableWidget = new QTableWidget(TimeTimeCalls);
        if (tableWidget->columnCount() < 11)
            tableWidget->setColumnCount(11);
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
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        tableWidget->setObjectName("tableWidget");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy2);
        tableWidget->setAlternatingRowColors(true);
        tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        verticalLayout->addWidget(tableWidget);


        retranslateUi(TimeTimeCalls);

        QMetaObject::connectSlotsByName(TimeTimeCalls);
    } // setupUi

    void retranslateUi(QWidget *TimeTimeCalls)
    {
        label->setText(QCoreApplication::translate("TimeTimeCalls", "Time to Time Call Search", nullptr));
        searchGroup->setTitle(QCoreApplication::translate("TimeTimeCalls", ".", nullptr));
        labelFromDate->setText(QCoreApplication::translate("TimeTimeCalls", "From Date:", nullptr));
        labelToDate->setText(QCoreApplication::translate("TimeTimeCalls", "To Date:", nullptr));
        labelPhoneNo->setText(QCoreApplication::translate("TimeTimeCalls", "Phone Number:", nullptr));
        labelCallType->setText(QCoreApplication::translate("TimeTimeCalls", "Call Type:", nullptr));
        callTypeCombo->setItemText(0, QCoreApplication::translate("TimeTimeCalls", "All", nullptr));
        callTypeCombo->setItemText(1, QCoreApplication::translate("TimeTimeCalls", "Incoming", nullptr));
        callTypeCombo->setItemText(2, QCoreApplication::translate("TimeTimeCalls", "Outgoing", nullptr));

        labelPageSize->setText(QCoreApplication::translate("TimeTimeCalls", "Page Size:", nullptr));
        searchButton->setText(QCoreApplication::translate("TimeTimeCalls", "Search", nullptr));
        labelTotalCalls->setText(QCoreApplication::translate("TimeTimeCalls", "Total Connected Calls: 0", nullptr));
        labelPage->setText(QCoreApplication::translate("TimeTimeCalls", "Page:", nullptr));
        btnPrevPage->setText(QCoreApplication::translate("TimeTimeCalls", "<", nullptr));
        btnNextPage->setText(QCoreApplication::translate("TimeTimeCalls", ">", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("TimeTimeCalls", "Play", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("TimeTimeCalls", "Channel", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("TimeTimeCalls", "Call Ref ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("TimeTimeCalls", "Call Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("TimeTimeCalls", "Call Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("TimeTimeCalls", "Call Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("TimeTimeCalls", "Duration", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("TimeTimeCalls", "Ring Duration", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("TimeTimeCalls", "Connect Duration", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("TimeTimeCalls", "Compression", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("TimeTimeCalls", "Channel Hardware", nullptr));
        (void)TimeTimeCalls;
    } // retranslateUi

};

namespace Ui {
    class TimeTimeCalls: public Ui_TimeTimeCalls {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMETIMECALLS_H

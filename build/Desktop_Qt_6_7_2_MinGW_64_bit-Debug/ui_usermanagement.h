/********************************************************************************
** Form generated from reading UI file 'usermanagement.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERMANAGEMENT_H
#define UI_USERMANAGEMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserManagement
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QTabWidget *tabWidget;
    QWidget *userTab;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *formGroupBox;
    QFormLayout *formLayout;
    QLabel *usernameLabel;
    QLineEdit *usernameEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordEdit;
    QLabel *roleLabel;
    QComboBox *roleCombo;
    QHBoxLayout *buttonLayout;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QPushButton *clearButton;
    QTableWidget *userTable;
    QWidget *channelTab;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *channelGroupBox;
    QFormLayout *formLayout_2;
    QLabel *groupNameLabel;
    QLineEdit *groupNameEdit;
    QLabel *channelsLabel;
    QHBoxLayout *horizontalLayout;
    QCheckBox *channel1Check;
    QCheckBox *channel2Check;
    QCheckBox *channel3Check;
    QCheckBox *channel4Check;
    QHBoxLayout *channelButtonLayout;
    QPushButton *addChannelGroupButton;
    QPushButton *editChannelGroupButton;
    QPushButton *deleteChannelGroupButton;
    QPushButton *clearChannelGroupButton;
    QTableWidget *channelGroupTable;
    QWidget *assignmentTab;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *assignmentGroupBox;
    QFormLayout *formLayout_3;
    QLabel *assignUserLabel;
    QComboBox *assignUserCombo;
    QLabel *assignGroupLabel;
    QComboBox *assignGroupCombo;
    QHBoxLayout *assignmentButtonLayout;
    QPushButton *assignButton;
    QPushButton *unassignButton;
    QTableWidget *assignmentTable;

    void setupUi(QWidget *UserManagement)
    {
        if (UserManagement->objectName().isEmpty())
            UserManagement->setObjectName("UserManagement");
        UserManagement->resize(800, 600);
        verticalLayout = new QVBoxLayout(UserManagement);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(UserManagement);
        titleLabel->setObjectName("titleLabel");
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignLeft);
        titleLabel->setMargin(0);

        verticalLayout->addWidget(titleLabel);

        tabWidget = new QTabWidget(UserManagement);
        tabWidget->setObjectName("tabWidget");
        userTab = new QWidget();
        userTab->setObjectName("userTab");
        verticalLayout_2 = new QVBoxLayout(userTab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        formGroupBox = new QGroupBox(userTab);
        formGroupBox->setObjectName("formGroupBox");
        formLayout = new QFormLayout(formGroupBox);
        formLayout->setObjectName("formLayout");
        usernameLabel = new QLabel(formGroupBox);
        usernameLabel->setObjectName("usernameLabel");

        formLayout->setWidget(0, QFormLayout::LabelRole, usernameLabel);

        usernameEdit = new QLineEdit(formGroupBox);
        usernameEdit->setObjectName("usernameEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, usernameEdit);

        passwordLabel = new QLabel(formGroupBox);
        passwordLabel->setObjectName("passwordLabel");

        formLayout->setWidget(1, QFormLayout::LabelRole, passwordLabel);

        passwordEdit = new QLineEdit(formGroupBox);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, passwordEdit);

        roleLabel = new QLabel(formGroupBox);
        roleLabel->setObjectName("roleLabel");

        formLayout->setWidget(2, QFormLayout::LabelRole, roleLabel);

        roleCombo = new QComboBox(formGroupBox);
        roleCombo->addItem(QString());
        roleCombo->addItem(QString());
        roleCombo->setObjectName("roleCombo");

        formLayout->setWidget(2, QFormLayout::FieldRole, roleCombo);


        verticalLayout_2->addWidget(formGroupBox);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        addButton = new QPushButton(userTab);
        addButton->setObjectName("addButton");
        addButton->setStyleSheet(QString::fromUtf8("\n"
"             QPushButton {\n"
"                 background-color: #2ecc71;\n"
"                 color: white;\n"
"                 border: none;\n"
"                 padding: 5px 15px;\n"
"                 border-radius: 4px;\n"
"             }\n"
"             QPushButton:hover {\n"
"                 background-color: #27ae60;\n"
"             }\n"
"            "));

        buttonLayout->addWidget(addButton);

        editButton = new QPushButton(userTab);
        editButton->setObjectName("editButton");
        editButton->setStyleSheet(QString::fromUtf8("\n"
"             QPushButton {\n"
"                 background-color: #f1c40f;\n"
"                 color: white;\n"
"                 border: none;\n"
"                 padding: 5px 15px;\n"
"                 border-radius: 4px;\n"
"             }\n"
"             QPushButton:hover {\n"
"                 background-color: #f39c12;\n"
"             }\n"
"            "));

        buttonLayout->addWidget(editButton);

        deleteButton = new QPushButton(userTab);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setStyleSheet(QString::fromUtf8("\n"
"             QPushButton {\n"
"                 background-color: #e74c3c;\n"
"                 color: white;\n"
"                 border: none;\n"
"                 padding: 5px 15px;\n"
"                 border-radius: 4px;\n"
"             }\n"
"             QPushButton:hover {\n"
"                 background-color: #c0392b;\n"
"             }\n"
"            "));

        buttonLayout->addWidget(deleteButton);

        clearButton = new QPushButton(userTab);
        clearButton->setObjectName("clearButton");
        clearButton->setStyleSheet(QString::fromUtf8("\n"
"             QPushButton {\n"
"                 background-color: #95a5a6;\n"
"                 color: white;\n"
"                 border: none;\n"
"                 padding: 5px 15px;\n"
"                 border-radius: 4px;\n"
"             }\n"
"             QPushButton:hover {\n"
"                 background-color: #7f8c8d;\n"
"             }\n"
"            "));

        buttonLayout->addWidget(clearButton);


        verticalLayout_2->addLayout(buttonLayout);

        userTable = new QTableWidget(userTab);
        if (userTable->columnCount() < 2)
            userTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        userTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        userTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        userTable->setObjectName("userTable");
        userTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        userTable->setSelectionMode(QAbstractItemView::SingleSelection);

        verticalLayout_2->addWidget(userTable);

        tabWidget->addTab(userTab, QString());
        channelTab = new QWidget();
        channelTab->setObjectName("channelTab");
        verticalLayout_3 = new QVBoxLayout(channelTab);
        verticalLayout_3->setObjectName("verticalLayout_3");
        channelGroupBox = new QGroupBox(channelTab);
        channelGroupBox->setObjectName("channelGroupBox");
        formLayout_2 = new QFormLayout(channelGroupBox);
        formLayout_2->setObjectName("formLayout_2");
        groupNameLabel = new QLabel(channelGroupBox);
        groupNameLabel->setObjectName("groupNameLabel");

        formLayout_2->setWidget(0, QFormLayout::LabelRole, groupNameLabel);

        groupNameEdit = new QLineEdit(channelGroupBox);
        groupNameEdit->setObjectName("groupNameEdit");

        formLayout_2->setWidget(0, QFormLayout::FieldRole, groupNameEdit);

        channelsLabel = new QLabel(channelGroupBox);
        channelsLabel->setObjectName("channelsLabel");

        formLayout_2->setWidget(1, QFormLayout::LabelRole, channelsLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        channel1Check = new QCheckBox(channelGroupBox);
        channel1Check->setObjectName("channel1Check");

        horizontalLayout->addWidget(channel1Check);

        channel2Check = new QCheckBox(channelGroupBox);
        channel2Check->setObjectName("channel2Check");

        horizontalLayout->addWidget(channel2Check);

        channel3Check = new QCheckBox(channelGroupBox);
        channel3Check->setObjectName("channel3Check");

        horizontalLayout->addWidget(channel3Check);

        channel4Check = new QCheckBox(channelGroupBox);
        channel4Check->setObjectName("channel4Check");

        horizontalLayout->addWidget(channel4Check);


        formLayout_2->setLayout(1, QFormLayout::FieldRole, horizontalLayout);


        verticalLayout_3->addWidget(channelGroupBox);

        channelButtonLayout = new QHBoxLayout();
        channelButtonLayout->setObjectName("channelButtonLayout");
        addChannelGroupButton = new QPushButton(channelTab);
        addChannelGroupButton->setObjectName("addChannelGroupButton");
        addChannelGroupButton->setStyleSheet(QString::fromUtf8("\n"
"             QPushButton {\n"
"                 background-color: #2ecc71;\n"
"                 color: white;\n"
"                 border: none;\n"
"                 padding: 5px 15px;\n"
"                 border-radius: 4px;\n"
"             }\n"
"             QPushButton:hover {\n"
"                 background-color: #27ae60;\n"
"             }\n"
"            "));

        channelButtonLayout->addWidget(addChannelGroupButton);

        editChannelGroupButton = new QPushButton(channelTab);
        editChannelGroupButton->setObjectName("editChannelGroupButton");
        editChannelGroupButton->setStyleSheet(QString::fromUtf8("\n"
"             QPushButton {\n"
"                 background-color: #f1c40f;\n"
"                 color: white;\n"
"                 border: none;\n"
"                 padding: 5px 15px;\n"
"                 border-radius: 4px;\n"
"             }\n"
"             QPushButton:hover {\n"
"                 background-color: #f39c12;\n"
"             }\n"
"            "));

        channelButtonLayout->addWidget(editChannelGroupButton);

        deleteChannelGroupButton = new QPushButton(channelTab);
        deleteChannelGroupButton->setObjectName("deleteChannelGroupButton");
        deleteChannelGroupButton->setStyleSheet(QString::fromUtf8("\n"
"             QPushButton {\n"
"                 background-color: #e74c3c;\n"
"                 color: white;\n"
"                 border: none;\n"
"                 padding: 5px 15px;\n"
"                 border-radius: 4px;\n"
"             }\n"
"             QPushButton:hover {\n"
"                 background-color: #c0392b;\n"
"             }\n"
"            "));

        channelButtonLayout->addWidget(deleteChannelGroupButton);

        clearChannelGroupButton = new QPushButton(channelTab);
        clearChannelGroupButton->setObjectName("clearChannelGroupButton");
        clearChannelGroupButton->setStyleSheet(QString::fromUtf8("\n"
"             QPushButton {\n"
"                 background-color: #95a5a6;\n"
"                 color: white;\n"
"                 border: none;\n"
"                 padding: 5px 15px;\n"
"                 border-radius: 4px;\n"
"             }\n"
"             QPushButton:hover {\n"
"                 background-color: #7f8c8d;\n"
"             }\n"
"            "));

        channelButtonLayout->addWidget(clearChannelGroupButton);


        verticalLayout_3->addLayout(channelButtonLayout);

        channelGroupTable = new QTableWidget(channelTab);
        if (channelGroupTable->columnCount() < 2)
            channelGroupTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        channelGroupTable->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        channelGroupTable->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        channelGroupTable->setObjectName("channelGroupTable");
        channelGroupTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        channelGroupTable->setSelectionMode(QAbstractItemView::SingleSelection);

        verticalLayout_3->addWidget(channelGroupTable);

        tabWidget->addTab(channelTab, QString());
        assignmentTab = new QWidget();
        assignmentTab->setObjectName("assignmentTab");
        verticalLayout_4 = new QVBoxLayout(assignmentTab);
        verticalLayout_4->setObjectName("verticalLayout_4");
        assignmentGroupBox = new QGroupBox(assignmentTab);
        assignmentGroupBox->setObjectName("assignmentGroupBox");
        formLayout_3 = new QFormLayout(assignmentGroupBox);
        formLayout_3->setObjectName("formLayout_3");
        assignUserLabel = new QLabel(assignmentGroupBox);
        assignUserLabel->setObjectName("assignUserLabel");

        formLayout_3->setWidget(0, QFormLayout::LabelRole, assignUserLabel);

        assignUserCombo = new QComboBox(assignmentGroupBox);
        assignUserCombo->setObjectName("assignUserCombo");

        formLayout_3->setWidget(0, QFormLayout::FieldRole, assignUserCombo);

        assignGroupLabel = new QLabel(assignmentGroupBox);
        assignGroupLabel->setObjectName("assignGroupLabel");

        formLayout_3->setWidget(1, QFormLayout::LabelRole, assignGroupLabel);

        assignGroupCombo = new QComboBox(assignmentGroupBox);
        assignGroupCombo->setObjectName("assignGroupCombo");

        formLayout_3->setWidget(1, QFormLayout::FieldRole, assignGroupCombo);


        verticalLayout_4->addWidget(assignmentGroupBox);

        assignmentButtonLayout = new QHBoxLayout();
        assignmentButtonLayout->setObjectName("assignmentButtonLayout");
        assignButton = new QPushButton(assignmentTab);
        assignButton->setObjectName("assignButton");
        assignButton->setStyleSheet(QString::fromUtf8("\n"
"             QPushButton {\n"
"                 background-color: #2ecc71;\n"
"                 color: white;\n"
"                 border: none;\n"
"                 padding: 5px 15px;\n"
"                 border-radius: 4px;\n"
"             }\n"
"             QPushButton:hover {\n"
"                 background-color: #27ae60;\n"
"             }\n"
"            "));

        assignmentButtonLayout->addWidget(assignButton);

        unassignButton = new QPushButton(assignmentTab);
        unassignButton->setObjectName("unassignButton");
        unassignButton->setStyleSheet(QString::fromUtf8("\n"
"             QPushButton {\n"
"                 background-color: #e74c3c;\n"
"                 color: white;\n"
"                 border: none;\n"
"                 padding: 5px 15px;\n"
"                 border-radius: 4px;\n"
"             }\n"
"             QPushButton:hover {\n"
"                 background-color: #c0392b;\n"
"             }\n"
"            "));

        assignmentButtonLayout->addWidget(unassignButton);


        verticalLayout_4->addLayout(assignmentButtonLayout);

        assignmentTable = new QTableWidget(assignmentTab);
        if (assignmentTable->columnCount() < 2)
            assignmentTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        assignmentTable->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        assignmentTable->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        assignmentTable->setObjectName("assignmentTable");
        assignmentTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        assignmentTable->setSelectionMode(QAbstractItemView::SingleSelection);

        verticalLayout_4->addWidget(assignmentTable);

        tabWidget->addTab(assignmentTab, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(UserManagement);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(UserManagement);
    } // setupUi

    void retranslateUi(QWidget *UserManagement)
    {
        UserManagement->setWindowTitle(QCoreApplication::translate("UserManagement", "User Management", nullptr));
        titleLabel->setText(QCoreApplication::translate("UserManagement", "Administration", nullptr));
        titleLabel->setProperty("class", QVariant(QCoreApplication::translate("UserManagement", "page-title", nullptr)));
        formGroupBox->setTitle(QCoreApplication::translate("UserManagement", "User Details", nullptr));
        usernameLabel->setText(QCoreApplication::translate("UserManagement", "Username:", nullptr));
        passwordLabel->setText(QCoreApplication::translate("UserManagement", "Password:", nullptr));
        roleLabel->setText(QCoreApplication::translate("UserManagement", "Role:", nullptr));
        roleCombo->setItemText(0, QCoreApplication::translate("UserManagement", "user", nullptr));
        roleCombo->setItemText(1, QCoreApplication::translate("UserManagement", "admin", nullptr));

        addButton->setText(QCoreApplication::translate("UserManagement", "Add User", nullptr));
        editButton->setText(QCoreApplication::translate("UserManagement", "Update User", nullptr));
        deleteButton->setText(QCoreApplication::translate("UserManagement", "Delete User", nullptr));
        clearButton->setText(QCoreApplication::translate("UserManagement", "Clear Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = userTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("UserManagement", "Username", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = userTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("UserManagement", "Role", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(userTab), QCoreApplication::translate("UserManagement", "User Management", nullptr));
        channelGroupBox->setTitle(QCoreApplication::translate("UserManagement", "Channel Group Details", nullptr));
        groupNameLabel->setText(QCoreApplication::translate("UserManagement", "Group Name:", nullptr));
        channelsLabel->setText(QCoreApplication::translate("UserManagement", "Channels:", nullptr));
        channel1Check->setText(QCoreApplication::translate("UserManagement", "Channel 1", nullptr));
        channel2Check->setText(QCoreApplication::translate("UserManagement", "Channel 2", nullptr));
        channel3Check->setText(QCoreApplication::translate("UserManagement", "Channel 3", nullptr));
        channel4Check->setText(QCoreApplication::translate("UserManagement", "Channel 4", nullptr));
        addChannelGroupButton->setText(QCoreApplication::translate("UserManagement", "Add Group", nullptr));
        editChannelGroupButton->setText(QCoreApplication::translate("UserManagement", "Update Group", nullptr));
        deleteChannelGroupButton->setText(QCoreApplication::translate("UserManagement", "Delete Group", nullptr));
        clearChannelGroupButton->setText(QCoreApplication::translate("UserManagement", "Clear Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = channelGroupTable->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("UserManagement", "Group Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = channelGroupTable->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("UserManagement", "Channels", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(channelTab), QCoreApplication::translate("UserManagement", "Channel Groups", nullptr));
        assignmentGroupBox->setTitle(QCoreApplication::translate("UserManagement", "Assign Channel Groups to Users", nullptr));
        assignUserLabel->setText(QCoreApplication::translate("UserManagement", "User:", nullptr));
        assignGroupLabel->setText(QCoreApplication::translate("UserManagement", "Channel Group:", nullptr));
        assignButton->setText(QCoreApplication::translate("UserManagement", "Assign Group to User", nullptr));
        unassignButton->setText(QCoreApplication::translate("UserManagement", "Remove Assignment", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = assignmentTable->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("UserManagement", "Username", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = assignmentTable->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("UserManagement", "Channel Group", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(assignmentTab), QCoreApplication::translate("UserManagement", "User Assignments", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserManagement: public Ui_UserManagement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERMANAGEMENT_H

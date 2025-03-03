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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserManagement
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
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
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        formGroupBox = new QGroupBox(UserManagement);
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


        verticalLayout->addWidget(formGroupBox);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        addButton = new QPushButton(UserManagement);
        addButton->setObjectName("addButton");
        addButton->setStyleSheet(QString::fromUtf8("\n"
"         QPushButton {\n"
"             background-color: #2ecc71;\n"
"             color: white;\n"
"             border: none;\n"
"             padding: 5px 15px;\n"
"             border-radius: 4px;\n"
"         }\n"
"         QPushButton:hover {\n"
"             background-color: #27ae60;\n"
"         }\n"
"        "));

        buttonLayout->addWidget(addButton);

        editButton = new QPushButton(UserManagement);
        editButton->setObjectName("editButton");
        editButton->setStyleSheet(QString::fromUtf8("\n"
"         QPushButton {\n"
"             background-color: #f1c40f;\n"
"             color: white;\n"
"             border: none;\n"
"             padding: 5px 15px;\n"
"             border-radius: 4px;\n"
"         }\n"
"         QPushButton:hover {\n"
"             background-color: #f39c12;\n"
"         }\n"
"        "));

        buttonLayout->addWidget(editButton);

        deleteButton = new QPushButton(UserManagement);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setStyleSheet(QString::fromUtf8("\n"
"         QPushButton {\n"
"             background-color: #e74c3c;\n"
"             color: white;\n"
"             border: none;\n"
"             padding: 5px 15px;\n"
"             border-radius: 4px;\n"
"         }\n"
"         QPushButton:hover {\n"
"             background-color: #c0392b;\n"
"         }\n"
"        "));

        buttonLayout->addWidget(deleteButton);

        clearButton = new QPushButton(UserManagement);
        clearButton->setObjectName("clearButton");
        clearButton->setStyleSheet(QString::fromUtf8("\n"
"         QPushButton {\n"
"             background-color: #95a5a6;\n"
"             color: white;\n"
"             border: none;\n"
"             padding: 5px 15px;\n"
"             border-radius: 4px;\n"
"         }\n"
"         QPushButton:hover {\n"
"             background-color: #7f8c8d;\n"
"         }\n"
"        "));

        buttonLayout->addWidget(clearButton);


        verticalLayout->addLayout(buttonLayout);

        userTable = new QTableWidget(UserManagement);
        if (userTable->columnCount() < 3)
            userTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        userTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        userTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        userTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        userTable->setObjectName("userTable");
        userTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        userTable->setSelectionMode(QAbstractItemView::SingleSelection);

        verticalLayout->addWidget(userTable);


        retranslateUi(UserManagement);

        QMetaObject::connectSlotsByName(UserManagement);
    } // setupUi

    void retranslateUi(QWidget *UserManagement)
    {
        UserManagement->setWindowTitle(QCoreApplication::translate("UserManagement", "User Management", nullptr));
        titleLabel->setText(QCoreApplication::translate("UserManagement", "User Management", nullptr));
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
        QTableWidgetItem *___qtablewidgetitem2 = userTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("UserManagement", "Actions", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserManagement: public Ui_UserManagement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERMANAGEMENT_H

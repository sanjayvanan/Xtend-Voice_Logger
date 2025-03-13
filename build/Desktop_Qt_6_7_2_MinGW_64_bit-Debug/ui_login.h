/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox_login;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_cimtitle1;
    QLabel *label_loginname1;
    QFormLayout *formLayout;
    QLabel *label__username;
    QLabel *label_password;
    QLineEdit *lineEdit__password;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *login_2;
    QLineEdit *lineEdit_username;
    QLabel *label_logo;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_loginfooter;

    void setupUi(QWidget *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName("login");
        login->resize(1195, 627);
        verticalLayout_3 = new QVBoxLayout(login);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        groupBox_login = new QGroupBox(login);
        groupBox_login->setObjectName("groupBox_login");
        horizontalLayout_3 = new QHBoxLayout(groupBox_login);
        horizontalLayout_3->setSpacing(15);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(15, 15, 15, 15);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(15);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(10);
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_cimtitle1 = new QLabel(groupBox_login);
        label_cimtitle1->setObjectName("label_cimtitle1");
        QFont font;
        font.setBold(true);
        font.setItalic(false);
        label_cimtitle1->setFont(font);
        label_cimtitle1->setScaledContents(false);
        label_cimtitle1->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_cimtitle1->setWordWrap(true);

        verticalLayout_4->addWidget(label_cimtitle1);

        label_loginname1 = new QLabel(groupBox_login);
        label_loginname1->setObjectName("label_loginname1");
        label_loginname1->setFont(font);
        label_loginname1->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(label_loginname1);


        verticalLayout_2->addLayout(verticalLayout_4);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setHorizontalSpacing(8);
        formLayout->setVerticalSpacing(10);
        formLayout->setContentsMargins(-1, -1, -1, 0);
        label__username = new QLabel(groupBox_login);
        label__username->setObjectName("label__username");
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        label__username->setFont(font1);
        label__username->setStyleSheet(QString::fromUtf8(""));

        formLayout->setWidget(1, QFormLayout::LabelRole, label__username);

        label_password = new QLabel(groupBox_login);
        label_password->setObjectName("label_password");
        label_password->setFont(font1);

        formLayout->setWidget(2, QFormLayout::LabelRole, label_password);

        lineEdit__password = new QLineEdit(groupBox_login);
        lineEdit__password->setObjectName("lineEdit__password");
        QFont font2;
        font2.setPointSize(10);
        lineEdit__password->setFont(font2);
        lineEdit__password->setEchoMode(QLineEdit::EchoMode::Password);

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEdit__password);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(5);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        login_2 = new QPushButton(groupBox_login);
        login_2->setObjectName("login_2");
        login_2->setFont(font1);
        login_2->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        login_2->setAutoDefault(true);
        login_2->setFlat(false);

        horizontalLayout_2->addWidget(login_2);


        formLayout->setLayout(3, QFormLayout::FieldRole, horizontalLayout_2);

        lineEdit_username = new QLineEdit(groupBox_login);
        lineEdit_username->setObjectName("lineEdit_username");
        lineEdit_username->setFont(font2);

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_username);


        verticalLayout_2->addLayout(formLayout);


        horizontalLayout_3->addLayout(verticalLayout_2);

        label_logo = new QLabel(groupBox_login);
        label_logo->setObjectName("label_logo");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_logo->sizePolicy().hasHeightForWidth());
        label_logo->setSizePolicy(sizePolicy);
        label_logo->setAutoFillBackground(true);
        label_logo->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_3->addWidget(label_logo);


        horizontalLayout->addWidget(groupBox_login);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        label_loginfooter = new QLabel(login);
        label_loginfooter->setObjectName("label_loginfooter");
        label_loginfooter->setFont(font1);
        label_loginfooter->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(label_loginfooter);

#if QT_CONFIG(shortcut)
        label__username->setBuddy(lineEdit_username);
        label_password->setBuddy(lineEdit__password);
#endif // QT_CONFIG(shortcut)

        retranslateUi(login);

        login_2->setDefault(true);


        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QWidget *login)
    {
        login->setWindowTitle(QCoreApplication::translate("login", "Form", nullptr));
        groupBox_login->setTitle(QString());
        label_cimtitle1->setText(QCoreApplication::translate("login", "Zosh Voice Logger", nullptr));
        label_loginname1->setText(QCoreApplication::translate("login", "Login", nullptr));
        label__username->setText(QCoreApplication::translate("login", "Username  ", nullptr));
        label_password->setText(QCoreApplication::translate("login", "Password  ", nullptr));
        login_2->setText(QCoreApplication::translate("login", "Login", nullptr));
        label_logo->setText(QString());
        label_loginfooter->setText(QCoreApplication::translate("login", "System Developed by : Zosh Aerospace", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H

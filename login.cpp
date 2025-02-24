#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include "apihandler.h"

login::login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login)
    , apiHandler(new APIHandler(this))
{
    ui->setupUi(this);
    setWindowTitle("Zosh Voice Logger - Login");
    
    connect(apiHandler, &APIHandler::loginSuccessful, 
            this, &login::handleLoginSuccess);
    connect(apiHandler, &APIHandler::loginFailed, 
            this, &login::handleLoginFailure);
}

login::~login()
{
    delete ui;
}

void login::on_login_2_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit__password->text();
    QString hashedPassword = APIHandler::hashPassword(password);

    ui->login_2->setEnabled(false);
    apiHandler->login(username, hashedPassword);
}

void login::handleLoginSuccess(const QString &token)
{
    ui->login_2->setEnabled(true);
    emit loginSuccessful(token);
    hide();
}

void login::handleLoginFailure(const QString &message)
{
    ui->login_2->setEnabled(true);
    QMessageBox::warning(this, "Login", "Login failed: " + message);
}

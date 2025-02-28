#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "apihandler.h"

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

signals:
    void loginSuccessful(const QString &token);

private slots:
    void on_login_2_clicked();
    void handleLoginSuccess(const QString &token);
    void handleLoginFailure(const QString &message);


private:
    Ui::login *ui;
    APIHandler *apiHandler;
};

#endif // LOGIN_H

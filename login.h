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
    static void initializeDatabase();

signals:
    void loginSuccessful(const QString &token, const QString &username, const QString &role);

private slots:
    void on_login_2_clicked();
    void handleLoginSuccess(const QString &token);
    void handleLoginFailure(const QString &message);

private:
    bool validateCredentials(const QString &username, const QString &password);
    static void createTablesIfNotExist();
    static void addDefaultUserIfNotExist();
    
    Ui::login *ui;
    APIHandler *apiHandler;
    QString backendToken;
    QString currentDisplayName;
    QString currentRole;
};

#endif // LOGIN_H

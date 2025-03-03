#include "mainwindow.h"
#include "login.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // Initialize the database before creating the login window
    login::initializeDatabase();
    
    // Apply stylesheet
    QFile file(":/myres/res/style_light.qss");
    if(file.open(QFile::ReadOnly | QFile::Text)){
        QTextStream stream(&file);
        QString styleSheet = stream.readAll();
        a.setStyleSheet(styleSheet);
        file.close();
    }

    MainWindow *mainWindow = new MainWindow();
    login *loginWindow = new login();

    // Connect login success to main window
    QObject::connect(loginWindow, &login::loginSuccessful,
                    [mainWindow](const QString &token, const QString &username, const QString &role) {
        mainWindow->setSessionToken(token, username, role);
        mainWindow->show();
    });

    loginWindow->show();

    return a.exec();
}

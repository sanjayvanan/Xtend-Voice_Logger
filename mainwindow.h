#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "apihandler.h"
#include "timetimecalls.h"
#include "dashboard.h"
#include "livecalls.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setSessionToken(const QString &token);

private slots:
    void on_actionLogout_triggered();
    void handleLogoutSuccess();
    void handleLogoutFailure(const QString &message);

private:
    Ui::MainWindow *ui;
    APIHandler *apiHandler;
    QString sessionToken;
    TimeTimeCalls *timeTimeCalls;
    Dashboard *dashboard;
    LiveCalls *liveCalls;
};
#endif // MAINWINDOW_H

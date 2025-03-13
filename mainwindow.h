#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "apihandler.h"
#include "timetimecalls.h"
#include "dashboard.h"
#include "livecalls.h"
#include "usermanagement.h"
#include <QTableWidget>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QGroupBox>
#include <QPushButton>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setSessionToken(const QString &token, const QString &username, const QString &role);
    QString getCurrentUsername() const { return currentDisplayName; }

private slots:
    void on_actionLogout_triggered();
    void handleLogoutSuccess();
    void handleLogoutFailure(const QString &message);
    void onAddUserClicked();
    void onDeleteUserClicked();
    void on_btnDashboard_clicked();
    void on_btnLiveCalls_clicked();
    void on_btnTimeTimeCalls_clicked();
    void on_btnUserManagement_clicked();

private:
    Ui::MainWindow *ui;
    APIHandler *apiHandler;
    QString sessionToken;
    TimeTimeCalls *timeTimeCalls;
    Dashboard *dashboard;
    LiveCalls *liveCalls;
    UserManagement *userManagement;
    QWidget *userManagementWidget = nullptr;
    QString currentUserRole;
    QString currentDisplayName;
    QTableWidget *tableUsers = nullptr;

    void setupUserManagement();
    void refreshUserList();
};
#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTableWidgetItem>
#include <QTimer>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTemporaryFile>
#include <QDir>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , apiHandler(new APIHandler(this))
{
    ui->setupUi(this);
    setWindowTitle("Zosh Voice Logger");

    // Initialize widgets
    dashboard = new Dashboard(this);
    timeTimeCalls = new TimeTimeCalls(this);
    liveCalls = new LiveCalls(this);

    // Remove existing widgets from stacked widget
    while (ui->stackedWidget->count() > 0) {
        ui->stackedWidget->removeWidget(ui->stackedWidget->widget(0));
    }

    // Add widgets to stacked widget in the correct order
    ui->stackedWidget->addWidget(dashboard);     // Index 0: Dashboard
    ui->stackedWidget->addWidget(liveCalls);     // Index 1: Live Calls
    ui->stackedWidget->addWidget(timeTimeCalls); // Index 2: Time to Time Calls

    // Connect button clicks to switch pages
    connect(ui->btnDashboard, &QPushButton::clicked, [this]() {
        ui->stackedWidget->setCurrentIndex(0);
        dashboard->setSessionToken(sessionToken);
        liveCalls->stopMonitoring();
    });

    connect(ui->btnLiveCalls, &QPushButton::clicked, [this]() {
        ui->stackedWidget->setCurrentIndex(1);
        liveCalls->setSessionToken(sessionToken);
        liveCalls->startMonitoring();
    });

    connect(ui->btnTimeTime, &QPushButton::clicked, [this]() {
        ui->stackedWidget->setCurrentIndex(2);
        timeTimeCalls->setSessionToken(sessionToken);
        liveCalls->stopMonitoring();
    });

    // Connect logout button
    connect(ui->btnLogout, &QPushButton::clicked, this, &MainWindow::on_actionLogout_triggered);

    // Set default view
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSessionToken(const QString &token)
{
    sessionToken = token;
    dashboard->setSessionToken(token);
    liveCalls->setSessionToken(token);
    timeTimeCalls->setSessionToken(token);
}

void MainWindow::on_actionLogout_triggered()
{
    if (!sessionToken.isEmpty()) {
        apiHandler->logout(sessionToken);
    }
}

void MainWindow::handleLogoutSuccess()
{
    QMessageBox::information(this, "Logout", "Successfully logged out");
    close();
}

void MainWindow::handleLogoutFailure(const QString &message)
{
    QMessageBox::warning(this, "Logout", "Logout failed: " + message);
}


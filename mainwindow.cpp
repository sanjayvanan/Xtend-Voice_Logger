#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dashboard.h"
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
    , liveCallsTimer(new QTimer(this))
    , mediaPlayer(nullptr)
    , audioOutput(nullptr)
    , tempWaveFile(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("Zosh Voice Logger");

    // Initialize widgets
    dashboard = new Dashboard(this);
    timeTimeCalls = new TimeTimeCalls(this);

    // Remove existing widgets from stacked widget
    while (ui->stackedWidget->count() > 0) {
        ui->stackedWidget->removeWidget(ui->stackedWidget->widget(0));
    }

    // Add widgets to stacked widget in the correct order
    ui->stackedWidget->addWidget(dashboard);         // Index 0: Dashboard (from dashboard.ui)
    ui->stackedWidget->addWidget(ui->pageCallLogs);  // Index 1: Call Logs
    ui->stackedWidget->addWidget(ui->pageLiveCalls); // Index 2: Live Calls
    ui->stackedWidget->addWidget(timeTimeCalls);     // Index 3: Time to Time Calls

    // Connect button clicks to switch pages
    connect(ui->btnDashboard, &QPushButton::clicked, [this]() {
        ui->stackedWidget->setCurrentIndex(0);
        dashboard->setSessionToken(sessionToken);  // Update dashboard when shown
    });

    connect(ui->btnLiveCalls, &QPushButton::clicked, [this]() {
        ui->stackedWidget->setCurrentIndex(2);
        refreshLiveCalls(); // Fetch immediately
        liveCallsTimer->start(); // Start periodic updates
    });

    connect(ui->btnTimeTime, &QPushButton::clicked, [this]() {
        ui->stackedWidget->setCurrentIndex(3);
        timeTimeCalls->setSessionToken(sessionToken);
    });

    // Connect API handler signals
    connect(apiHandler, &APIHandler::logoutSuccessful,
            this, &MainWindow::handleLogoutSuccess);
    connect(apiHandler, &APIHandler::logoutFailed,
            this, &MainWindow::handleLogoutFailure);
    connect(apiHandler, &APIHandler::callDetailsReceived,
            this, &MainWindow::handleCallDetails);
    connect(apiHandler, &APIHandler::callDetailsFailed,
            this, &MainWindow::handleCallDetailsFailed);
    connect(apiHandler, &APIHandler::liveCallsReceived,
            this, &MainWindow::handleLiveCalls);
    connect(apiHandler, &APIHandler::liveCallsFailed,
            this, &MainWindow::handleLiveCallsFailed);
    connect(apiHandler, &APIHandler::waveFileReceived,
            this, &MainWindow::handleWaveFile);

    // Set up timer for live calls refresh
    liveCallsTimer->setInterval(5000); // Refresh every 5 seconds
    connect(liveCallsTimer, &QTimer::timeout,
            this, &MainWindow::refreshLiveCalls);

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
    
    // Initialize dashboard
    dashboard->setSessionToken(token);
    
    // Initialize time time calls
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


void MainWindow::handleCallDetails(const QJsonObject &details)
{
    updateCallDetailsTable(details);
}

void MainWindow::handleCallDetailsFailed(const QString &message)
{
    QMessageBox::warning(this, "Error", "Failed to fetch call details: " + message);
}

void MainWindow::updateCallDetailsTable(const QJsonObject &details)
{
    QJsonArray callList = details["List"].toArray();
    ui->tableWidget->setRowCount(callList.size());

    for (int i = 0; i < callList.size(); ++i) {
        QJsonObject call = callList[i].toObject();

        // Create table items
        QTableWidgetItem *refId = new QTableWidgetItem(call["CallRef-ID"].toString());
        QTableWidgetItem *channel = new QTableWidgetItem(call["Channel"].toString());
        QTableWidgetItem *callType = new QTableWidgetItem(call["Call-Type"].toString());
        QTableWidgetItem *callTime = new QTableWidgetItem(call["Call-Time"].toString());
        QTableWidgetItem *duration = new QTableWidgetItem(call["Total-Duration"].toString());
        QTableWidgetItem *status = new QTableWidgetItem(call["Call-Status"].toString());

        // Add items to table
        ui->tableWidget->setItem(i, 0, refId);
        ui->tableWidget->setItem(i, 1, channel);
        ui->tableWidget->setItem(i, 2, callType);
        ui->tableWidget->setItem(i, 3, callTime);
        ui->tableWidget->setItem(i, 4, duration);
        ui->tableWidget->setItem(i, 5, status);
    }

    // Adjust column widths
    ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::on_btnDashboard_clicked()
{
    // Switch to the dashboard page
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_btnCallLogs_clicked()
{
    // This function is now removed
}

void MainWindow::on_btnLiveCalls_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    refreshLiveCalls(); // Fetch immediately
    liveCallsTimer->start(); // Start periodic updates
}

void MainWindow::refreshLiveCalls()
{
    if (!sessionToken.isEmpty()) {
        apiHandler->fetchLiveCalls(sessionToken);
    }
}

void MainWindow::handleLiveCalls(const QJsonObject &details)
{
    updateLiveCallsTable(details);
}

void MainWindow::handleLiveCallsFailed(const QString &message)
{
    ui->labelLiveCallsStatus->setText("Error: " + message);
}

void MainWindow::updateLiveCallsTable(const QJsonObject &details)
{
    // Clear existing items
    ui->tableLiveCalls->clearContents();
    ui->tableLiveCalls->setRowCount(0);

    // Update status label
    QString status = details["status"].toString();
    QString message = details["message"].toString();

    if (status == "0") {
        ui->labelLiveCallsStatus->setText("No active calls");
        return;
    }

    QJsonArray callList = details["List"].toArray();
    ui->tableLiveCalls->setRowCount(callList.size());
    ui->labelLiveCallsStatus->setText(QString("Active Calls: %1").arg(details["TotalCount"].toString()));

    for (int i = 0; i < callList.size(); ++i) {
        QJsonObject call = callList[i].toObject();

        QTableWidgetItem *channel = new QTableWidgetItem(call["Channel"].toString());
        QTableWidgetItem *channelName = new QTableWidgetItem(call["Channel-Name"].toString());
        QTableWidgetItem *callType = new QTableWidgetItem(call["Call-Type"].toString() == "O" ? "Outgoing" : "Incoming");
        QTableWidgetItem *callTime = new QTableWidgetItem(call["Call-Time"].toString());
        QTableWidgetItem *callerID = new QTableWidgetItem(call["Caller-ID"].toString());
        QTableWidgetItem *calledID = new QTableWidgetItem(call["Called-ID"].toString());
        QTableWidgetItem *reason = new QTableWidgetItem(call["Reason"].toString());

        ui->tableLiveCalls->setItem(i, 0, channel);
        ui->tableLiveCalls->setItem(i, 1, channelName);
        ui->tableLiveCalls->setItem(i, 2, callType);
        ui->tableLiveCalls->setItem(i, 3, callTime);
        ui->tableLiveCalls->setItem(i, 4, callerID);
        ui->tableLiveCalls->setItem(i, 5, calledID);
        ui->tableLiveCalls->setItem(i, 6, reason);

        // Add Listen button for connected calls
        if (call["Reason"].toString() == "Connected") {
            QPushButton *listenButton = new QPushButton("Listen Live");
            listenButton->setProperty("callRefId", call["CallRef-ID"].toString());

            connect(listenButton, &QPushButton::clicked, this, [this, call]() {
                QString callRefId = call["CallRef-ID"].toString();
                apiHandler->streamWaveFile(sessionToken, callRefId);
            });

            ui->tableLiveCalls->setCellWidget(i, 7, listenButton);
        }
    }

    ui->tableLiveCalls->resizeColumnsToContents();
}

void MainWindow::handleWaveFile(const QByteArray &waveData)
{
    if (!mediaPlayer) {
        mediaPlayer = new QMediaPlayer(this);
        audioOutput = new QAudioOutput(this);
        mediaPlayer->setAudioOutput(audioOutput);
    }

    // Create a temporary file for the streaming audio
    if (tempWaveFile) {
        delete tempWaveFile;
    }
    tempWaveFile = new QTemporaryFile(this);
    tempWaveFile->setFileTemplate(QDir::tempPath() + "/voicelogger_live_XXXXXX.wav");

    if (!tempWaveFile->open()) {
        QMessageBox::warning(this, "Error", "Could not create temporary file for playback");
        return;
    }

    // Write the wave data and play
    tempWaveFile->write(waveData);
    tempWaveFile->flush();
    tempWaveFile->seek(0);

    mediaPlayer->setSource(QUrl::fromLocalFile(tempWaveFile->fileName()));
    mediaPlayer->play();
}


